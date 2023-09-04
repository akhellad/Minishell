/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexers_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 05:56:46 by akhellad          #+#    #+#             */
/*   Updated: 2023/09/05 01:57:24 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lexer	*ft_newlexer(char *str, int token)
{
	t_lexer		*new;
	static int	i = 0;

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

void	ft_addlexer_back(t_lexer **lexers, t_lexer *new)
{
	t_lexer	*tmp;

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

char	*handle_incomplete_command(char *input)
{
	char	*new_input;
	char	*tmp;

	if (!input)
		return (NULL);
	if (input[strlen(input) - 1] == '|')
	{
		new_input = readline("\033[34m> \033[0m");
		if (!new_input)
			return (NULL);
		tmp = ft_strjoin(input, new_input);
		free(input);
		free(new_input);
		input = tmp;
	}
	return (input);
}

int	handle_partial_command(t_infos *infos)
{
	char	*full_cmd;

	full_cmd = handle_incomplete_command(infos->args);
	if (!full_cmd)
	{
		free(infos->args);
		infos->args = NULL;
		return (1);
	}
	infos->args = full_cmd;
	return (0);
}
