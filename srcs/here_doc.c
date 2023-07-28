/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 23:22:21 by akhellad          #+#    #+#             */
/*   Updated: 2023/07/28 04:32:14 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	display_here_doc(t_lexer *hd_infos, int quotes, t_infos *infos, \
					char *filename)
{
	int		fd;
	char	*arg;

	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0664);
	arg = readline("\033[1;34m> \033[0m");
	while (arg && ft_strncmp(hd_infos->arg, arg, ft_strlen(hd_infos->arg)) \
			&& !g_global.stop_here_doc)
	{
		if (quotes == 0)
			arg = expand_str(infos, arg);
		write(fd, arg, ft_strlen(arg));
		write(fd, "\n", 1);
		free(arg);
		arg = readline("\033[1;34m> \033[0m");
	}
	free(arg);
	if (g_global.stop_here_doc || !arg)
		return (1);
	close(fd);
	return (0);
}

int	check_fd_heredoc(t_infos *infos, int end[2], t_cmds_infos *cmd)
{
	int	in_fd;

	if (infos->here_doc)
	{
		close(end[0]);
		in_fd = open(cmd->hd_filename, O_RDONLY);
	}
	else
		in_fd = end[0];
	return (in_fd);
}

int	here_doc(t_infos *infos, t_lexer *hd_infos, char *filename)
{
	int	quotes;
	int	exit_code;

	exit_code = 0;
	if ((hd_infos->arg[0] == '\"'
			&& hd_infos->arg[ft_strlen(hd_infos->arg) - 1] == '\"')
		|| (hd_infos->arg[0] == '\''
			&& hd_infos->arg[ft_strlen(hd_infos->arg) - 1] == '\''))
		quotes = 1;
	else
		quotes = 0;
	del_quotes(hd_infos->arg, '\'');
	del_quotes(hd_infos->arg, '\"');
	g_global.stop_here_doc = 0;
	g_global.in_here_doc = 1;
	exit_code = display_here_doc(hd_infos, quotes, infos, filename);
	g_global.in_here_doc = 0;
	infos->here_doc = 1;
	return (exit_code);
}

char	*here_doc_filename(void)
{
	static int	i = 0;
	char		*index;
	char		*filename;

	index = ft_itoa(i++);
	filename = ft_strjoin("tmp/.tmp_heredoc_file_", index);
	free(index);
	return (filename);
}

int	check_here_doc(t_infos *infos, t_cmds_infos *cmd)
{
	t_lexer	*first;
	int		exit_code;

	first = cmd->redir;
	exit_code = 0;
	while (cmd->redir)
	{
		if (cmd->redir->token == TWO_LESS)
		{
			if (cmd->hd_filename)
				free(cmd->hd_filename);
			cmd->hd_filename = here_doc_filename();
			exit_code = here_doc(infos, cmd->redir, cmd->hd_filename);
			if (exit_code)
			{
				g_global.error_num = 1;
				return (reset_infos(infos));
			}
		}
		cmd->redir = cmd->redir->next;
	}
	cmd->redir = first;
	return (0);
}
