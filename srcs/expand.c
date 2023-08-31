/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 05:00:41 by akhellad          #+#    #+#             */
/*   Updated: 2023/08/31 02:01:48 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	dollar_loop(t_infos *infos, char *str, char **tmp, int j)
{
	int		k;
	int		ret;
	char	*tmp2;
	char	*tmp3;

	k = 0;
	ret = 0;
	while (infos->envp[k])
	{
		if (ft_strncmp(str + j + 1, infos->envp[k], \
			find_equal(infos->envp[k]) - 1) == 0
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
			j += handle_question(&tmp, infos);
		else if (str[j] == '$' && (str[j + 1] != ' ' && (str[j + 1] != '"' \
				|| str[j + 2] != '\0')) && str[j + 1] != '\0')
			j += dollar_loop(infos, str, &tmp, j);
		else
		{
			tmp2 = char_to_str(str[j++]);
			tmp3 = ft_strjoin(tmp, tmp2);
			free(tmp);
			tmp = tmp3;
			free (tmp2);
		}
	}
	return (tmp);
}

char	**expand(t_infos *infos, char **str)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = NULL;
	while (str[++i] != NULL)
	{
		if (find_dollar(str[i]) != 0 && str[i][find_dollar(str[i]) - 2] != '\''
			&& str[i][find_dollar(str[i])] != '\0')
		{
			tmp = handle_dollar(infos, str[i]);
			free (str[i]);
			str[i] = ft_strdup(tmp);
			free(tmp);
		}
		if (ft_strncmp(str[0], "export", ft_strlen(str[0]) - 1) != 0)
		{
			str[i] = handle_quotes(str[i]);
		}
	}
	return (str);
}

char	*expand_str(t_infos *infos, char *str)
{
	char	*tmp;

	tmp = NULL;
	if (find_dollar(str) != 0 && str[find_dollar(str) - 2] != '\''
		&& str[find_dollar(str)] != '\0')
	{
		tmp = handle_dollar(infos, str);
		free(str);
		str = tmp;
	}
	return (str);
}
