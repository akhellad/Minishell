/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 05:00:41 by akhellad          #+#    #+#             */
/*   Updated: 2023/07/24 05:50:08 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_global global;

size_t	find_equal(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i + 1);
		i++;
	}
	return (0);
}

int	expand_lengh(char *str, int j)
{
	int	i;

	i = j + 1;
	while (str[i] != '\0' && str[i] != '$' && str[i] != ' '
		&& str[i] != '\"' && str[i] != '\'' && str[i] != '=' && str[i] != '-'
		&& str[i] != ':')
		i++;
	return (i);
}

int		dollar_loop(t_infos *infos, char *str, char **tmp, int j)
{
	int		k;
	int		ret;
	char	*tmp2;
	char	*tmp3;

	k = 0;
	ret = 0;
	while (infos->envp[k])
	{
		if (ft_strncmp(str + j + 1, infos->envp[k], find_equal(infos->envp[k]) - 1) == 0
			&& expand_lengh(str, j) - j == (int)find_equal(infos->envp[k]))
		{
			tmp2 = ft_strdup(infos->envp[k] + find_equal(infos->envp[k]));
			tmp3 = ft_strjoin(*tmp, tmp2);
			free(*tmp);
			*tmp = tmp3;
			free(tmp2);
			ret = find_equal(infos->envp[k]);
		}
		k++;
	}
	if (ret == 0)
		ret = expand_lengh(str, j) - j;
	return (ret);
}


size_t	find_dollar(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (i + 1);
		i++;
	}
	return (0);
}
int		check_digit(int j, char *str)
{
	int i;

	i = j;
	if (str[j] == '$')
	{
		if (ft_isdigit(str[j + 1]) == 1)
			j += 2;
	}
	return (j - i);
}

int	handle_question(char **tmp)
{
	free(*tmp);
	*tmp = ft_itoa(global.error_num);
	return (ft_strlen(*tmp) + 1);
}

char	*char_to_str(char c)
{
	char	*str;

	str = ft_calloc(sizeof(char), 2);
	str[0] = c;
	return (str);
}

char	*handle_dollar(t_infos *infos, char *str)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = 0;
	tmp = ft_strdup("\0");
	while (str[j])
	{
		j += check_digit(j, str);
		if (str[j] == '$' && str[j + 1] == '?')
			j += handle_question(&tmp);
		else if (str[j] == '$' && (str[j + 1] != ' ' && (str[j + 1] != '"' || str[j + 2] != '\0')) && str[j + 1] != '\0')
			j += dollar_loop(infos, str, &tmp, j);
		else
		{
			tmp = char_to_str(str[j++]);
			tmp3 = ft_strjoin(tmp, tmp2);
			free(tmp);
			tmp = tmp3;
			free (tmp2);
		}
	}
	return (tmp);
}

char    **expand(t_infos *infos, char **str)
{
    int     i;
    char    *tmp;

	i = 0;
	tmp = NULL;

	while (str[i] != NULL)
	{
		if (str[i][find_dollar(str[i]) - 2] != '\'' && find_dollar(str[i]) != 0 && str[i][find_dollar(str[i])] != '\0')
		{
			tmp = handle_dollar(infos, str[i]);
			free (str[i]);
			str[i] = tmp;
		}	
		i++;
	}
	return (str);
}

char	*expand_str(t_infos *infos, char *str)
{
	char	*tmp;

	tmp = NULL;
	if (str[find_dollar(str) - 2] != '\'' && find_dollar(str) != 0
		&& str[find_dollar(str)] != '\0')
	{
		tmp = handle_dollar(infos, str);
		free(str);
		str = tmp;
	}
	return (str);
}

t_cmds_infos	*call_expand(t_infos *infos, t_cmds_infos *cmd)
{
	t_lexer	*start;

	cmd->str = expand(infos, cmd->str);
	start = cmd->redir;
	while (cmd->redir)
	{
		if (cmd->redir->token != TWO_LESS)
			cmd->redir->arg
				= expand_str(infos, cmd->redir->arg);
		cmd->redir = cmd->redir->next;
	}
	cmd->redir = start;
	return (cmd);
}