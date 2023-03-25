/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:53:39 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/25 18:26:13 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell(t_minishell *ms);

int	main(void)
{
	t_minishell	*ms;

	ms = init_ms();
	minishell(ms);
	free (ms);
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
		// printf("---before expansion---\n");//
		// print_execlist(ms);//
		expansion(ms);
		// printf("---after expansion---\n");//
		// print_execlist(ms);//
		prepare_redirect(ms);
		//cmd_exec(ms);//
		ms->exit_status = execute_cmd(ms);
		free(line);
		clear_ms(ms);
	}
	exit(ms->exit_status);
}
