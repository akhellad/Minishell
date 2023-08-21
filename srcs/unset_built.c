/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_built.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 23:38:56 by akhellad          #+#    #+#             */
/*   Updated: 2023/08/21 14:10:06 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**set_new_env(char **env, char **tmp, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i] != NULL)
	{
		if (!(ft_strncmp(env[i], str, find_equal(env[i]) - 1) == 0 \
			&& env[i][ft_strlen(str)] == '='))
		{
			tmp[j] = ft_strdup(env[i]);
			if (tmp[j] == NULL)
			{
				free_arr(tmp);
				return (tmp);
			}
			j++;
		}
		i++;
	}
	return (tmp);
}

char	**unset_var(char **env, char *var)
{
	char	**tmp;
	size_t	i;

	i = 0;
	while (env[i] != NULL)
		i++;
	tmp = ft_calloc(sizeof(char *), i + 1);
	if (!tmp)
		return (NULL);
	tmp = set_new_env(env, tmp, var);
	return (tmp);
}

int	check_unset_error(t_cmds_infos *cmd_infos)
{
	if (!cmd_infos->str[1])
	{
		ft_putendl_fd("unset: not enough arguments", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (find_equal(cmd_infos->str[1]))
	{
		ft_putendl_fd("unset: invalid parameter name", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	unset_built(t_infos *infos, t_cmds_infos *cmd_infos)
{
	char	**tmp;

	if (check_unset_error(cmd_infos))
		return (EXIT_FAILURE);
	else
	{
		tmp = unset_var(infos->envp, cmd_infos->str[1]);
		free_arr(infos->envp);
		infos->envp = tmp;
	}
	return (EXIT_SUCCESS);
}
