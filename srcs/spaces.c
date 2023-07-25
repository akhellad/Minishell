/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 07:20:39 by akhellad          #+#    #+#             */
/*   Updated: 2023/07/25 07:21:12 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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