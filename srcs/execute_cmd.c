/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:59:50 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/20 12:45:44 by naharagu         ###   ########.fr       */
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

void	init_pipe_fd(int fd[2])
{
	fd[0] = STDIN_FILENO;
	fd[1] = STDOUT_FILENO;
}

void	close_fd(int fd[2])
{
	if (fd[0] != STDIN_FILENO)
		close(fd[0]);
	if (fd[1] != STDOUT_FILENO)
		close(fd[1]);
}

static void	execute_single_cmd_helper(t_minishell *ms, t_execlist *exec)
{
	extern char	**environ;
	char		*path;
	char		**args;

	path = exec->cmd->str;
	args = create_args_array(exec);
	// printf("arg[0] is %s\n", args[0]);
	// printf("arg[1] is %s\n", args[1]);
	// printf("arg[2] is %s\n", args[2]);
	if (!(ft_strchr(path, '/')))
	{
		path = search_path(ms, path);
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

static void	execute_single_cmd(t_minishell *ms, t_execlist *exec, int left_pipe[2],
		int right_pipe[2])
{
	pid_t		pid;
	extern char	**environ;
	int			current_pipe[2];

	current_pipe[0] = left_pipe[0];
	current_pipe[1] = right_pipe[1];
	pid = fork();
	// printf("fork pid is %d\n", pid);
	if (pid < 0)
		exit_error(ms, "pipe");
	else if (pid == 0)
	{
		dup2(current_pipe[0], STDIN_FILENO);
		dup2(current_pipe[1], STDOUT_FILENO);
		close_fd(current_pipe);
		close_fd(left_pipe);
		close_fd(right_pipe);
		execute_single_cmd_helper(ms, exec);
	}
}

void	execute_child_process(t_minishell *ms)
{
	int			wstatus;
	t_execlist	*tmp_exec;
	int			left_pipe[2];
	int			right_pipe[2];

	tmp_exec = ms->exec;
	init_pipe_fd(left_pipe);
	while (tmp_exec)
	{
		if (tmp_exec->next)
			pipe(right_pipe);
		else
			init_pipe_fd(right_pipe);
		execute_single_cmd(ms, tmp_exec, left_pipe, right_pipe);
		close_fd(left_pipe);
		left_pipe[0] = right_pipe[0];
		left_pipe[1] = right_pipe[1];
		tmp_exec = tmp_exec->next;
	}
	wait(&wstatus);
	ms->exit_status = WEXITSTATUS(wstatus);
}

void	execute_cmd(t_minishell *ms)
{
	// pid_t	pid;
	// int		status;
	//シグナルの調整が必要
	// if (ms->list->pipe == NO_PIPE)
	// 	status = execute_single_cmd(ms);
	// else
	// printf("test1!\n");
	execute_child_process(ms);
	//シグナルの調整が必要
}
