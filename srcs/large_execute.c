/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   large_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 04:42:49 by akhellad          #+#    #+#             */
/*   Updated: 2023/11/16 09:37:35 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_dup(t_cmds_infos *cmd, t_infos *infos, int end[2], int in_fd)

{
	if (cmd->prev && dup2(in_fd, 0) < 0)
		ft_error(ERR_PIPE, infos);
	close(end[0]);
	if (cmd->next && dup2(end[1], 1) < 0)
		ft_error(ERR_PIPE, infos);
	close(end[1]);
	if (cmd->prev)
		close(in_fd);
	sort_cmd(cmd, infos);
}

int	ft_fork(t_infos *infos, int end[2], int in_fd, t_cmds_infos *cmd)
{
	static int	i = 0;

	if (infos->reset == 1)
	{
		i = 0;
		infos->reset = 0;
	}
	infos->pid[i] = fork();
	if (infos->pid[i] < 0)
		ft_error(ERR_FORK, infos);
	if (infos->pid[i] == 0)
		cmd_dup(cmd, infos, end, in_fd);
	i++;
	return (0);
}

int	wait_all(int *pid, int nbr, t_infos *infos)
{
	int	i;
	int	status;

	i = 0;
	while (i < nbr)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	waitpid(pid[i], &status, 0);
	if (WIFEXITED(status))
		infos->error_num = WEXITSTATUS(status);
	return (0);
}

t_cmds_infos	*ft_cmds_infosfirst(t_cmds_infos *cmds)
{
	int	i;

	i = 0;
	if (!cmds)
		return (NULL);
	while (cmds->prev != NULL)
	{
		cmds = cmds->prev;
		i++;
	}
	return (cmds);
}

int	large_execute(t_infos *infos)
{
	int	end[2];
	int	in_fd;

	in_fd = 0;
	while (infos->cmds_infos)
	{
		infos->cmds_infos = call_expand(infos, infos->cmds_infos);
		if (infos->cmds_infos->next)
			pipe(end);
		check_here_doc(infos, infos->cmds_infos);
		ft_fork(infos, end, in_fd, infos->cmds_infos);
		close(end[1]);
		if (infos->cmds_infos->prev)
			close(in_fd);
		in_fd = check_fd_heredoc(infos, end, infos->cmds_infos);
		if (infos->cmds_infos->next && g_signal_error != 3)
			infos->cmds_infos = infos->cmds_infos->next;
		else
			break ;
	}
	wait_all(infos->pid, infos->pipes, infos);
	close(in_fd);
	infos->cmds_infos = ft_cmds_infosfirst(infos->cmds_infos);
	return (0);
}
