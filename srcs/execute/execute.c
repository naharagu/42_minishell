/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 17:53:43 by naharagu          #+#    #+#             */
/*   Updated: 2023/03/29 21:47:46 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_non_builtin(t_minishell *ms, t_execlist *exec)
{
	char		**env;
	char		*path;
	char		**args;

	if (exec->redtype != NO_REDIRECT)
		set_redirect(exec->red);
	if (!exec->cmd)
		exit(NOT_FOUND);
	path = exec->cmd->str;
	env = create_env_array(ms, ms->env);
	args = create_args_array(ms, exec);
	if (!(ft_strchr(path, '/')))
		path = search_path(ms, path);
	validate_path(path, exec);
	execve(path, args, env);
	if (exec->redtype != NO_REDIRECT)
		reset_redirect(exec->red);
}

static pid_t	execute_child_process(t_minishell *ms, t_execlist *exec)
{
	pid_t		pid;

	setup_pipe(exec);
	pid = fork();
	if (pid < 0)
		exit_error(ms, "pipe");
	else if (pid == 0)
	{
		setup_child_pipe(exec);
		set_signal_handlers_for_execution(ms);
		if (exec->cmdtype == NO_CMD)
			execute_non_builtin(ms, exec);
		else
			exit(execute_builtin(ms, exec));
	}
	set_signal_handlers_for_waiting_child(ms);
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
				status = EXIT_ERROR + WTERMSIG(wstatus);
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

int	execute(t_minishell *ms)
{
	int		status;
	pid_t	last_pid;

	if (ms->exec->cmd == NULL)
		return (1);
	if (ms->exec->cmdtype != NO_CMD && ms->exec->next == NULL)
	{
		status = execute_parent_process(ms);
	}
	else
	{
		last_pid = execute_child_process(ms, ms->exec);
		status = wait_child_process(ms, last_pid);
	}
	return (status);
}
