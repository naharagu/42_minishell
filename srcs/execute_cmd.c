/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:59:50 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/10 20:59:07 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include "../include/minishell.h"

static void	free_path(char **path)
{
	size_t i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
}

static char	*serch_path(t_minishell *ms, char *file)
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

static void	child_process(t_minishell *ms, char *cmdline)
{
	extern char	**environ;
	char		*path;

	path = cmdline;
	if (!(ft_strchr(path, '/')))
	{
		path = serch_path(ms, path);
		if (!path)
			return ;
		if (access(path, F_OK) < 0)
			return (free(path));
		if (execve(path, &ms->exec->cmdline[0], environ) == -1)
			return ;
	}
	else if (execve(path, &ms->exec->cmdline[0], environ) == -1)
		return ;
}

void	execute_cmd(t_minishell *ms)
{
	pid_t		pid;
	int			wstatus;

	pid = fork();
	if (pid < 0)
		exit_error(ms, "pipe");
	else if (pid == 0)
		child_process(ms, ms->exec->cmdline[0]);
	wait(&wstatus);
	ms->exit_status = WEXITSTATUS(wstatus);
}
