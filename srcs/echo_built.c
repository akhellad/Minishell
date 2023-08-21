/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 23:10:38 by akhellad          #+#    #+#             */
/*   Updated: 2023/08/21 13:56:51 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	printer(int i, char **str, int fd)
{
	while (str[i])
	{
		ft_putstr_fd(str[i++], fd);
		if (str[i])
			ft_putchar_fd(' ', fd);
	}
}

int	echo_built(t_infos *infos, t_cmds_infos *cmd_infos)
{
	int		i;
	int		j;
	bool	n_param;

	i = 1;
	n_param = false;
	(void) infos;
	while (cmd_infos->str[i] && cmd_infos->str[i][0] == '-' \
			&& cmd_infos->str[i][1] == 'n')
	{
		j = 1;
		while (cmd_infos->str[i][j] == 'n')
			j++;
		if (cmd_infos->str[i][j] == '\0')
			n_param = true;
		else
			break ;
		i++;
	}
	printer(i, cmd_infos->str, STDOUT_FILENO);
	if (n_param == false)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
