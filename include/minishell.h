/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:54:12 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/16 15:55:23 by shimakaori       ###   ########.fr       */
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

typedef enum e_quote
{
	NO_QUOTE,
	S_QUOTE,
	END_S_QUOTE,
	D_QUOTE,
	END_D_QUOTE
}	t_quote;

typedef enum e_redirect
{
	NO_REDIRECT,
	OUTPUT,
	APPEND,
	INPUT,
	HERE_DOC
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
	EXIT_CMD,
	LS_CMD,
	SPC_CMD,
	OTHER_CMD
}	t_cmd;

typedef enum e_fd
{
	STD_IN,
	STD_OUT,
	STD_ERR,
	FILE_1,
	FILE_2
}	t_fd;

typedef enum e_sig
{
	DEFAULT,
	HEREDOC
}	t_sig;

typedef struct s_mslist
{
	char				*str;
	t_pipe				pipe;
	struct s_mslist		*next;
}	t_mslist;

typedef struct s_cmdlist
{
	char				*str;
	t_quote				quote;
	struct s_cmdlist	*next;
}	t_cmdlist;

typedef struct s_redlist
{
	char				*str;
	t_quote				quote;
	struct s_redlist	*next;
}	t_redlist;

typedef struct s_envlist
{
	char				*key;
	char				*value;
	struct s_envlist	*next;
}	t_envlist;

typedef struct s_heredoc
{
	char				*docline;
	char				*expand;
	char				*delimiter;
	t_quote				quote;
}	t_heredoc;

typedef struct s_execlist
{
	char				**cmdline;
	t_cmd				cmdtype;
	t_redirect			redtype;
	int					std_fd;
	int					err_fd;
	t_cmdlist			*cmd;
	t_redlist			*red;
	t_envlist			*env;
	t_heredoc			*heredoc;
	struct s_execlist	*next;
}	t_execlist;

typedef struct s_minishell
{
	int					exit_status;
	char				*startline;
	char				*line;
	t_quote				quote;
	t_mslist			*list;
	t_execlist			*exec;
}	t_minishell;

typedef struct s_argv
{
	int					argc;
	char				**argv;
}	t_argv;

// main.c
void		minishell(t_minishell *ms);

//interpret.c
void		interpret(t_minishell *ms);

//signal.c
void		handle_signal(t_minishell *ms, int signum, t_sig flag);
void		ignore_signal(t_minishell *ms, int signum);
void		init_signal(t_minishell *ms, int signum);

//lexer.c
void		lexer(t_minishell *ms);

//bool.c
bool		is_quoted(char c, t_minishell *ms);
bool		is_space(char c);
bool		is_metachara(char c);

//parser.c
void		parser(t_minishell *ms);

//check_type.c
void		check_cmdtype(t_minishell *ms, char *str);
void		check_redtype(t_minishell *ms, char *str);

//expansion.c
void		expansion(t_minishell *ms);

//redirect.c
void		redirect(t_minishell *ms);

//red_out.c
void		red_out(t_minishell *ms, t_execlist *exec, t_redlist *red);

//red_append.c
void		red_append(t_minishell *ms, t_execlist	*exec, t_redlist *red);

//red_in.c
void		red_in(t_minishell *ms, t_redlist *red);

//red_heredoc.c
void		red_heredoc(t_minishell *ms, t_execlist *exec, t_redlist *red);

//cmd_exec.c
void		cmd_exec(t_minishell *ms);
void		exec_command(t_execlist	*exec);
void		read_fd(t_minishell *ms, int fd);

//utils.c
t_minishell	*init_struct_ms(void);
char		*toupper_char(char *str);
void		check_pipe(t_minishell *ms, char *str);
void		all_free(t_minishell *ms);

//mslist.c
t_mslist	*ms_lstnew(size_t len, char *str);
t_mslist	*ms_lstlast(t_mslist *lst);
void		ms_lstadd_back(t_mslist **lst, t_mslist *new);
int			ms_lstsize(t_mslist *lst);
void		ms_lstclear(t_mslist **lst);

//exec_listnew.c
t_execlist	*exec_lstnew(t_minishell *ms, t_mslist *list, size_t num);
t_cmdlist	*cmd_lstnew(t_minishell *ms, t_cmdlist *cmd);
t_redlist	*red_lstnew(t_minishell *ms, t_redlist *red);

//execlist.c
void		exec_lstadd_back(t_execlist **lst, t_execlist *new);
int			exec_lstsize(t_execlist *lst);
int			red_lstsize(t_redlist *lst);
int			cmd_lstsize(t_cmdlist *lst);

//exec_lstclear.c
void		exec_lstclear(t_execlist **lst);

//error.c
void		error_lexer(t_minishell *ms);
void		error_parser_mslist(t_minishell *ms);
void		error_parser_execlist(t_minishell *ms);
void		error_expansion(t_minishell *ms, t_execlist *exec, size_t i);

//print_error.c
void		exit_error(t_minishell *ms, char *location);
void		syntax_error(t_minishell *ms, char *location, int status);
void		other_error(t_minishell *ms, char *location, char *msg, int status);

//ft_exit.c
void		ft_exit(t_minishell *ms, int argc, char **argv);

//list_to_argv.c
t_argv		*list_to_argv(t_minishell *ms, t_execlist *exec);
t_argv		*init_argv(t_minishell *ms);
void		free_argv(t_argv *argv);

//print_list.c (for test)
void		print_mslist(t_minishell *ms);
void		print_execlist(t_minishell *ms);
void		print_cmdredlist(t_minishell *ms);

#endif
