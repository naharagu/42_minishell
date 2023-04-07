/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:53:39 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/07 13:01:00 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_status;
void		minishell(t_minishell *ms);
static void	prompt_helper(t_minishell *ms, char *line);

int	main(void)
{
	t_minishell	ms;

	init_ms(&ms);
	minishell(&ms);
}

void	minishell(t_minishell *ms)
{
	char	*line;

	rl_outstream = stderr;//
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
		prompt_helper(ms, line);
		clear_ms(ms);
	}
	env_lstclear(&ms->env);
	exit(g_status);
}

static void	prompt_helper(t_minishell *ms, char *line)
{
	lexer(ms);
	parser(ms);
	expansion(ms);
	if (prepare_redirect(ms) == EXIT_SUCCESS)
		g_status = execute(ms);
	free(line);
	return ;
}
