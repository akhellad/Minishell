/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 05:59:08 by akhellad          #+#    #+#             */
/*   Updated: 2023/07/25 07:18:32 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*del_quotes(char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			j = 0;
			while (str[i + j] == c)
				j++;
			ft_strlcpy(&str[i], &str[i + j], strlen(str) - i);
		}
		i++;
	}
	return (str);
}

int	check_double_quotes(char *str, int i, int *quotes_nbr, int quotes)
{
	int j;

	j = i + 1;
	*quotes_nbr += 1;
	while (str[j] && str[j] != quotes)
		j++;
	if (str[j] == quotes)
		*quotes_nbr += 1;
	return (j - i);
}

int	check_quotes(char *str)
{
	int	i;
	int	j;
	int	n;

	i = 0;
	j = 0;
	n = 0;
	while (str[i])
	{
		if (str[i] == 39)
			i += check_double_quotes(str, i, &j, 39);
		if (str[i] == 34)
			i += check_double_quotes(str, i, &n, 34);
		i++;
	}
	if ((n > 0 && n % 2 != 0) || (j > 0 && j % 2 != 0))
		return (0);
	return (1);
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
