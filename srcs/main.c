/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:53:39 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/05 10:54:26 by naharagu         ###   ########.fr       */
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
}

void	minishell(t_minishell *ms)
{
	char	*line;

	init_env(ms);
	while (1)
	{
		set_signal_for_shell_prompt(ms);
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
		//print_execlist(ms);//
		expansion(ms);
		//print_execlist(ms);//
		if (prepare_redirect(ms) == EXIT_SUCCESS)
			g_status = execute(ms);
		free(line);
		clear_ms(ms);
	}
	env_lstclear(&ms->env);
	exit(g_status);
}
