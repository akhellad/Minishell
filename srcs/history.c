/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 04:18:28 by akhellad          #+#    #+#             */
/*   Updated: 2023/07/22 04:26:41 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#define HISTORY_SIZE 100

void	add_history(char *cmd, int history_count)
{
	char history[100][100]; 

	if (history_count < HISTORY_SIZE)
	{
		ft_strlcpy(history[history_count], cmd, ft_strlen(cmd));
		history_count++;
	}
}