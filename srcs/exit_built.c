/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 21:34:55 by akhellad          #+#    #+#             */
/*   Updated: 2023/07/28 22:20:35 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_infos(t_infos *infos)
{
	free_arr(infos->paths);
	free_arr(infos->envp);
	free(infos->args);
	ft_cmdsinfo_clear(&infos->cmds_infos);
	free(infos->pwd);
	free(infos->old_pwd);
	if (infos->pipes)
		free(infos->pid);
}

int	is_str_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void    find_exit_code(char **str)
{
    int exit_code;
    
    if (!str[1])
        exit_code = 0;
	else if (is_str_digit(str[1]))
		exit_code = ft_atoi(str[1]);
	else
	{
		ft_putstr_fd(str[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exit_code = 255;
	}
	free_arr(str);
	ft_putendl_fd("exit", 2);
	exit(exit_code);
}

int exit_built(t_infos *infos, t_cmds_infos *cmd_infos)
{
    char    **str;

    if (cmd_infos->str[1] && cmd_infos->str[2])
    {
        ft_putendl_fd("exit: too many arguments", 2);
        return (1);
    }
    str = ft_arrdup(cmd_infos->str);
    free_infos(infos);
    find_exit_code(str);
    return (0);
}