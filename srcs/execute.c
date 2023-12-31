/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 03:00:03 by akhellad          #+#    #+#             */
/*   Updated: 2023/11/16 10:33:14 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	exec_error(char *str)
{
	DIR	*dir;
	int	fd;
	int	value;

	fd = open(str, O_WRONLY);
	dir = opendir(str);
	ft_putstr_fd(str, STDERR_FILENO);
	if (!ft_strchr(str, '/'))
		ft_putendl_fd(": command not found", STDERR_FILENO);
	else if (fd == -1 && !dir)
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	else if (fd == -1 && dir)
		ft_putendl_fd(": Is a directory", STDERR_FILENO);
	else if (fd != -1 && !dir)
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
	if (!ft_strchr(str, '/') || (fd == -1 && !dir))
		value = 127;
	else
		value = 126;
	if (dir)
		closedir(dir);
	if (fd > 0)
		close(fd);
	return (value);
}

int	execute(t_cmds_infos *cmd, t_infos *infos)
{
	int		i;
	char	*final_cmd;

	i = 0;
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
	return (exec_error(cmd->str[0]));
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
	int	fd[2];

	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	infos->cmds_infos = call_expand(infos, infos->cmds_infos);
	if (cmd->builtins != NULL)
	{
		infos->error_num = one_cmd_bultin(infos, fd[0], fd[1], cmd);
		return ;
	}
	close(fd[0]);
	close(fd[1]);
	check_here_doc(infos, cmd);
	pid = fork();
	if (pid < 0)
		ft_error(ERR_FORK, infos);
	if (pid == 0)
		sort_cmd(cmd, infos);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		infos->error_num = WEXITSTATUS(status);
}
