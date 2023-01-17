/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:54:12 by shimakaori        #+#    #+#             */
/*   Updated: 2023/01/16 12:46:46 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <limits.h>
# include <stdbool.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <signal.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <termcap.h> 
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

// # define 

typedef enum e_quote
{
	NO_QUOTE,
	S_QUOTE,
	D_QUOTE,
	END_S_QUOTE,
	END_D_QUOTE,
}	t_quote;

typedef enum e_redirect
{
	NO_REDIRECT,
	INPUT,
	OUTPUT,
	HERE_DOC,
	APPEND
}	t_redirect;

typedef enum e_pipe
{
	NO_PIPE,
	READ,
	WRITE,
	READ_WRITE
}	t_pipe;

typedef enum e_cmd
{
	NO_CMD,
	ECHO_CMD,
	CD_CMD,
	PWD_CMD,
	EXPORT_CMD,
	UNSET_CMD,
	ENV_CMD,
	EXIT_CMD
}	t_cmd;

typedef struct s_minishell
{
	int		exit_status;
	char	*input;
	int		quote;
}	t_minishell;

typedef struct s_mslist
{
	char			*str;
	int				pipe;
	int				redirect;
	int				cmd;
	struct s_mslist	*next;
	struct s_mslist	*prev;
}	t_mslist;

// main.c

//init.c
t_minishell	*init_struct_ms(t_minishell *ms);
t_mslist	*init_mslist(t_mslist *list);

//mslist.c
t_mslist	*ms_lstnew(size_t len, char *str);
t_mslist	*ms_lstlast(t_mslist *lst);
void		ms_lstadd_front(t_mslist **lst, t_mslist *new);
void		ms_lstadd_back(t_mslist **lst, t_mslist *new);
int			ms_lstsize(t_mslist *lst);

#endif
