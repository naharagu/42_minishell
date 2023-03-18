/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:53:39 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/18 17:59:08 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		minishell(t_minishell *ms);

int	main(int argc, char **argv, char **env)
{
	t_minishell	*ms;

	(void)argc;
	(void)argv;
	(void)env;
	ms = init_struct_ms();
	minishell(ms);
	all_free(ms);
	return (0);
}

void	minishell(t_minishell *ms)
{
	char	*line;

	rl_outstream = stderr;
	handle_signal(ms, SIGINT, DEFAULT);
	ignore_signal(ms, SIGQUIT);
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		ms->line = line;
		lexer(ms);
		//print_mslist(ms);//
		parser(ms);
		//print_cmdline(ms);//
		print_execlist(ms);//
		expansion(ms);
		//print_execlist(ms);//
		redirect(ms);
		cmd_exec(ms);//
		interpret(ms);
		free(line);
	}
	exit(ms->exit_status);
}
