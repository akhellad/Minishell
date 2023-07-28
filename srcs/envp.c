/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 20:24:50 by akhellad          #+#    #+#             */
/*   Updated: 2023/07/28 04:26:03 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_path(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5));
		i++;
	}
	return (ft_strdup("\0"));
}

int	set_path(t_infos *infos)
{
	int		i;
	char	*long_path;
	char	*part_path;

	long_path = find_path(infos->envp);
	infos->paths = ft_split(long_path, ':');
	free(long_path);
	i = 0;
	while (infos->paths[i])
	{
		if (ft_strncmp(&infos->paths[i][ft_strlen(infos->paths[i]) - 1], \
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
