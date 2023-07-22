/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 01:41:30 by akhellad          #+#    #+#             */
/*   Updated: 2023/07/22 06:32:32 by akhellad         ###   ########.fr       */
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

typedef enum s_tokens
{
	PIPE = 1,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS,
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
	t_lexer	*lexers;
}		t_infos;


/*excute.c*/
void	execute(char *argv, char **envp);

/*history.c*/
void	add_history(char *cmd, int history_count);

#endif