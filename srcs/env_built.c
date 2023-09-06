/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_built.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 04:54:35 by akhellad          #+#    #+#             */
/*   Updated: 2023/09/02 23:41:22 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	env_built(t_infos *infos, t_cmds_infos *cmd_infos)
{
	int	i;

	if (cmd_infos->redir)
	{
		if (init_redirs(cmd_infos))
			return (1);
	}
	i = 0;
	while (infos->envp[i])
	{
		if (find_equal(infos->envp[i]))
		{
			ft_putstr_fd(infos->envp[i], 1);
			ft_putchar_fd('\n', 1);
		}
		i++;
	}
	return (0);
}

int	pwd_built(t_infos *infos, t_cmds_infos *cmd_infos)
{
	(void) cmd_infos;
	ft_putendl_fd(infos->pwd, 1);
	return (0);
}
