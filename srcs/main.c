/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:53:39 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/29 19:13:21 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_status;
void	minishell(t_minishell *ms);

int	main(void)
{
	t_minishell	ms;

	init_ms(&ms);
	minishell(&ms);
	return (0);
}

void	minishell(t_minishell *ms)
{
	char	*line;

	rl_outstream = stderr;
	handle_signal(ms, SIGINT, DEFAULT);
	ignore_signal(ms, SIGQUIT);
	init_env(ms);
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
		// print_cmdline(ms);//
		// printf("---before expansion---\n");//
		// print_execlist(ms);//
		expansion(ms);
		// printf("---after expansion---\n");//
		// print_execlist(ms);//
		prepare_redirect(ms);
		g_status = execute(ms);
		free(line);
		clear_ms(ms);
	}
	env_lstclear(&ms->env);
	exit(g_status);
}
