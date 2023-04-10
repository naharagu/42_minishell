/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:53:39 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/10 22:38:09 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_status;
static void	minishell(t_minishell *ms);
static void	prompt_helper(t_minishell *ms, char *line);

int	main(void)
{
	t_minishell	ms;

	init_ms(&ms);
	minishell(&ms);
}

static void	minishell(t_minishell *ms)
{
	char	*line;

	rl_outstream = stderr;//delete later
	init_env(ms);
	while (1)
	{
		set_signal_for_shell_prompt();
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		ms->line = line;
		prompt_helper(ms, line);
		clear_ms(ms);
	}
	env_lstclear(&ms->env);
	exit(g_status);
}

static void	prompt_helper(t_minishell *ms, char *line)
{
	if (lexer(ms) == EXIT_FAILURE)
		return ;
	print_mslist(ms);//
	if (parser(ms) == EXIT_FAILURE)
		return ;
	//print_cmdline(ms);
	//print_execlist(ms);//
	if (expansion(ms) == EXIT_FAILURE)
		return ;
	//print_execlist(ms);//
	if (prepare_redirect(ms) == EXIT_FAILURE)
		return ;
	g_status = execute(ms);
	free(line);
	return ;
}
