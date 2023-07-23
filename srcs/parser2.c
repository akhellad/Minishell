/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 08:19:58 by akhellad          #+#    #+#             */
/*   Updated: 2023/07/23 10:38:47 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    pipes_nbr(t_lexer *lexers, t_infos *infos)
{
    t_lexer *tmp;

	tmp = lexers;
	infos->pipes = 0;
	while(tmp)
	{
		if (tmp->token == PIPE)
			infos->pipes++;
		tmp = tmp->next;
	}
	
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

int parser(t_infos *infos)
{
//    t_cmds_infos    *node;
//    t_parser_infos  parser_infos;


    infos->cmds_infos = NULL;
	pipes_nbr(infos->lexers, infos);
	if (infos->lexers->token == PIPE)
		return (double_token_error(infos, infos->lexers, infos->lexers->token));
	/*while(infos->lexers)
	{
		if (infos->lexers && infos->lexers->token == PIPE)
		{
			printf("lol");
			ft_dellexer_one(&infos->lexers, infos->lexers->index);
		if (check_pipe_errors(infos, infos->lexers->token))
			return (1);

	}*/
	return (0);
}