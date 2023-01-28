/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:54:12 by shimakaori        #+#    #+#             */
/*   Updated: 2023/01/28 12:52:46 by shimakaori       ###   ########.fr       */
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
	END_S_QUOTE,
	D_QUOTE,
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
	PIPE,
	SEMICOLON,
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

typedef struct s_mslist
{
	char			*str;
	t_pipe			pipe;
	t_redirect		redirect;
	t_cmd			cmd;
	struct s_mslist	*next;
	struct s_mslist	*prev;
}	t_mslist;

typedef struct s_cmdlist
{
	t_cmd				cmdtype;
	char				*str;
	//char				*quote;
	struct s_cmdlist	*next;
}	t_cmdlist;

typedef struct s_redlist
{
	t_redirect			redtype;
	char				*str;
	//char				*quot;
	int					fd;
	struct s_redlist	*next;
}	t_redlist;

typedef struct s_envlist
{
	char				*key;
	char				*value;
	struct s_envlist	*next;
}	t_envlist;

typedef struct s_execlist
{
	char				**cmdline;
	t_cmdlist			*cmd;
	t_redlist			*red;
	t_envlist			*env;
	struct s_execlist	*next;
}	t_execlist;

typedef struct s_minishell
{
	int			exit_status;
	char		*input;
	t_quote		quote;
	t_mslist	*list;
	t_execlist	*exec;
}	t_minishell;

// main.c

//lexer.c
void		lexer(t_minishell *ms);

//parser.c
void		parser(t_minishell *ms);

//utils.c
t_minishell	*init_struct_ms(t_minishell *ms);
void		get_pathname(void);

//mslist.c
t_mslist	*ms_lstnew(size_t len, char *str);
t_mslist	*ms_lstlast(t_mslist *lst);
void		ms_lstadd_back(t_mslist **lst, t_mslist *new);
int			ms_lstsize(t_mslist *lst);
void		ms_lstclear(t_mslist **lst);

//execlist.c
t_execlist	*exec_lstnew(t_minishell *ms, size_t num);

#endif
