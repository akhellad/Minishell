/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 05:53:43 by akhellad          #+#    #+#             */
/*   Updated: 2023/07/22 06:51:27 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_tokens    is_token(int c)
{
    int tokens[3][2] = {{'|', PIPE}, {'>', GREAT}, {'<', LESS}};

    int i;

    i = 0;
    while (i < 3)
    {
        if (tokens[i][1] == c)
            return (tokens[i][2]);
        i ++;
    }
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

int	set_token(t_infos *infos)
{
	int	i;
	int	j;

	i = 0;
	while(infos->args[i])
	{
		j = 0;
		i += skip_space(infos->args, i);
		if (is_token(infos->args[i]))
			/*handle token*/
		else
			/*read word*/
		if (j < 0)
			return (0);
		i += j;
	}
	return (1);
}