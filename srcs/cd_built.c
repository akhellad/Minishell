/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_built.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 23:48:52 by akhellad          #+#    #+#             */
/*   Updated: 2023/08/19 05:38:47 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    update_path(t_infos *infos)
{
	char	*tmp;
	
	tmp = malloc(sizeof(char) * PATH_MAX);
	if (!tmp)
		return ;
	free(infos->old_pwd);
	infos->old_pwd = ft_strdup(infos->pwd);
	if (getcwd(tmp, PATH_MAX))
	{
		free(infos->pwd);
		infos->pwd = ft_strdup(tmp);
	}
	free(tmp);
}

char    *find_equal_path(char *str, t_infos *infos)
{
    int i;

    i = 0;
    while (infos->envp[i])
    {
        if (!ft_strncmp(infos->envp[i], str, ft_strlen(str)))
			return (ft_substr(infos->envp[i], ft_strlen(str),
					ft_strlen(infos->envp[i]) - ft_strlen(str)));
        i++;
    }
	return (NULL);
}

int preset_path(t_infos *infos, char *str)
{
    char    *tmp;
    int     i;

    tmp = find_equal_path(str, infos);
	i = chdir(tmp);
	free(tmp);
	if (i != 0)
	{
		str = ft_substr(str, 0, ft_strlen(str) - 1);
		ft_putstr_fd(str, 2);
		free(str);
		ft_putendl_fd(" not set", 2);
	}
	return (i);
}

void    update_env(t_infos *infos)
{
	int		i;
	char	*tmp;

	i = 0;
	while (infos->envp[i])
	{
		if (!ft_strncmp(infos->envp[i], "PWD=", 4))
		{
			tmp = ft_strjoin("PWD=", infos->pwd);
			free(infos->envp[i]);
			infos->envp[i] = tmp;
		}
		else if (!ft_strncmp(infos->envp[i], "OLDPWD=", 7) && infos->old_pwd)
		{
			tmp = ft_strjoin("OLDPWD=", infos->old_pwd);
			free(infos->envp[i]);
			infos->envp[i] = tmp;
		}
		i++;
	}
}

int cd_built(t_infos *infos, t_cmds_infos *cmd_infos)
{
    int i;

    if (!cmd_infos->str[1])
        i = preset_path(infos, "HOME=");
    else if (!ft_strncmp(cmd_infos->str[1], "-", 1) || !ft_strncmp(cmd_infos->str[1], "..", 2))
		i = preset_path(infos, "OLDPWD=");
    else
    {
        i = chdir(cmd_infos->str[1]);
        if (i != 0)
        {
			ft_putstr_fd(cmd_infos->str[1], 2);
			perror(" ");            
        }
    }
	if (i != 0)
		return (1);
    update_path(infos);
    update_env(infos);
	return (0);
}