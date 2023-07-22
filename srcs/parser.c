/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 05:53:43 by akhellad          #+#    #+#             */
/*   Updated: 2023/07/22 19:40:31 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	sort_token(char *str, int i, t_lexer **lexers);

t_tokens    is_token(int c)
{
    static int tokens[3][2] = {
	{124, PIPE}, 
	{62, GREAT}, 
	{60, LESS}
	};

    int i;

    i = 0;
    while (i < 3)
    {
        if (tokens[i][0] == c)
            return (tokens[i][1]);
        i ++;
    }
	return (0);
}

int is_space(char c)
{
    if (c == ' ' || (c > 8 && c < 14))
        return (1);
    return (0);
}

int skip_spaces(char *str, int i)
{
    int j;

    j = 0;
    while (is_space(str[i + j]))
        j++;
    return (j);
}

int	quotes(int i, char *str, char del)
{
	int j;

	j = 0;
	if (str[i + j] == del)
	{
		while (str[i + j] != del && str[i + j])
			j ++;
		j ++; 
	}
	return (j);
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

int	words(int i, char *str, t_lexer **lexers)
{
	int j;
	
	j = 0;
	while (str[i + j] && !(is_token(str[i + j])))
	{
		j += quotes(i + j, str, 39);
		j += quotes(i + j, str, 34);
		if (is_space(str[i + j]))
			break ;
		else
			j++;
	}
	if (!add_lexer(ft_substr(str, i, j), 0, lexers))
		return (-1);
	return (j);
}

int	sort_token(char *str, int i, t_lexer **lexers)
{
	t_tokens	token;

	token = is_token(str[i]);
	if (token == GREAT && is_token(str[i + 1]) == GREAT)
	{
		if(!add_lexer(0, TWO_GREAT, lexers))
			return (-1);
		return (2);
	}
	if (token == LESS && is_token(str[i + 1]) == LESS)
	{
		if(!add_lexer(0, TWO_LESS, lexers))
			return (-1);
		return (2);
	}
	else if (token)
	{
		if (!add_lexer(0, token, lexers))
			return (-1);
		return (1);
	}
	return (0);
}

int	set_token(t_infos *infos)
{
	int	i;
	int	j;

	i = 0;
	while(infos->args[i])
	{
		j = 0;
		i += skip_spaces(infos->args, i);
		if (is_token(infos->args[i]))
			j = sort_token(infos->args, i, &infos->lexers);
		if (!is_token(infos->args[i]))
			j = words(i, infos->args, &infos->lexers);
		if (j < 0)
			return (0);
		i += j;
	}
	return (1);
}