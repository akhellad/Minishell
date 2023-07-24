/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 01:41:27 by akhellad          #+#    #+#             */
/*   Updated: 2023/07/24 01:58:47 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void display_tokens(t_lexer* head) {
    t_lexer* current = head;

    printf("Contenu de la liste : ");
    while (current != NULL) {
        if (current->token != 0) {
            switch (current->token) {
                case PIPE:
                    printf("| ");
                    break;
                case GREAT:
                    printf("> ");
                    break;
                case TWO_GREAT:
                    printf(">> ");
                    break;
                case LESS:
                    printf("< ");
                    break;
                case TWO_LESS:
                    printf("<< ");
                    break;
                default:
                    break;
            }
        }
        else if (head->arg)
            printf("%s\n", head->arg);
        printf("\n");
        current = current->next;
    }
//	printf("\n");
}

int	init_infos(t_infos *infos)
{
	infos->pid = NULL;
	set_path(infos);
	return (1);
}

int	main(int ac, char **av, char **env)
{
	t_infos	infos;
	if(ac != 1 || av[1])
	{
		printf("Too many arguments\n");
		return (0);
	}
	infos.envp = ft_arrdup(env);
	init_infos(&infos);
	main_loop(&infos);
	return (0);
}