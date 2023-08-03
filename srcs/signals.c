/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 01:05:18 by agaley            #+#    #+#             */
/*   Updated: 2023/08/04 01:30:30 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	signal_handler(int signum)
{
	signal(signum, signal_handler);
	if (signum == SIGQUIT)
		return ;
	if (signum == SIGINT)
		printf("TODO : relancer le prompt minishell>\n");
}

void	signal_init(void)
{
	signal(SIGQUIT, signal_handler);
	signal(SIGINT, signal_handler);
}
