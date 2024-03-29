/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:54:12 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/18 21:39:06 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# define NOT_EXECUTABLE 126
# define NOT_FOUND 127
# define EXIT_ERROR 128
# define SYNTAX_ERROR 128

extern volatile sig_atomic_t	g_status;
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
	EXIT_CMD
}	t_cmd;

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
	t_redirect			type;
	int					fd_target;
	int					fd_file;
	int					fd_stashed;
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
	int					pipe_in[2];
	int					pipe_out[2];
	t_cmd				cmdtype;
	t_redirect			redtype;
	t_cmdlist			*cmd;
	t_redlist			*red;
	t_heredoc			*heredoc;
	struct s_execlist	*next;
}	t_execlist;

typedef struct s_minishell
{
	char				*line;
	size_t				cmd_size;
	t_quote				quote;
	t_mslist			*list;
	t_execlist			*exec;
	t_envlist			*env;
}	t_minishell;

//signal.c
void		set_signal_for_shell_prompt(void);
void		set_signal_for_heredoc(void);
void		set_signal_for_execution(void);
void		set_signal_for_waiting_child(void);
void		prompt_handler(int signum);
void		heredoc_handler(int signum);
void		waitchild_handler(int signum);
void		assign_dfl_handler(int signum);
void		assign_ign_handler(int signum);

//lexer.c
int			lexer(t_minishell *ms);

//bool.c
bool		is_quoted(char c, t_minishell *ms);
bool		is_space(char c);
bool		is_metachara(char c);

//parser.c
int			parser(t_minishell *ms);

//check_type.c
void		check_cmdtype(t_minishell *ms, char *str);
void		check_redtype(t_minishell *ms, char *str);
int			error_redirect(t_execlist *exec, char *cmdline);

//expansion.c
int			expansion(t_minishell *ms);
char		*get_old(char **new, char **old);
char		*get_env(t_minishell *ms, char *str);
char		*trim_quote(char *str, int c);
void		free_split(char **split);

//expansion_utils.c
bool		is_quoted_cmd(t_cmdlist *cmd, char c);
bool		is_quoted_red(t_redlist *red, char c);
int			quotedstr(char *str);
bool		is_upperchar(char c);
int			split_str(char *str);

//expand_cmd_utils.c
void		expand_cmd( t_minishell *ms, t_cmdlist *cmd, char *str);

//expand_red_utils.c
int			expand_red(t_minishell *ms, t_redlist *red, char *str);

//lexer_in_parser.c
char		**lexer_cmd(t_cmdlist *cmd, char **original);

//redirect.c
int			prepare_redirect(t_minishell *ms);
int			check_redirect(t_minishell *ms);
void		set_redirect(t_redlist *red);
void		reset_redirect(t_redlist *red);

//heredoc.c
int			run_heredoc(char *delimiter, t_redlist *red, t_minishell *ms);

//utils.c
void		init_ms(t_minishell *ms);
char		*toupper_char(char *str);
void		clear_ms(t_minishell *ms);
char		*get_errchar(size_t count_in, size_t count_out);
void		safe_close(int fd);

//mslist.c
t_mslist	*ms_lstnew(size_t len, char *str);
t_mslist	*ms_lstlast(t_mslist *lst);
void		ms_lstadd_back(t_mslist **lst, t_mslist *new);
int			ms_lstsize(t_mslist *lst);
void		ms_lstclear(t_mslist **lst);

//exec_listnew.c
t_execlist	*exec_lstnew(t_mslist *list, size_t num);
t_heredoc	*heredoc_lstnew(void);

//exec_lstclear.c
void		exec_lstclear(t_execlist **lst);
void		env_lstclear(t_envlist **lst);

//add_execlist.c
void		add_execlist(t_minishell *ms, t_mslist	*first, size_t num);
void		exec_lstadd_back(t_execlist **lst, t_execlist *new);
int			exec_lstsize(t_execlist *lst);

//add_cmdlist.c
void		add_cmdlist(t_minishell *ms, char *str);
t_cmdlist	*cmd_lstnew(char *str);
int			cmd_lstsize(t_cmdlist *lst);

//add_redlist.c
void		add_redlist(t_minishell *ms, char *str);
t_redlist	*red_lstnew(char *str);
int			red_lstsize(t_redlist *lst);

//add_envlist.c
void		add_envlist(t_minishell *ms, char *key, char *value);
t_envlist	*env_lstnew(char *key, char *value);
int			env_lstsize(t_envlist *lst);

//check_error.c
int			error_lexer(t_minishell *ms);
int			errror_parser_mslist(t_minishell *ms);
int			error_expandedred(t_redlist *red, char *original);

//print_error.c
void		exit_error(char *location);
void		exit_error_with_status(char *location, char *message, int status);
int			syntax_error(char *location, int status);
int			other_error(char *location, char *msg, int status);

//create_array.c
char		**create_env_array(t_envlist *env);
char		**create_args_array(t_execlist *exec);
size_t		get_args_size(t_execlist *exec);
void		free_arg_array(size_t argc, char **argv);

//execute.c
int			execute(t_minishell *ms);

//execute_builtin.c
int			execute_parent_process(t_minishell *ms);
int			execute_builtin(t_minishell *ms, t_execlist *exec);

//builtin
int			ft_echo(size_t argc, char **argv);
int			ft_cd(t_minishell *ms, size_t argc, char **argv);
int			ft_pwd(void);
int			ft_export(t_minishell *ms, size_t argc, char **argv);
int			ft_unset(t_minishell *ms, size_t argc, char **argv);
int			ft_env(t_minishell *ms, size_t argc);
int			ft_exit(int argc, char **argv);
void		put_error_nonvalid_env(char *cmd, char *key);
void		print_env(char *key, char *value, bool is_export);

//path.c
char		*get_and_validate_path(char *path, t_minishell *ms, \
									t_execlist *exec);

//pipe.c
void		setup_pipe(t_execlist *exec);
void		setup_child_pipe(t_execlist *exec);
void		setup_parent_pipe(t_execlist *exec);

//environ.c
void		init_env(t_minishell *ms);
bool		is_valid_env_key(char *key);
t_envlist	*get_env_from_key(t_minishell *ms, char *key);
char		*get_value_from_key(t_minishell *ms, char *key);
int			update_env_value(t_minishell *ms, char *arg);
char		*create_str_from_envlist(t_envlist *env);

//print_list.c (for test)
void		print_mslist(t_minishell *ms);
void		print_cmdline(t_minishell *ms);
void		print_execlist(t_minishell *ms);

#endif
