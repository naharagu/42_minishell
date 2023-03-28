/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 11:29:34 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/28 22:19:26 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
volatile sig_atomic_t	g_sig;

void	default_handler(int signum)
{
	(void)signum;
	rl_on_new_line();
	rl_replace_line("", 0);
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_redisplay();
}

void	heredoc_handler(int signum)
{
	(void)signum;
	rl_on_new_line();
	rl_replace_line("", 0);
	ft_putchar_fd('\n', STDOUT_FILENO);
}

void	handle_signal(t_minishell *ms, int signum, t_sig flag)
{
	struct sigaction	sa;

	if (flag == DEFAULT)
		sa.sa_handler = default_handler;
	else if (flag == HEREDOC)
		sa.sa_handler = heredoc_handler;
	if (sigemptyset(&sa.sa_mask) < 0)
		exit_error(ms, "sigemptyset");
	sa.sa_flags = 0;
	if (sigaction(signum, &sa, NULL) < 0)
		exit_error(ms, "sigaction");
}

void	ignore_signal(t_minishell *ms, int signum)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	if (sigemptyset(&sa.sa_mask) < 0)
		exit_error(ms, "sigemptyset");
	sa.sa_flags = 0;
	if (sigaction(signum, &sa, NULL) < 0)
		exit_error(ms, "sigaction");
}

void	init_signal(t_minishell *ms, int signum)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_DFL;
	if (sigemptyset(&sa.sa_mask) < 0)
		exit_error(ms, "sigemptyset");
	sa.sa_flags = 0;
	if (sigaction(signum, &sa, NULL) < 0)
		exit_error(ms, "sigaction");
}
