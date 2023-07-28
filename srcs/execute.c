/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 03:00:03 by akhellad          #+#    #+#             */
/*   Updated: 2023/07/28 04:10:20 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cmd_not_found(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	return (127);
}

int	execute(t_cmds_infos *cmd, t_infos *infos)
{
	int		i;
	char	*final_cmd;

	i = 0;
	cmd->str = resplit_str(cmd->str);
	if (!access(cmd->str[0], F_OK))
		execve(cmd->str[0], cmd->str, infos->envp);
	while (infos->paths[i])
	{
		final_cmd = ft_strjoin(infos->paths[i], cmd->str[0]);
		if (!access(final_cmd, F_OK))
			execve(final_cmd, cmd->str, infos->envp);
		free(final_cmd);
		i ++;
	}
	return (cmd_not_found(cmd->str[0]));
}

void	sort_cmd(t_cmds_infos *cmd, t_infos *infos)
{
	int	exit_code;

	exit_code = 0;
	if (cmd->redir)
		if (init_redirs(cmd))
			exit (1);
	if (cmd->builtins != NULL)
	{
		exit_code = cmd->builtins(infos, cmd);
		exit(exit_code);
	}
	if (cmd->str[0][0] != '\0')
		exit_code = execute(cmd, infos);
	exit(exit_code);
}

void	one_cmd(t_cmds_infos *cmd, t_infos *infos)
{
	int	pid;
	int	status;

	infos->cmds_infos = call_expand(infos, infos->cmds_infos);
	if (cmd->builtins == cd_built)
	{
		g_global.error_num = cmd->builtins(infos, cmd);
		return ;
	}
	check_here_doc(infos, cmd);
	pid = fork();
	if (pid < 0)
		ft_error(ERR_FORK, infos);
	if (pid == 0)
		sort_cmd(cmd, infos);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_global.error_num = WEXITSTATUS(status);
}
