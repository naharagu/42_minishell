/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:59:50 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/18 15:00:56 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(t_minishell *ms, char **argv);
char	*serch_path(char *file);

void	interpret(t_minishell *ms)
{
	t_argv		*argv;
	pid_t		pid;
	int			wstatus;

	argv = init_argv(ms);
	pid = fork();
	argv->argc = 2;
	argv->argv = ft_calloc(2, sizeof(char **));
	if (!argv->argv)
		exit_error(ms, "malloc");
	printf("cmdstr= %s\n", ms->exec->cmd->str);//
	if (ms->exec->cmd->str)
		argv->argv[0] = ft_strdup(ms->exec->cmd->str);
	else if (!(ms->exec->cmd->str) && ms->exec->red->str)
		argv->argv[0] = ft_strdup(ms->exec->red->str);
	printf("argv[0]= %s\n", argv->argv[0]);//
	argv->argv[1] = NULL;
	if (pid < 0)
		free_argv(argv);
	else if (pid == 0)
		child_process(ms, argv->argv);
	else if (pid > 0)
	{
		wait(&wstatus);
		ms->exit_status = WEXITSTATUS(wstatus);
	}
	free_argv(argv);
}

void	child_process(t_minishell *ms, char **argv)
{
	extern char	**environ;
	char		*path;

	path = argv[0];
	printf("path= %s\n", path);//
	if (!(ft_strchr(path, '/')))
	{
		path = serch_path(path);
		if (!path || access(path, F_OK) < 0)
			return ;
		if (execve(path, argv, environ))
			exit_error(ms, "execve");
	}
	else if (execve(path, argv, environ))
		exit_error(ms, "execve");
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
