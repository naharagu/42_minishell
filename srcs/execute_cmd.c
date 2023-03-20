/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:59:50 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/20 19:35:17 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	execute_single_cmd_helper(t_minishell *ms, t_execlist *exec)
{
	extern char	**environ;
	char		*path;
	char		**args;

	path = exec->cmd->str;
	args = create_args_array(exec);
	if (!(ft_strchr(path, '/')))
	{
		path = search_path(ms, path);
		// printf("path is %s\n", path);//
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

void	setup_pipe(t_execlist *exec)
{
	if (exec->next == NULL)
		return ;
	pipe(exec->pipe_out);
	exec->next->pipe_in[0] = exec->pipe_out[0];
	exec->next->pipe_in[1] = exec->pipe_out[1];
}

void	setup_child_pipe(t_execlist *exec)
{
	close(exec->pipe_out[0]);
	dup2(exec->pipe_in[0], STDIN_FILENO);
	if (exec->pipe_in[0] != STDIN_FILENO)
		close(exec->pipe_in[0]);
	dup2(exec->pipe_out[1], STDOUT_FILENO);
	if (exec->pipe_out[1] != STDOUT_FILENO)
		close(exec->pipe_out[1]);
}

void	setup_parent_pipe(t_execlist *exec)
{
	if (exec->pipe_in[0] != STDIN_FILENO)
		close(exec->pipe_in[0]);
	if (exec->next)
		close(exec->pipe_out[1]);
}

static void	execute_child_process(t_minishell *ms, t_execlist *exec)
{
	pid_t		pid;
	extern char	**environ;

	setup_pipe(exec);
	pid = fork();
	if (pid < 0)
		exit_error(ms, "pipe");
	else if (pid == 0)
	{
		// printf("pid is %d\n", pid);//
		setup_child_pipe(exec);
		execute_single_cmd_helper(ms, exec);
	}
	// printf("pid is %d exec is %s\n", pid, exec->cmd->str);//
	setup_parent_pipe(exec);
	if (exec->next)
		return (execute_child_process(ms, exec->next));
}

void	execute_cmd(t_minishell *ms)
{
	// pid_t	pid;
	int		status;
	//シグナルの調整が必要
	// if (ms->list->pipe == NO_PIPE)
	// 	status = execute_single_cmd(ms);
	// else
	// printf("test1!\n");
	execute_child_process(ms, ms->exec);
	wait(&status);
	//シグナルの調整が必要
}
