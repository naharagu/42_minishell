/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 11:29:34 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/10 18:36:15 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	default_handler(int signum)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_redisplay();
}

void	heredoc_handler(int signum)
{
	t_minishell	*ms;

	ms = init_struct_ms(ms);
	rl_on_new_line();
	rl_replace_line("", 0);
	ft_putchar_fd('\n', STDOUT_FILENO);
	minishell(ms);
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
