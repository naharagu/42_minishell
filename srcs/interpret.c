/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:59:50 by shimakaori        #+#    #+#             */
/*   Updated: 2023/02/27 23:45:48 by shimakaori       ###   ########.fr       */
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
	{
		ms->err_location = ft_strdup("malloc");
		print_error(ms, ms->err_location, EXIT_ERR);
	}
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
			ms->err_msg = ft_strjoin(argv[0], ": command not found");
			print_error(ms, OTHER_ERR);
		}
		if (execve(path, argv, environ))
		{
			free(path);
			free_argv_error(ms, argv, "execve");
		}
	}
	else if (execve(ms->line, argv, environ))
		free_argv_error(ms, argv, "execve");
	free(path);
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
	ms->err_msg = str;
	print_error(ms, EXIT_ERR);
}
