/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 22:47:25 by naharagu          #+#    #+#             */
/*   Updated: 2023/01/16 22:12:37 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_struct_ms(t_minishell *ms)
{
	ms = malloc(sizeof(t_minishell));
	if (!ms)
		exit(0);
	ms->exit_status = 0;
	return ;
}

int	execute_cmd(char *input, char **argv, char **env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		execve(input, argv, env);
	}
	else
	{
		wait(&status);
		return (status);
	}
}

void	minishell(t_minishell *ms, char **argv, char **env)
{
	char	*input;

	while (1)
	{
		input = readline("minishell$>");
		if (!input)
			break ;
		add_history(input);
		execute_cmd(input, argv, env);
		free(input);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	*ms;

	init_struct_ms(ms);
	minishell(ms, argv, env);
	exit(0);
}
