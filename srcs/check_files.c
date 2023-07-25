/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 22:05:56 by akhellad          #+#    #+#             */
/*   Updated: 2023/07/25 00:59:04 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_outfile_redir(t_lexer *redir)
{
	int	fd;

	if (redir->token == TWO_GREAT)
		fd = open(redir->arg, O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		fd = open(redir->arg, O_CREAT | O_RDWR | O_TRUNC, 0644);
	return (fd);
}

int	init_outfile(t_lexer *redirection)
{
	int	fd;

	fd = check_outfile_redir(redirection);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: outfile: Error\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (fd > 0 && dup2(fd, STDOUT_FILENO) < 0)
	{
		ft_putstr_fd("minishell: pipe error\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (fd > 0)
		close(fd);
	return (EXIT_SUCCESS);
}

int     init_infile(char *file)
{
    int fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("infile: No such file or directory\n", 2);
		return (1);
	}
	if (fd > 0 && dup2(fd, 0) < 0)
	{
		ft_putstr_fd("pipe error\n", 2);
		return (1);		
	}
	if (fd > 0)
		close (fd);
	return (0);
}

int     init_redirs(t_cmds_infos *cmd)
{
    t_lexer	*start;

	start = cmd->redir;
    while (cmd->redir)
    {
        if (cmd->redir->token == LESS)
        {		
			if (init_infile(cmd->redir->arg))
				return (1);
        }
		else if (cmd->redir->token == GREAT || cmd->redir->token == TWO_GREAT)
		{
			if (init_outfile(cmd->redir));
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