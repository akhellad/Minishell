/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 01:41:27 by akhellad          #+#    #+#             */
/*   Updated: 2023/07/28 01:22:35 by akhellad         ###   ########.fr       */
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
	g_global.stop_here_doc = 0;
	g_global.in_cmd = 0;
	g_global.in_here_doc = 0;
	set_path(infos);
	return (1);
}

int	init_pwd(t_infos *infos)
{
	int	i;

	i = 0;
	while (infos->envp[i])
	{
		if (!ft_strncmp(infos->envp[i], "PWD=", 4))
			infos->pwd = ft_substr(infos->envp[i],
					4, ft_strlen(infos->envp[i]) - 4);
		if (!ft_strncmp(infos->envp[i], "OLDPWD=", 7))
			infos->old_pwd = ft_substr(infos->envp[i],
					7, ft_strlen(infos->envp[i]) - 7);
		i++;
	}
	return (1);
}

int	main(int ac, char **av, char **env)
{
	t_infos	infos;

	if (ac != 1 || av[1])
	{
		printf("Too many arguments\n");
		return (0);
	}
	infos.envp = ft_arrdup(env);
	init_pwd(&infos);
	init_infos(&infos);
	main_loop(&infos);
	return (0);
}
