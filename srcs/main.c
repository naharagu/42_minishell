/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:53:39 by shimakaori        #+#    #+#             */
/*   Updated: 2023/02/07 15:56:08 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	minishell(t_minishell *ms);
static void	signal_handler(int signum);

int	main(int argc, char **argv, char **env)
{
	t_minishell	*ms;

	ms = init_struct_ms(ms);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	minishell(ms);
	return (0);
}

static void	print_execlist(t_minishell *ms)
{
	size_t		i;
	size_t		j;

	i = 0;
	//printf("execsize= %d\n", exec_lstsize(ms->exec));//
	while (ms->exec)
	{
		j = 0;
		while (ms->exec->cmdline[j] != 0)
		{
			printf("[exec:%ld]cmdline[%ld]= %s\n", i, j, ms->exec->cmdline[j]);
			j++;
		}
		ms->exec = ms->exec->next;
		i++;
	}
}

static void	minishell(t_minishell *ms)
{
	char	*line;

	rl_outstream = stderr;
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		ms->input = line;
		lexer(ms);
		parser(ms);
		print_execlist(ms);//
		free(line);
		ms_lstclear(&ms->list);
	}
	exit(ms->exit_status);
}

static void	signal_handler(int signum)
{
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_redisplay();
}
