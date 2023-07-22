/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 01:41:27 by akhellad          #+#    #+#             */
/*   Updated: 2023/07/22 04:25:21 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;

	int history_count;
	char	*line;

	history_count = 0;
	while(1)
	{
		ft_putstr_fd("minishell>", 0);
		line = get_next_line(0);
		pid_t	pid;
		pid = fork();
		if (pid < 0)
			return (1);
		else if (pid == 0)
		{
			execute(line, env);
			add_history(line, history_count);
		}
		else
			waitpid(pid, 0, 0);
		free(line);
	}
	return (0);
}