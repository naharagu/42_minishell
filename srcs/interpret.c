/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:59:50 by shimakaori        #+#    #+#             */
/*   Updated: 2023/02/25 22:13:00 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_error(t_minishell *ms, char **argv, char *str);

int	interpret(t_minishell *ms, char *line)
{
	extern char	**environ;
	char		**argv;
	pid_t		pid;
	int			wstatus;

	pid = fork();
	argv = ft_calloc(2, sizeof(char *));
	if (!argv)
		print_error(ms, "malloc", EXIT_ERR);
	argv[0] = ft_strdup(line);
	argv[1] = NULL;
	if (pid < 0)
		free_error(ms, argv, "fork");
	else if (pid == 0)
	{
		if (execve(line, argv, environ))
			free_error(ms, argv, "execve");
	}
	else if (pid > 0)
	{
		wait(&wstatus);
		return (WEXITSTATUS(wstatus));
	}
	free_error(ms, argv, "");
	return (0);
}

void	free_error(t_minishell *ms, char **argv, char *str)
{
	free(argv[0]);
	free(argv);
	print_error(ms, str, EXIT_ERR);
}
