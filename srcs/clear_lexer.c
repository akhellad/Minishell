/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clearlexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 08:53:12 by akhellad          #+#    #+#             */
/*   Updated: 2023/07/23 09:19:29 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lexer	*ft_clearlexer_one(t_lexer **lexers)
{
	if ((*lexers)->arg)
	{
		free((*lexers)->arg);
		(*lexers)->arg = NULL;
	}
	free(*lexers);
	*lexers = NULL;
	return (NULL);
}

void	 ft_dellexer_first(t_lexer **lexers)
{
	t_lexer	*node;

	node = *lexers;
	*lexers = node->next;
	ft_clearlexer_one(&node);
	if (*lexers)
		(*lexers)->prev = NULL;
}

void	ft_dellexer_one(t_lexer **lexers, int key)
{
	t_lexer	*node;
	t_lexer	*prev;
	t_lexer	*start;

	start = *lexers;
	node = start;
	if ((*lexers)->index == key)
	{
		 ft_dellexer_first(lexers);
		return ;
	}
	while (node && node->index != key)
	{
		prev = node;
		node = node->next;
	}
	if (node)
		prev->next = node->next;
	else
		prev->next = NULL;
	if (prev->next)
		prev->next->prev = prev;
	ft_clearlexer_one(&node);
	*lexers = start;
}

void	ft_clearlexer(t_lexer **lexers)
{
	t_lexer	*tmp;

	if (!*lexers)
		return ;
	while (*lexers)
	{
		tmp = (*lexers)->next;
		if ((*lexers)->arg)
			free((*lexers)->arg);
		free(*lexers);
		*lexers = tmp;
	}
	*lexers = NULL;
}