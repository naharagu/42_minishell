/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 11:29:34 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/29 21:55:00 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assign_dfl_handler(int signum, t_minishell *ms)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_DFL;
	if (sigemptyset(&sa.sa_mask) < 0)
		exit_error(ms, "sigemptyset");
	sa.sa_flags = 0;
	if (sigaction(signum, &sa, NULL) < 0)
		exit_error(ms, "sigaction");
}

void	assign_ign_handler(int signum, t_minishell *ms)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	if (sigemptyset(&sa.sa_mask) < 0)
		exit_error(ms, "sigemptyset");
	sa.sa_flags = 0;
	if (sigaction(signum, &sa, NULL) < 0)
		exit_error(ms, "sigaction");
}

void	set_signal_handlers_for_shell_prompt(t_minishell *ms)
{
	assign_dfl_handler(SIGQUIT, ms);
	assign_ign_handler(SIGINT, ms);
}

void	set_signal_handlers_for_execution(t_minishell *ms)
{
	assign_dfl_handler(SIGQUIT, ms);
	assign_dfl_handler(SIGINT, ms);
}

void	set_signal_handlers_for_waiting_child(t_minishell *ms)
{
	assign_ign_handler(SIGQUIT, ms);
	assign_ign_handler(SIGQUIT, ms);
}
