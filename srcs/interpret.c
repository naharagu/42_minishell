/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:59:50 by shimakaori        #+#    #+#             */
/*   Updated: 2023/02/28 12:08:22 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(t_minishell *ms, char **argv);
char	*serch_path(char *file);
void	free_argv_error(t_minishell *ms, char **argv, char *str);

int	interpret(t_minishell *ms)
{
	char		**argv;
	pid_t		pid;
	int			wstatus;

	pid = fork();
	argv = ft_calloc(2, sizeof(char *));
	if (!argv)
		exit_error(ms, "malloc");
	argv[0] = ft_strdup(ms->exec->cmd->str);
	argv[1] = NULL;
	if (pid < 0)
		free_argv_error(ms, argv, "fork");
	else if (pid == 0)
		child_process(ms, argv);
	else if (pid > 0)
	{
		wait(&wstatus);
		return (WEXITSTATUS(wstatus));
	}
	free_argv_error(ms, argv, "");
	return (0);
}

void	child_process(t_minishell *ms, char **argv)
{
	extern char	**environ;
	char		*path;

	path = argv[0];
	if (!(ft_strchr(path, '/')))
	{
		path = serch_path(path);
		if (!path || access(path, F_OK) < 0)
			other_error(ms, argv[0], "command not found", 127);
		if (execve(path, argv, environ))
			return ;
	}
	else if (execve(ms->line, argv, environ))
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

void	free_argv_error(t_minishell *ms, char **argv, char *str)
{
	free(argv[0]);
	free(argv);
	exit_error(ms, str);
}
