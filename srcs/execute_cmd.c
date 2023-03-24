/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:59:50 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/24 21:01:53y naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_child_process_helper(t_minishell *ms, t_execlist *exec)
{
	extern char	**environ;
	char		*path;
	char		**args;

	if (exec->redtype != NO_REDIRECT)
		set_redirect(exec->red);
	path = exec->cmd->str;
	args = create_args_array(exec);
	if (!(ft_strchr(path, '/')))
	{
		path = search_path(ms, path);
		if (!path)
			exit(127); //shoule be 127
		if (access(path, F_OK) < 0)
			return (free(path));
		if (execve(path, args, environ) == -1)
			return (free(path));
		if (exec->redtype != NO_REDIRECT)
			reset_redirect(exec->red);
	}
	else if (execve(path, args, environ) == -1)
	{
		if (exec->redtype != NO_REDIRECT)
			reset_redirect(exec->red);
	}
}

static pid_t	execute_child_process(t_minishell *ms, t_execlist *exec)
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
		execute_child_process_helper(ms, exec);
	}
	// printf("pid is %d exec is %s\n", pid, exec->cmd->str);//
	setup_parent_pipe(exec);
	if (exec->next)
		return (execute_child_process(ms, exec->next));
	return (pid);
}

int	wait_child_process(t_minishell *ms, pid_t last_pid)
{
	pid_t	wait_result;
	int		status;
	int		wstatus;

	while (1)
	{
		wait_result = wait(&wstatus);
		if (wait_result == last_pid)
		{
			if (WIFSIGNALED(wstatus))
				status = 128 + WTERMSIG(wstatus);
			else
				status = WEXITSTATUS(wstatus);
		}
		else if (wait_result < 0)
		{
			if (errno == ECHILD)
				break ;
			else if (errno == EINTR)
				continue ;
			else
				exit_error(ms, "wait");
		}
	}
	return (status);
}

int	execute_cmd(t_minishell *ms)
{
	int		status;
	pid_t	last_pid;

	if (ms->exec->cmd == NULL)
		return (1);
	if (ms->list->pipe == NO_PIPE && ms->exec->cmdtype != NO_CMD)
	{
		// printf("start parent process\n");//
		status = execute_parent_process(ms);
	}
	else
	{
		last_pid = execute_child_process(ms, ms->exec);
		status = wait_child_process(ms, last_pid);
	}
	return (status);
	//シグナルの調整が必要
}
