/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 06:53:48 by akhellad          #+#    #+#             */
/*   Updated: 2023/07/23 02:12:48 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lexer *ft_newlexer(char *str, int token)
{
    t_lexer *new;
    static int i;

    i = 0;
    new = (t_lexer *)malloc(sizeof(t_lexer));
    if (!new)
        return (0);
    new->arg = str;
    new->token = token;
    new->index = i++;
    new->prev = NULL;
    new->next = NULL;
    return (new);
}

void    ft_addlexer_back(t_lexer **lexers, t_lexer *new)
{
    t_lexer *tmp;

    tmp = *lexers;
    if (*lexers == NULL)
    {
        *lexers = new;
        return ;
    }
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new;
    new->prev = tmp;
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

int	check_double_quotes(char *str, int i, int *quotes_nbr, int quotes)
{
	int j;

	j = i + 1;
	*quotes_nbr += 1;
	while (str[j] && str[j] != quotes)
		j++;
	if (str[j] == quotes)
		*quotes_nbr += 1;
	return (j - i);
}

int	check_quotes(char *str)
{
	int	i;
	int	j;
	int	n;

	i = 0;
	j = 0;
	n = 0;
	while (str[i])
	{
		if (str[i] == 39)
			i += check_double_quotes(str, i, &j, 39);
		if (str[i] == 34)
			i += check_double_quotes(str, i, &n, 34);
		i++;
	}
	if ((n > 0 && n % 2 != 0) || (j > 0 && j % 2 != 0))
		return (0);
	return (1);
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

int	ft_error(int error, t_infos *infos)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (error == 0)
		ft_putstr_fd("syntax error near unexpected token 'newline'\n",
			STDERR_FILENO);
	else if (error == 1)
		ft_putstr_fd("memory error: unable to assign memory\n", STDERR_FILENO);
	else if (error == 2)
		ft_putstr_fd("syntax error: unable to locate closing quotation\n",
			STDERR_FILENO);
	else if (error == 3)
		ft_putstr_fd("Parser problem\n", STDERR_FILENO);
	else if (error == 4)
		ft_putstr_fd("Failed to create pipe\n", STDERR_FILENO);
	else if (error == 5)
		ft_putstr_fd("Failed to fork\n", STDERR_FILENO);
	else if (error == 6)
		ft_putstr_fd("outfile: Error\n", STDERR_FILENO);
	else if (error == 7)
		ft_putstr_fd("infile: No such file or directory\n", STDERR_FILENO);
	else if (error == 8)
		ft_putendl_fd("Path does not exist", STDERR_FILENO);
	reset_infos(infos);
	return (EXIT_FAILURE);
}