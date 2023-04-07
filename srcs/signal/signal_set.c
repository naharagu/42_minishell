/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 11:29:34 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/06 16:30:27 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_signal_for_shell_prompt(t_minishell *ms)
{
	struct sigaction	sa;

	if (sigemptyset(&sa.sa_mask) < 0)
		exit_error(ms, "sigemptyset");
	sa.sa_handler = prompt_handler;
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) < 0)
		exit_error(ms, "sigaction");
	assign_ign_handler(SIGQUIT, ms);
}

void	set_signal_for_heredoc(t_minishell *ms)
{
	struct sigaction	sa;

	if (sigemptyset(&sa.sa_mask) < 0)
		exit_error(ms, "sigemptyset");
	sa.sa_handler = heredoc_handler;
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) < 0)
		exit_error(ms, "sigaction");
	assign_ign_handler(SIGQUIT, ms);
}

void	set_signal_for_execution(t_minishell *ms)
{
	assign_dfl_handler(SIGINT, ms);
	assign_dfl_handler(SIGQUIT, ms);
}

void	set_signal_for_waiting_child(t_minishell *ms)
{
	struct sigaction	sa;

	if (sigemptyset(&sa.sa_mask) < 0)
		exit_error(ms, "sigemptyset");
	sa.sa_handler = waitchild_handler;
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) < 0)
		exit_error(ms, "sigaction");
	if (sigaction(SIGQUIT, &sa, NULL) < 0)
		exit_error(ms, "sigaction");
}
