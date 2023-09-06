/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 01:41:30 by akhellad          #+#    #+#             */
/*   Updated: 2023/09/07 00:57:40 by agaley           ###   ########lyon.fr   */
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
# include <limits.h>
# include <errno.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/types.h>
# include <dirent.h>

typedef enum s_tokens
{
	PIPE = 1,
	GREAT,
	TWO_GREAT,
	LESS,
	TWO_LESS,
}	t_tokens;

typedef struct s_lexer
{
	char			*arg;
	t_tokens		token;
	int				index;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct s_infos
{
	char				*args;
	char				**paths;
	char				**envp;
	int					*pid;
	int					here_doc;
	struct s_cmds_infos	*cmds_infos;
	int					pipes;
	int					reset;
	t_lexer				*lexers;
	char				*pwd;
	char				*old_pwd;
	int					export_var;
	int					in_cmd;
	int					in_here_doc;
	int					stop_here_doc;
	int					error_num;
}		t_infos;

typedef struct s_parser_infos
{
	t_lexer				*lexers;
	t_lexer				*redir;
	int					redir_nbr;
	struct s_infos		*infos;
}	t_parser_infos;

typedef struct s_cmds_infos
{
	char				**str;
	int					redir_nbr;
	char				*hd_filename;
	t_lexer				*redir;
	int					(*builtins)(t_infos *, struct s_cmds_infos *);
	struct s_cmds_infos	*next;
	struct s_cmds_infos	*prev;
}	t_cmds_infos;

extern int	g_signal_error;
int	(*init_builtins(char *str))(t_infos *infos, t_cmds_infos *cmds_infos);

/* Error codes */
# define ERR_NEWLINE 0
# define ERR_MEMORY 1
# define ERR_QUOTES 2
# define ERR_PARSER 3
# define ERR_PIPE 4
# define ERR_FORK 5
# define ERR_OUTFILE 6
# define ERR_INFILE 7
# define ERR_PATH 8
# define ERR_PERM 9

/*main.c*/
int				init_infos(t_infos *infos);
int				reset_infos(t_infos *infos);

/*excute.c*/
void			one_cmd(t_cmds_infos *cmd, t_infos *infos);
void			sort_cmd(t_cmds_infos *cmd, t_infos *infos);

/*utils.c*/
char			**ft_arrdup(char **arr);
void			free_arr(char **split_arr);
int				count_args(t_lexer	*lexers);

/*lexers.c*/
t_tokens		is_token(int c);
int				set_token(t_infos *infos);

/*envp.c*/
int				set_path(t_infos *infos);

/*loop.c*/
int				main_loop(t_infos *infos);
void			print_parser_infos(t_parser_infos *parser_infos);
t_cmds_infos	*call_expand(t_infos *infos, t_cmds_infos *cmd);

/*parser.c*/
int				parser(t_infos *infos);

/*clear_lexer.c*/
void			ft_clearlexer(t_lexer **lexers);
void			ft_dellexer_one(t_lexer **lexers, int index);
void			ft_dellexer_first(t_lexer **lexers);
t_lexer			*ft_clearlexer_one(t_lexer **lexers);

/*errors.c*/
int				double_token_error(t_infos *infos, t_lexer *lexers, \
								t_tokens token);
void			parser_error(int error, t_infos *infos, t_lexer *lexers);
int				ft_error(int error, t_infos *infos);
int				check_pipe_errors(t_infos *infos, t_tokens token);
int				export_err(char *c);

/*redirs.c*/
void			sort_redirs(t_parser_infos *parser_infos);

/*expand.c*/
char			**expand(t_infos *infos, char **str);
char			*expand_str(t_infos *infos, char *str);

/*check_files.c*/
int				init_redirs(t_cmds_infos *cmd);

/*here_doc.c*/
int				check_here_doc(t_infos *infos, t_cmds_infos *cmd);
int				check_fd_heredoc(t_infos *infos, int end[2], t_cmds_infos *cmd);

/*large_execute.c*/
int				large_execute(t_infos *infos);

/*execute_utils.c*/
char			**resplit_str(char **double_arr);
int				one_cmd_bultin(t_infos *infos, int fd_in, int fd_out, \
								t_cmds_infos *cmd);

/*lexers_utils.c*/
t_lexer			*ft_newlexer(char *str, int token);
void			ft_addlexer_back(t_lexer **lexers, t_lexer *new);
int				add_lexer(char *str, t_tokens token, t_lexer **lexers);
int				handle_partial_command(t_infos *infos);

/*quotes.c*/
int				check_quotes(char *str);
int				check_double_quotes(char *str, int i, int *quotes_nbr, \
									int quotes);
int				quotes(int i, char *str, char del);
void			handle_quotes(char **str);
int				find_quote(char *str);

/*spaces.c*/
int				skip_spaces(char *str, int i);
int				is_space(char c);

/*cmds_infos.c*/
void			ft_cmds_infosadd_back(t_cmds_infos **lst, t_cmds_infos *new);
t_cmds_infos	*ft_cmds_infonew(char **str, int redir_nbr, \
								t_lexer *redirections);
void			ft_cmdsinfo_clear(t_cmds_infos **lst);

/*expand_utils.c*/
char			*char_to_str(char c);
int				handle_question(char **tmp, t_infos *infos);
int				check_digit(int j, char *str);
int				expand_lengh(char *str, int j);
size_t			find_equal(char *str);

/*cd_built.c*/
int				cd_built(t_infos *infos, t_cmds_infos *cmd_infos);

/*env_built.c*/
int				env_built(t_infos *infos, t_cmds_infos *cmd_infos);
int				pwd_built(t_infos *infos, t_cmds_infos *cmd_infos);

/*exit_build.c*/
int				exit_built(t_infos *infos, t_cmds_infos *cmd_infos);

/*signals.c*/
void			signal_init(void);
void			check_error_signal(t_infos *infos);

/*unset_built.c*/
int				unset_built(t_infos *infos, t_cmds_infos *cmd_infos);

/*echo_built.c*/
int				echo_built(t_infos *infos, t_cmds_infos *cmd_infos);

/*export_built.c*/
int				export_built(t_infos *infos, t_cmds_infos *cmds_infos);

/*export_utils.c*/
void			solo_export(t_infos *infos);
int				check_valid_identifier(char c);

#endif