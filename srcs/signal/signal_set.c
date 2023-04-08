/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 11:29:34 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/08 13:43:41 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_signal_for_shell_prompt(void)
{
	struct sigaction	sa;

	if (sigemptyset(&sa.sa_mask) < 0)
		exit_error("sigemptyset");
	sa.sa_handler = prompt_handler;
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) < 0)
		exit_error("sigaction");
	assign_ign_handler(SIGQUIT);
}

void	set_signal_for_heredoc(void)
{
	struct sigaction	sa;

	if (sigemptyset(&sa.sa_mask) < 0)
		exit_error("sigemptyset");
	sa.sa_handler = heredoc_handler;
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) < 0)
		exit_error("sigaction");
	assign_ign_handler(SIGQUIT);
}

void	set_signal_for_execution(void)
{
	assign_dfl_handler(SIGINT);
	assign_dfl_handler(SIGQUIT);
}

void	set_signal_for_waiting_child(void)
{
	struct sigaction	sa;

	if (sigemptyset(&sa.sa_mask) < 0)
		exit_error("sigemptyset");
	sa.sa_handler = waitchild_handler;
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) < 0)
		exit_error("sigaction");
	if (sigaction(SIGQUIT, &sa, NULL) < 0)
		exit_error("sigaction");
}
