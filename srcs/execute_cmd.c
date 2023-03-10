/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:59:50 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/10 13:51:36 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include "../include/minishell.h"

void	child_process(t_minishell *ms, char *str);
char	*serch_path(char *file);
void	free_argv(t_minishell *ms, char **argv);

void	execute_cmd(t_minishell *ms)
{
	// char		**argv;
	pid_t		pid;
	int			wstatus;

	pid = fork();
	// argv = ft_calloc(2, sizeof(char **));
	// if (!argv)
	// 	exit_error(ms, "malloc");
	// if (ms->exec->cmd->str)
	// 	argv[0] = ft_strdup(ms->exec->cmd->str);
	// else if (!(ms->exec->cmd->str) && ms->exec->red->str)
	// 	argv[0] = ft_strdup(ms->exec->red->str);
	// argv[1] = NULL;
	if (pid < 0)
		exit_error(ms, "pipe");
	else if (pid == 0)
		child_process(ms, ms->exec->cmdline[0]);
	else if (pid > 0)
	{
		wait(&wstatus);
		ms->exit_status = WEXITSTATUS(wstatus);
	}
	// free_argv(ms, argv);
}

void	child_process(t_minishell *ms, char *cmdline)
{
	extern char	**environ;
	char		*path;

	path = cmdline;
	if (!(ft_strchr(path, '/')))
	{
		path = serch_path(path);
		// printf("test: path is %s\n", path);
		// printf("test: str is %s\n", str);
		// printf("test: env is %s\n", environ[0]);
		if (!path || access(path, F_OK) < 0)
			return ;
		if (execve(path, &ms->exec->cmdline[0], environ) == -1)
			return ;
	}
	else if (execve(path, &ms->exec->cmdline[0], environ) == -1)
		return ;
}

char	*serch_path(char *file)
{
	char	**path;
	char	*value;
	size_t	i;

	value = getenv("PATH");
	path = ft_split(value, ':');
	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], "/");
		path[i] = ft_strjoin(path[i], file);
		if (!(access(path[i], X_OK)))
			return (path[i]);
		else
			free(path[i]);
		i++;
	}
	return (NULL);
}
