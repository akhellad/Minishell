/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 20:24:50 by akhellad          #+#    #+#             */
/*   Updated: 2023/07/22 20:43:03 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**find_path(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	return (paths);
}

int set_path(t_infos *infos)
{
	int		i;
	char	*part_path;

	infos->paths = find_path(infos->envp);
	i = 0;
	while (infos->paths[i])
	{
        if (ft_strncmp(&infos->paths[i][ft_strlen(infos->paths[i]) - 1],
		"/", 1) != 0)
        {
		    part_path = ft_strjoin(infos->paths[i], "/");
		    free(infos->paths[i]);
            infos->paths[i] = part_path;
        }
		i++;
	}
	return (0);
}