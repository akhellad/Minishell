/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 23:40:21 by akhellad          #+#    #+#             */
/*   Updated: 2023/07/28 00:11:31 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int (*init_builtins(char *str))(t_infos *infos, t_cmds_infos *cmd_infos)
{
    static void *builtins[1][2] = 
    {
        {"cd", cd_built},
    };
    int         i;

    i = 0;
    while (i < 1)
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