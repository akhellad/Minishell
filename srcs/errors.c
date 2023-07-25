/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 09:13:07 by akhellad          #+#    #+#             */
/*   Updated: 2023/07/25 22:38:40 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parser_error(int error, t_infos *infos, t_lexer *lexers)
{
	ft_clearlexer(&lexers);
	ft_error(error, infos);
}

int	double_token_error(t_infos *infos, t_lexer *lexers,
	t_tokens token)
{
	ft_putstr_fd(">syntax error near unexpected token ",
		STDERR_FILENO);
	if (token == GREAT)
		ft_putstr_fd("'>'\n", STDERR_FILENO);
	else if (token == TWO_GREAT)
		ft_putstr_fd("'>>'\n", STDERR_FILENO);
	else if (token == LESS)
		ft_putstr_fd("'<'\n", STDERR_FILENO);
	else if (token == TWO_LESS)
		ft_putstr_fd("'<<'\n", STDERR_FILENO);
	else if (token == PIPE)
		ft_putstr_fd("'|'\n", STDERR_FILENO);
	else
		ft_putstr_fd("\n", STDERR_FILENO);
	ft_clearlexer(&lexers);
	reset_infos(infos);
	return (EXIT_FAILURE);
}

int	ft_error(int error, t_infos *infos)
{
	ft_putstr_fd(">", STDERR_FILENO);
	if (error == 0)
		ft_putstr_fd("syntax error near unexpected token 'newline'\n",
			STDERR_FILENO);
	else if (error == 1)
		ft_putstr_fd("memory error: unable to assign memory\n", STDERR_FILENO);
	else if (error == 2)
		ft_putstr_fd("syntax error: unable to locate closing quotation\n",
			STDERR_FILENO);
	else if (error == 3)
		ft_putstr_fd("Parser problem\n", STDERR_FILENO);
	else if (error == 4)
		ft_putstr_fd("Failed to create pipe\n", STDERR_FILENO);
	else if (error == 5)
		ft_putstr_fd("Failed to fork\n", STDERR_FILENO);
	else if (error == 6)
		ft_putstr_fd("outfile: Error\n", STDERR_FILENO);
	else if (error == 7)
		ft_putstr_fd("infile: No such file or directory\n", STDERR_FILENO);
	else if (error == 8)
		ft_putendl_fd("Path does not exist", STDERR_FILENO);
	reset_infos(infos);
	return (EXIT_FAILURE);
}

int	check_pipe_errors(t_infos *infos, t_tokens token)
{
	if (token == PIPE)
	{
		double_token_error(infos, infos->lexers,
			infos->lexers->token);
		return (1);
	}
	if (!infos->lexers)
	{
		parser_error(0, infos, infos->lexers);
		return (1);
	}
	return (0);
}
