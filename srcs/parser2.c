/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 08:19:58 by akhellad          #+#    #+#             */
/*   Updated: 2023/07/24 00:45:29 by akhellad         ###   ########.fr       */
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

t_cmds_infos	*ft_cmds_infonew(char **str, int redir_nbr, t_lexer *redirections)
{
	t_cmds_infos	*new;

	new = (t_cmds_infos *)malloc(sizeof(t_cmds_infos));
	if (!new)
		return (0);
	new->str = str;
	new->filename = NULL;
	new->redir_nbr = redir_nbr;
	new->redir = redirections;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_cmds_infos	*init_cmd(t_parser_infos *parser_infos)
{
	char	**args;
	int		i;
	int		args_nbr;
	t_lexer	*tmp;

	i = 0;
	sort_redirs(parser_infos);
	args_nbr = count_args(parser_infos->lexers);
	args = ft_calloc(args_nbr + 1, sizeof(char *));
	if (!args)
		parser_error(1, parser_infos->infos, parser_infos->lexers);
	tmp = parser_infos->lexers;
	while (args_nbr > 0)
	{
		if (tmp->arg)
		{
			args[i++] = ft_strdup(tmp->arg);
			ft_dellexer_one(&parser_infos->lexers, tmp->index);
			tmp = parser_infos->lexers;
		}
		args_nbr--;
	}
	return (ft_cmds_infonew(args, parser_infos->redir_nbr, parser_infos->redir));
}

t_parser_infos	init_parser_infos(t_lexer *lexers, t_infos *infos)
{
	t_parser_infos	parser_infos;

	parser_infos.lexers = lexers;
	parser_infos.redir = NULL;
	parser_infos.redir_nbr = 0;
	parser_infos.infos = infos;
	return (parser_infos);
}

void    pipes_nbr(t_lexer *lexers, t_infos *infos)
{
    t_lexer *tmp;

	tmp = lexers;
	infos->pipes = 0;
	while(tmp)
	{
		if (tmp->token == PIPE)
			infos->pipes++;
		tmp = tmp->next;
	}
	
}

int	check_pipe_errors(t_infos *infos, t_tokens token)
{
	if (token == PIPE)
	{
		double_token_error(infos, infos->lexers,
			infos->lexers->token);
		return (1);
	}
	if (!infos->lexers)
	{
		parser_error(0, infos, infos->lexers);
		return (1);
	}
	return (0);
}

int parser(t_infos *infos)
{
	t_cmds_infos    *node;
	t_parser_infos  parser_infos;


    infos->cmds_infos = NULL;
	pipes_nbr(infos->lexers, infos);
	if (infos->lexers->token == PIPE)
		return (double_token_error(infos, infos->lexers, infos->lexers->token));
	while(infos->lexers)
	{
		if (infos->lexers && infos->lexers->token == PIPE)
			ft_dellexer_one(&infos->lexers, infos->lexers->index);
		if (check_pipe_errors(infos, infos->lexers->token))
			return (1);
		parser_infos = init_parser_infos(infos->lexers, infos);
		node = init_cmd(&parser_infos);
		if (!node)
			parser_error(0, infos, parser_infos.lexers);
		if (!infos->cmds_infos)
			infos->cmds_infos = node;
		else
			ft_cmds_infosadd_back(&infos->cmds_infos, node);
		infos->lexers = parser_infos.lexers;
	}
	return (0);
}