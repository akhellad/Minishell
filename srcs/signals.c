/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 21:41:42 by akhellad          #+#    #+#             */
/*   Updated: 2023/08/21 14:09:23 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	event_hook(void)
{
	return (EXIT_SUCCESS);
}

void	signal_handler(int signum)
{
	(void)signum;
	if (!g_global.in_here_doc)
		ft_putstr_fd("\n", STDERR_FILENO);
	if (g_global.in_cmd)
	{
		g_global.stop_here_doc = 1;
		rl_replace_line("", 0);
		rl_redisplay();
		rl_done = 1;
		return ;
	}
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_init(void)
{
	rl_event_hook = event_hook;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler);
}
