/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 06:53:48 by akhellad          #+#    #+#             */
/*   Updated: 2023/07/22 07:01:03 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lexer *ft_newlexer(char *str, int token)
{
    t_lexer *new;
    static int i;

    i = 0;
    new = (t_lexer *)malloc(sizeof(t_lexer));
    if (!new)
        return (0);
    new->arg = str;
    new->token = token;
    new->index = i++;
    new->prev = NULL;
    new->next = NULL;
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