/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:19:13 by akhellad          #+#    #+#             */
/*   Updated: 2023/07/22 21:33:29 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void display_history(void)
{
    HIST_ENTRY** history_entries = history_list();
    int i = 0;

    if (history_entries == NULL)
        return;
    while (history_entries[i] != NULL) 
	{
        printf("%d: %s\n", i + 1, history_entries[i]->line);
        i++;
    }
    free(history_entries);
}

int	reset_infos(t_infos *infos)
{
	free(infos->args);
	if(infos->pid)
		free(infos->pid);
	free_arr(infos->paths);
	init_infos(infos);
	main_loop(infos);
	return (1);
}

int	main_loop(t_infos *infos)
{
	char *tmp;
	
	infos->args = readline("minishell>");
	tmp = ft_strtrim(infos->args, " ");
	free(infos->args);
	infos->args = tmp;
	if (!infos->args)
	{
		ft_putendl_fd("exit", 1);
		exit(0);
	}
	if (infos->args[0] == '\0')
		return (reset_infos(infos));
	add_history(infos->args);
	display_history();
	reset_infos(infos);
	return (0);
}