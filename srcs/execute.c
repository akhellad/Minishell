/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 03:00:03 by akhellad          #+#    #+#             */
/*   Updated: 2023/07/25 03:37:09 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*join_split_str(char **split_str, char *new_str)
{
	char	*tmp;
	char	*add_space;
	int		i;

	tmp = ft_strdup(split_str[0]);
	i = 1;
	while (split_str[i])
	{
		new_str = tmp;
		add_space = ft_strjoin(new_str, " ");
		free(new_str);
		tmp = ft_strjoin(add_space, split_str[i]);
		free(add_space);
		i++;
	}
	new_str = tmp;
	return (new_str);
}

char	**resplit_str(char **double_arr)
{
	char	**ret;
	char	*joined_str;

	joined_str = join_split_str(double_arr, NULL);
	free_arr(double_arr);
	ret = ft_split(joined_str, ' ');
	free(joined_str);
	joined_str = join_split_str(ret, NULL);
	free_arr(ret);
	ret = ft_split(joined_str, ' ');
	free(joined_str);
	return (ret);
}

int		execute(t_cmds_infos *cmd, t_infos *infos)
{
	int		i;
	char	*final_cmd;

	i = 0;
	cmd->str = resplit_str(cmd->str);
	printf("%s\n", cmd->str[0]);
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
}

void	sort_cmd(t_cmds_infos *cmd, t_infos *infos)
{
	int	exit_code;

	exit_code = 0;
	if (cmd->redir)
		if (init_redirs(cmd))
			exit (1);
	if (cmd->str[0][0] != '\0')
		exit_code = execute(cmd, infos);
	exit(exit_code);
}

void	one_cmd(t_cmds_infos *cmd, t_infos *infos)
{
	int	pid;
	int	status;

	infos->cmds_infos = call_expand(infos, infos->cmds_infos);
	check_here_doc(infos, cmd);
	pid = fork();
	if (pid < 0)
		ft_error(5, infos);
	if (pid == 0)
		sort_cmd(cmd, infos);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		global.error_num = WEXITSTATUS(status);
}
