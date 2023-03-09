/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 11:29:34 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/09 14:38:42 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_minishell(t_minishell *ms)
{
	g_flag = 0;
	ft_putchar_fd('\n', STD_ERR);
	rl_on_new_line();
	rl_redisplay();
}

void	signal_heredoc(t_minishell *ms)
{
	g_flag = 0;
	all_free(ms);
	minishell(ms);
}

void	signal_exit(t_minishell *ms, int status)
{
	g_flag = 0;
	ms->exit_status = status;
	ft_putendl_fd("exit", STD_ERR);
	all_free(ms);
	exit (ms->exit_status);
}

void	signal_handler(int signum)
{
	g_flag = signum;
}

void	handle_signal(t_minishell *ms, int signum)
{
	struct sigaction	sa;

	// if (!heredoc)
	// 	sa.sa_handler = signal_minishell;
	// if (heredoc)
	// 	sa.sa_handler = signal_heredoc;
	sa.sa_handler = signal_handler;
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
