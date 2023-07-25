/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 21:42:38 by akhellad          #+#    #+#             */
/*   Updated: 2023/07/25 01:46:34 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	add_new_redirs(t_lexer *tmp, t_parser_infos *parser_infos)
{
	t_lexer	*node;
	int		index_1;
	int		index_2;

	node = ft_newlexer(ft_strdup(tmp->next->arg), tmp->token);
	if (!node)
		parser_error(1, parser_infos->infos, parser_infos->lexers);
	ft_addlexer_back(&parser_infos->redir, node);
	index_1 = tmp->index;
	index_2 = tmp->next->index;
	ft_dellexer_one(&parser_infos->lexers, index_1);
	ft_dellexer_one(&parser_infos->lexers, index_2);
	parser_infos->redir_nbr++;
	return (0);
}

void	sort_redirs(t_parser_infos *parser_infos)
{
	t_lexer	*tmp;

	tmp = parser_infos->lexers;
	while (tmp && tmp->token == 0)
		tmp = tmp->next;
	if (!tmp || tmp->token == PIPE)
		return ;
	if (!tmp->next)
	{
		parser_error(0, parser_infos->infos, parser_infos->lexers);
		return ;
	}
	if (tmp->next->token)
		double_token_error(parser_infos->infos,
			parser_infos->lexers, tmp->next->token);
	if (tmp->next && (tmp->token >= GREAT
			&& tmp->token <= TWO_LESS))
		add_new_redirs(tmp, parser_infos);
	sort_redirs(parser_infos);
}