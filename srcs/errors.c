/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 09:13:07 by akhellad          #+#    #+#             */
/*   Updated: 2023/07/29 00:29:57 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parser_error(char *error, t_infos *infos, t_lexer *lexers)
{
	ft_clearlexer(&lexers);
	ft_error(error, infos);
}

int	double_token_error(t_infos *infos, t_lexer *lexers,
	t_tokens token)
{
	ft_putstr_fd("syntax error near unexpected token ",
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

int	ft_error(char *message, t_infos *infos)
{
	ft_putstr_fd(message, STDERR_FILENO);
	if (infos)
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
