/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_infos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 07:23:43 by akhellad          #+#    #+#             */
/*   Updated: 2023/09/02 21:44:58 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cmds_infosadd_back(t_cmds_infos **lst, t_cmds_infos *new)
{
	t_cmds_infos	*tmp;

	tmp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

t_cmds_infos	*ft_cmds_infonew(char **str, int redir_nbr, \
									t_lexer *redirections)
{
	t_cmds_infos	*new;

	new = (t_cmds_infos *)malloc(sizeof(t_cmds_infos));
	if (!new)
		return (0);
	new->str = str;
	new->builtins = init_builtins(str[0]);
	new->hd_filename = NULL;
	new->redir_nbr = redir_nbr;
	new->redir = redirections;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	ft_cmdsinfo_clear(t_cmds_infos **lst)
{
	t_cmds_infos	*tmp;
	t_lexer			*redir_tmp;

	if (!*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		redir_tmp = (*lst)->redir;
		if (redir_tmp)
			ft_clearlexer(&redir_tmp);
		if ((*lst)->str)
			free_arr((*lst)->str);
		if ((*lst)->hd_filename)
			free((*lst)->hd_filename);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}
