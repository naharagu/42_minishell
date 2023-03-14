/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:59:50 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/14 21:16:14 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include "../include/minishell.h"

static void	free_path(char **path)
{
	size_t	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
}

static char	*search_path(t_minishell *ms, char *file)
{
	char	**path;
	char	*value;
	char	*res;
	size_t	i;

	value = getenv("PATH");
	path = ft_split(value, ':');
	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], "/");
		path[i] = ft_strjoin(path[i], file);
		if (!(access(path[i], X_OK)))
		{
			res = ft_strdup(path[i]);
			if (!res)
				exit_error(ms, "malloc");
			free_path(path);
			return (res);
		}
		i++;
	}
	free_path(path);
	return (NULL);
}

static void	child_process(t_minishell *ms, t_execlist *exec)
{
	extern char	**environ;
	char		*path;
	char		**args;

	path = exec->cmd->str;
	args = create_args_array(exec);
	printf("test2!\n");
	int i = 0;
	while (args)
	{
		printf("arg is %s\n", args[i]);
		i++;
	}

	if (!(ft_strchr(path, '/')))
	{
		path = search_path(ms, path);
		printf("path is %s\n", path);
		if (!path)
			return ;
		if (access(path, F_OK) < 0)
			return (free(path));
		if (execve(path, args, environ) == -1)
			return (free(path));
	}
	else if (execve(path, args, environ) == -1)
		return ;
}

void	execute_child_process(t_minishell *ms)
{
	pid_t	pid;
	int		wstatus;
	t_execlist	tmp;

	// size_t	cmd_index;
	// cmd_index = 0;
	while (ms->exec)
	{
		pid = fork();
		printf("test1!\n");
		if (pid < 0)
			exit_error(ms, "pipe");
		else if (pid == 0)
			child_process(ms, ms->exec);
		ms->exec = ms->exec->next;
	}
	wait(&wstatus);
	ms->exit_status = WEXITSTATUS(wstatus);
}

void	execute_cmd(t_minishell *ms)
{
	pid_t	pid;
	int		status;

	//シグナルの調整が必要
	// if (ms->list->pipe == NO_PIPE)
	// 	status = execute_one_cmd(ms);
	// else
	execute_child_process(ms);
	//シグナルの調整が必要
}
