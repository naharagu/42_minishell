/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:53:39 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/19 11:28:32 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_status;
static void	minishell(t_minishell *ms);
static void	prompt_helper(t_minishell *ms);

int	main(void)
{
	t_minishell	ms;

	init_ms(&ms);
	minishell(&ms);
}

static void	minishell(t_minishell *ms)
{
	char	*line;

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
		prompt_helper(ms);
		free(line);
		clear_ms(ms);
	}
	env_lstclear(&ms->env);
	exit(g_status);
}

static void	prompt_helper(t_minishell *ms)
{
	if (lexer(ms) == EXIT_FAILURE)
		return ;
	if (parser(ms) == EXIT_FAILURE)
		return ;
	if (expansion(ms) == EXIT_FAILURE)
		return ;
	if (prepare_redirect(ms) == EXIT_FAILURE)
		return ;
	g_status = execute(ms);
	return ;
}
