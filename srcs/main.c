/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 01:41:27 by akhellad          #+#    #+#             */
/*   Updated: 2023/07/25 05:54:01 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	init_infos(t_infos *infos)
{
	infos->pid = NULL;
    infos->lexers = NULL;
    infos->cmds_infos = NULL;
    infos->reset = 0;
    infos->here_doc = 0;
    global.stop_here_doc = 0;
    global.in_cmd = 0;
    global.in_here_doc = 0;
	set_path(infos);
	return (1);
}

int	main(int ac, char **av, char **env)
{
	t_infos	infos;
	if(ac != 1 || av[1])
	{
		printf("Too many arguments\n");
		return (0);
	}
	infos.envp = ft_arrdup(env);
	init_infos(&infos);
	main_loop(&infos);
	return (0);
}