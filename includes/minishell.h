/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 01:41:30 by akhellad          #+#    #+#             */
/*   Updated: 2023/07/23 22:19:19 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/includes/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum s_tokens
{
	PIPE = 1,
	GREAT,
	TWO_GREAT,
	LESS,
	TWO_LESS,
}	t_tokens;

typedef struct  s_lexer
{
    char    *arg;
    t_tokens token;
    int		index;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct	s_infos
{
	char	*args;
	char	**paths;
	char	**envp;
	int		*pid;
	struct t_cmds_infos	*cmds_infos;
	int		pipes;
	t_lexer	*lexers;
}		t_infos;

typedef struct s_parser_infos
{
	t_lexer		*lexers;
	t_lexer		*redir;
	int			redir_nbr;
	struct s_infos		*infos;
}	t_parser_infos;

typedef struct s_cmds_infos
{
	char	**str;
	int		redir_nbr;
	char	*filename;
	t_lexer	*redir;
	struct s_cmds_infos	*next;
	struct s_cmds_infos	*prev;
}	t_cmds_infos;

/*main.c*/
int	init_infos(t_infos *infos);
int	reset_infos(t_infos *infos);
void display_tokens(t_lexer* head);

/*excute.c*/
void	execute(char *argv, char **envp);

/*history.c*/

/*utils.c*/
t_lexer *ft_newlexer(char *str, int token);
void    ft_addlexer_back(t_lexer **lexers, t_lexer *new);
char	**ft_arrdup(char **arr);
void	free_arr(char **split_arr);
int		check_quotes(char *str);
int		ft_error(int error, t_infos *infos);
int		count_args(t_lexer	*lexers);

/*parser.c*/
t_tokens    is_token(int c);
int			quotes(int i, char *str, char del);
int	set_token(t_infos *infos);

/*envp.c*/
int		set_path(t_infos *infos);

/*loop.c*/
int		main_loop(t_infos *infos);

/*parser2.c*/
int parser(t_infos *infos);

/*clear_lexer.c*/
void    ft_clearlexer(t_lexer **lexers);
void    ft_dellexer_one(t_lexer **lexers, int index);
void    ft_dellexer_first(t_lexer **lexers);
t_lexer *ft_clearlexer_one(t_lexer  **lexers);

/*errors.c*/
int	double_token_error(t_infos *infos, t_lexer *lexers, t_tokens token);
void	parser_error(int error, t_infos *infos, t_lexer *lexers);

/*redirs.c*/
void    sort_redirs(t_parser_infos *parser_infos);

#endif