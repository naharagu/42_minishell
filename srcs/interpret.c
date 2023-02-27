/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:59:50 by shimakaori        #+#    #+#             */
/*   Updated: 2023/02/27 22:05:11 by shimakaori       ###   ########.fr       */
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
		print_error(ms, "malloc", EXIT_ERR);
	argv[0] = ft_strdup(ms->line);
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
		{
			ms->exit_status = 127;
			ms->err_str = ft_strjoin(argv[0], ": command not found");
			print_error(ms, ms->err_str, OTHER_ERR);
		}
		if (execve(path, argv, environ))
			free_argv_error(ms, argv, "execve");
	}
	else if (execve(ms->line, argv, environ))
		free_argv_error(ms, argv, "execve");
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
		//printf("path= %s\n", path[i]);//
		if (!(access(path[i], X_OK)))
			return (path[i]);
		i++;
	}
	return (NULL);
}

void	free_argv_error(t_minishell *ms, char **argv, char *str)
{
	free(argv[0]);
	free(argv);
	print_error(ms, str, EXIT_ERR);
}
