/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:59:50 by shimakaori        #+#    #+#             */
/*   Updated: 2023/02/25 17:14:37 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	interpret(char *line)
{
	extern char	**environ;
	char		*argv[] = {line, NULL};
	pid_t		pid;
	int			wstatus;

	pid = fork();
	if (pid < 0)
		print_error(ms, "fork", EXIT_ERR);
	else if (pid == 0)
	{
		// child process
		execve(line, argv, environ);
		print_error(ms, "execve", EXIT_ERR);
	}
	else
	{
		// parent process
		wait(&wstatus);
		return (WEXITSTATUS(wstatus));
	}
}
