/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 01:41:30 by akhellad          #+#    #+#             */
/*   Updated: 2023/07/22 21:26:15 by akhellad         ###   ########.fr       */
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
	t_lexer	*lexers;
}		t_infos;

/*main.c*/
int	init_infos(t_infos *infos);

/*excute.c*/
void	execute(char *argv, char **envp);

/*history.c*/

/*utils.c*/
t_lexer *ft_newlexer(char *str, int token);
void    ft_addlexer_back(t_lexer **lexers, t_lexer *new);
char	**ft_arrdup(char **arr);
void	free_arr(char **split_arr);

/*parser.c*/
t_tokens    is_token(int c);
int			quotes(int i, char *str, char del);
int	set_token(t_infos *infos);

/*envp.c*/
int		set_path(t_infos *infos);

/*loop.c*/
int		main_loop(t_infos *infos);

#endif