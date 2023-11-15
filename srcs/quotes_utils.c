/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:40:02 by akhellad          #+#    #+#             */
/*   Updated: 2023/11/15 12:41:41 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	quote_type(char *str, int index)
{
	int	single_quote;
	int	double_quote;
	int	i;

	single_quote = 0;
	double_quote = 0;
	i = 0;
	while (str[i] && i < index)
	{
		if (str[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (str[i] == '\"' && !single_quote)
			double_quote = !double_quote;
		i++;
	}
	if (single_quote) 
		return (1);
	if (double_quote) 
		return (2);
	return (0);
}

char	*append_char(char *str, char c)
{
	char	append_str[2];
	char	*new_str;

	append_str[0] = c;
	append_str[1] = '\0';
	new_str = ft_strjoin(str, append_str);
	free(str);
	return (new_str);
}

int	is_valid_variable_char(char c)
{
	return (c && c != ' ' && c != '"' && c != '\'');
}
