/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 23:40:21 by akhellad          #+#    #+#             */
/*   Updated: 2023/08/19 03:08:30 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int (*init_builtins(char *str))(t_infos *infos, t_cmds_infos *cmd_infos)
{
    static void *builtins[7][2] = 
    {
        {"cd", cd_built},
        {"env", env_built},
        {"pwd", pwd_built},
        {"exit", exit_built},
        {"unset", unset_built},
        {"export", export_built},
        {"echo", echo_built},
    };
    int         i;

    i = 0;
    while (i < 6)
    {
        if (str)
        {
            if (!ft_strncmp(builtins[i][0], str, ft_strlen((builtins[i][0]))))
                return (builtins[i][1]);
        }
        i++;
    }
    return (NULL);
}