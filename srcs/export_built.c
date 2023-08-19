/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_built.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 22:10:45 by akhellad          #+#    #+#             */
/*   Updated: 2023/08/19 05:46:26 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_valid_identifier(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '[' || c == ']'
		|| c == '\'' || c == '\"' || c == ' ' || c == ',' || c == '.'
		|| c == ':' || c == '/' || c == '{' || c == '}' || c == '+'
		|| c == '^' || c == '%' || c == '#' || c == '@' || c == '!'
		|| c == '~'
		|| c == '=' || c == '-' || c == '?' || c == '&' || c == '*');
}

void	solo_export(t_infos *infos)
{
	int	i;

	i = 0;
	while (infos->envp[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(infos->envp[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}

int	variable_exist(t_infos *infos, char *str)
{
	int	i;

	i = 0;
	if (str[find_equal(str)] == '\"')
		hd_del_quotes(str, '\"');
	if (str[find_equal(str)] == '\'')
		hd_del_quotes(str, '\'');
	while (infos->envp[i])
	{
		if (ft_strncmp(infos->envp[i],
				str, find_equal(infos->envp[i])) == 0)
		{
			free(infos->envp[i]);
			infos->envp[i] = ft_strdup(str);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_parameter(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[0]))
		return (export_err(str));
	if (find_equal(str) == 0)
		return (EXIT_FAILURE);
	if (str[0] == '=')
		return (export_err(str));
	while (str[i] != '=')
	{
		if (check_valid_identifier(str[i]))
			return (export_err(str));
		i++;
	}
	return (EXIT_SUCCESS);
}

char	**whileloop_add_var(char **arr, char **rtn, char *str)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		if (arr[i + 1] == NULL)
		{
			rtn[i] = ft_strdup(str);
			rtn[i + 1] = ft_strdup(arr[i]);
		}
		else
			rtn[i] = ft_strdup(arr[i]);
		if (rtn[i] == NULL)
		{
			free_arr(rtn);
			return (rtn);
		}
		i++;
	}
	return (rtn);
}

char	**add_var(char **arr, char *str)
{
	char	**rtn;
	size_t	i;

	i = 0;
	if (str[find_equal(str)] == '\"')
		hd_del_quotes(str, '\"');
	if (str[find_equal(str)] == '\'')
		hd_del_quotes(str, '\'');
	while (arr[i] != NULL)
		i++;
	rtn = ft_calloc(sizeof(char *), i + 2);
	if (!rtn)
		return (NULL);
	i = 0;
	whileloop_add_var(arr, rtn, str);
	return (rtn);
}

int	export_built(t_infos *infos, t_cmds_infos *s_cmds_infos)
{
	char	**tmp;
	int		i;

	i = 1;
	if (!s_cmds_infos->str[1] || s_cmds_infos->str[1][0] == '\0')
		solo_export(infos);
	else
	{
		while (s_cmds_infos->str[i])
		{
			if (check_parameter(s_cmds_infos->str[i]) == 0
				&& variable_exist(infos, s_cmds_infos->str[i]) == 0)
			{
				if (s_cmds_infos->str[i])
				{
					tmp = add_var(infos->envp, s_cmds_infos->str[i]);
					free_arr(infos->envp);
					infos->envp = tmp;
				}
			}
			i++;
		}
	}
	return (EXIT_SUCCESS);
}