/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:59:50 by shimakaori        #+#    #+#             */
/*   Updated: 2023/02/27 17:01:50 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*serch_path(char *file);
void	free_argv_error(t_minishell *ms, char **argv, char *str);

int	interpret(t_minishell *ms)
{
	extern char	**environ;
	char		**argv;
	char		*path;
	pid_t		pid;
	int			wstatus;

	pid = fork();
	argv = ft_calloc(2, sizeof(char *));
	if (!argv)
		print_error(ms, "malloc", EXIT_ERR);
	argv[0] = ft_strdup(ms->line);
	argv[1] = NULL;
	path = argv[0];
	if (pid < 0)
		free_argv_error(ms, argv, "fork");
	else if (pid == 0)
	{
		if (execve(ms->line, argv, environ))
			free_argv_error(ms, argv, "execve");
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
	}
	else if (pid > 0)
	{
		wait(&wstatus);
		return (WEXITSTATUS(wstatus));
	}
	free_argv_error(ms, argv, "");
	return (0);
}

char	*serch_path(char *file)
{
	char	*path;
	char	*value;
	char	*end;

	value = getenv("PATH");
	printf("value= %s\n", value);//
	while (*value)
	{
		end = ft_strchr(value, ':');
		if (end)
			ft_strlcpy(path, value, end - value);
		else
			ft_strlcpy(path, value, ft_strlen(value));
		ft_strlcat(path, "/", ft_strlen(path));
		ft_strlcat(path, file, ft_strlen(path));
		printf("path= %s\n", path);//
		if (!(access(path, X_OK)))
			return (path);
		// if (!end)
		// 	return (NULL);
		value = end + 1;
	}
	return (NULL);
}

void	free_argv_error(t_minishell *ms, char **argv, char *str)
{
	free(argv[0]);
	free(argv);
	print_error(ms, str, EXIT_ERR);
}
