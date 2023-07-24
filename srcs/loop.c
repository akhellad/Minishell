/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:19:13 by akhellad          #+#    #+#             */
/*   Updated: 2023/07/24 08:48:59 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_global global;

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
	ft_cmdsinfo_clear(&infos->cmds_infos);
	free(infos->args);
	if (infos->pid)
		free(infos->pid);
	free_arr(infos->paths);
	init_infos(infos);
	main_loop(infos);
	return (1);
}

void print_parsed_elements(char **parsed_elements)
{
    if (parsed_elements == NULL)
    {
        printf("Le tableau est vide.\n");
        return;
    }

    printf("Éléments parsés :\n");
    int i = 0;
    while (parsed_elements[i] != NULL)
    {
        printf("[%d] : %s\n", i, parsed_elements[i]);
        i++;
    }
}

int	check_execute(t_infos *infos)
{
	global.in_cmd = 1;
	if (infos->pipes == 0)
		one_cmd(infos->cmds_infos, infos);
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
	if(!check_quotes(infos->args))
		return (ft_error(2, infos));
	if(!set_token(infos))
		return(ft_error(1, infos));
	parser(infos);
	call_expand(infos, infos->cmds_infos);
	print_parsed_elements(infos->cmds_infos->str);
	reset_infos(infos);
	return (0);
}