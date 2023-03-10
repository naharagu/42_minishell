/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 11:29:34 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/10 16:35:35 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_default(int signum)
{
	ft_putchar_fd('\n', STD_ERR);
	rl_on_new_line();
	rl_redisplay();
}

void	signal_heredoc(int signum)
{
	ft_putendl_fd("exit", STD_ERR);
}

void	signal_exit(int signum)
{
	ft_putendl_fd("exit", STD_ERR);
}

void	signal_handler(int signum)
{
	printf("minishell$ exit");
	//ft_putendl_fd("minishell$ exit", STD_OUT);
}

void	handle_signal(t_minishell *ms, int signum, int flag)
{
	struct sigaction	sa;

	if (flag == DEFAULT)
		sa.sa_handler = signal_default;
	else if (flag == HEREDOC)
		sa.sa_handler = signal_heredoc;
	// else if (flag == EXIT)
	// 	sa.sa_handler = signal_exit;
	//sa.sa_handler = signal_handler;
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
