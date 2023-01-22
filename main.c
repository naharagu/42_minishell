/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 22:47:25 by naharagu          #+#    #+#             */
/*   Updated: 2023/01/21 19:12:40 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <unistd.h>

void	init_struct_ms(t_minishell *ms)
{
	ms->exit_status = 0;
	return ;
}

char	*get_cmdpath(char *cmd, char **envp)
{
	char	**paths;
	char	*tmp;
	char	*cmd_path;

	while (ft_strncmp("PATH=", *envp, 5))
		envp++;
	paths = ft_split(&envp[0][5], ':');
	if (!paths)
		exit(1);
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		if (tmp == NULL)
			exit(1);
		cmd_path = ft_strjoin(tmp, cmd);
		if (cmd_path == NULL)
			exit(1);
		free(tmp);
		if (access(cmd_path, 0) == 0)
			return (cmd_path);
		free(cmd_path);
		paths++;
	}
	return (NULL);
}

int	execute_cmd(char *input, char **argv, char **env)
{
	pid_t	pid;
	int		status;
	char	*cmd_path;

	pid = fork();
	cmd_path = input;
	if (pid < 0)
		exit(1);
	else if (pid == 0)
	{
		if (ft_strchr(cmd_path, '/') == NULL)
			cmd_path = get_cmdpath(cmd_path, env);
		execve(cmd_path, argv, env);
		free(cmd_path);
	}
	else
	{
		wait(&status);
		return (WEXITSTATUS(status));
	}
	return (0);
}

int	minishell(t_minishell *ms, char **argv, char **env)
{
	char	*input;

	while (1)
	{
		input = readline("minishell$>");
		if (!input)
			break ;
		add_history(input);
		ms->exit_status = execute_cmd(input, argv, env);
		free(input);
	}
	return (ms->exit_status);
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	ms;

	if (argc != 1)
		return (1);
	init_struct_ms(&ms);
	exit(minishell(&ms, argv, env));
}

/* __attribute__((destructor)) static void destructor()
{
	system("leaks -q minishell");
} */
