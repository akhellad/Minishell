/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:19:13 by akhellad          #+#    #+#             */
/*   Updated: 2023/07/25 07:30:55 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_global global;

int	reset_infos(t_infos *infos)
{
	ft_cmdsinfo_clear(&infos->cmds_infos);
	free(infos->args);
	if (infos->pid)
		free(infos->pid);
	free_arr(infos->paths);
	init_infos(infos);
	infos->reset = 1;
	main_loop(infos);
	return (1);
}

int	check_execute(t_infos *infos)
{
	global.in_cmd = 1;
	if (infos->pipes == 0)
		one_cmd(infos->cmds_infos, infos);
	else
	{
		infos->pid = ft_calloc(sizeof(int), infos->pipes + 2);
		if (!infos->pid)
			return (ft_error(1, infos));
		large_execute(infos);
	}
	global.in_cmd = 0;
	return (0);
}

int	main_loop(t_infos *infos)
{
	char *tmp;
	
	infos->args = readline("minishell>");
	tmp = ft_strtrim(infos->args, " ");
	free(infos->args);
	infos->args = tmp;
	if (!infos->args)
	{
		ft_putendl_fd("exit", 1);
		exit(0);
	}
	if (infos->args[0] == '\0')
		return (reset_infos(infos));
	add_history(infos->args);
	if(!check_quotes(infos->args))
		return (ft_error(2, infos));
	if(!set_token(infos))
		return(ft_error(1, infos));
	parser(infos);
	check_execute(infos);
	reset_infos(infos);
	return (0);
}