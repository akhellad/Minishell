/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 06:53:48 by akhellad          #+#    #+#             */
/*   Updated: 2023/07/25 06:00:39 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		count_args(t_lexer	*lexers)
{
	t_lexer	*tmp;
	int		i;

	i = 0;
	tmp = lexers;
	while (tmp && tmp->token != PIPE)
	{
		if (tmp->index >= 0)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

void	free_arr(char **split_arr)
{
	int	i;

	i = 0;
	while (split_arr[i])
	{
		free(split_arr[i]);
		i++;
	}
	free(split_arr);
}

char	**ft_arrdup(char **arr)
{
	char	**tmp;
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	tmp = ft_calloc(sizeof(char *), i + 1);
	if (!tmp)
		return (NULL);
	i = 0;
	while (arr[i] != NULL)
	{
		tmp[i] = ft_strdup(arr[i]);
		if (tmp[i] == NULL)
		{
			free_arr(tmp);
			return (tmp);
		}
		i++;
	}
	return (tmp);
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