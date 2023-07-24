/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 03:00:03 by akhellad          #+#    #+#             */
/*   Updated: 2023/07/24 08:56:24 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sort_cmd(t_cmds_infos *cmd, t_infos *infos)
{
	int	exit_code;

	exit_code = 0;
	if (cmd->redir)
		if ()
}

void	one_cmd(t_cmds_infos *cmd, t_infos *infos)
{
	int	pid;
	int	status;

	infos->cmds_infos = call_expand(infos, infos->cmds_infos);
	pid = fork();
	if (pid < 0)
		ft_error(5, infos);
	if (pid == 0)
		
}
