/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 22:05:56 by akhellad          #+#    #+#             */
/*   Updated: 2023/09/03 00:40:06 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_outfile_redir(t_lexer *redir)
{
	int	fd;

	if (redir->token == TWO_GREAT)
		fd = open(redir->arg, O_CREAT | O_RDWR | O_APPEND, 0777);
	else
		fd = open(redir->arg, O_CREAT | O_RDWR | O_TRUNC, 0777);
	return (fd);
}

int	init_outfile(t_lexer *redirection)
{
	int	fd;

	fd = check_outfile_redir(redirection);
	if (fd < 0)
	{
		if (errno == EACCES)
			return (ft_error(ERR_PERM, NULL));
		return (ft_error(ERR_OUTFILE, NULL));
	}
	if (dup2(fd, 1) < 0)
		return (close(fd), ft_error(ERR_PIPE, NULL));
	return (close(fd), 0);
}

int	init_infile(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		if (errno == EACCES)
			return (ft_error(ERR_PERM, NULL));
		return (ft_error(ERR_INFILE, NULL));
	}
	if (dup2(fd, 0) < 0)
		return (close(fd), ft_error(ERR_PIPE, NULL));
	return (close(fd), 0);
}

int	init_redirs(t_cmds_infos *cmd)
{
	t_lexer	*start;

	start = cmd->redir;
	while (cmd->redir)
	{
		handle_quotes(&cmd->redir->arg);
		if (cmd->redir->token == LESS)
		{
			if (init_infile(cmd->redir->arg))
				return (1);
		}
		else if (cmd->redir->token == GREAT || cmd->redir->token == TWO_GREAT)
		{
			if (init_outfile(cmd->redir))
				return (1);
		}
		if (cmd->redir->token == TWO_LESS)
		{
			if (init_infile(cmd->hd_filename))
				return (1);
		}
		cmd->redir = cmd->redir->next;
	}
	cmd->redir = start;
	return (0);
}
