/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 11:29:34 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/11 20:54:41 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_status;

void	prompt_handler(int signum)
{
	(void)signum;
	rl_on_new_line();
	rl_replace_line("", 0);
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_redisplay();
	g_status = 1;
}

void	heredoc_handler(int signum)
{
	(void)signum;
	g_status = 1;
}

void	waitchild_handler(int signum)
{
	ft_putchar_fd('\n', STDOUT_FILENO);
	g_status = EXIT_ERROR + signum;
}

void	assign_dfl_handler(int signum)
{
	struct sigaction	sa;

	if (sigemptyset(&sa.sa_mask) < 0)
		exit_error("sigemptyset");
	sa.sa_handler = SIG_DFL;
	sa.sa_flags = 0;
	if (sigaction(signum, &sa, NULL) < 0)
		exit_error("sigaction");
}

void	assign_ign_handler(int signum)
{
	struct sigaction	sa;

	if (sigemptyset(&sa.sa_mask) < 0)
		exit_error("sigemptyset");
	sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0;
	if (sigaction(signum, &sa, NULL) < 0)
		exit_error("sigaction");
}
