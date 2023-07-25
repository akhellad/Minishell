/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexers_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 05:56:46 by akhellad          #+#    #+#             */
/*   Updated: 2023/07/25 07:19:34 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lexer *ft_newlexer(char *str, int token)
{
    t_lexer *new;
    static int i = 0;

    new = (t_lexer *)malloc(sizeof(t_lexer));
    if (!new)
        return (0);
    new->arg = str;
    new->token = token;
    new->index = i++;
    new->prev = NULL;
    new->next = NULL;
    return (new);
}

void    ft_addlexer_back(t_lexer **lexers, t_lexer *new)
{
    t_lexer *tmp;

    tmp = *lexers;
    if (*lexers == NULL)
    {
        *lexers = new;
        return ;
    }
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new;
    new->prev = tmp;
}

int	add_lexer(char *str, t_tokens token, t_lexer **lexers)
{
	t_lexer	*lexer;

	lexer = ft_newlexer(str, token);
	if (!lexer)
		return (0);
	ft_addlexer_back(lexers, lexer);
	return (1);
}