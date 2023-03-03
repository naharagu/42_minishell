/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:53:39 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/03 15:50:38 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		minishell(t_minishell *ms);
static void	signal_handler(int signum);
//redinとheredoc要確認！
int	main(int argc, char **argv, char **env)
{
	t_minishell	*ms;

	ms = init_struct_ms(ms);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	minishell(ms);
	return (0);
}

void	minishell(t_minishell *ms)
{
	rl_outstream = stderr;
	while (1)
	{
		ms->line = readline("minishell$ ");
		if (!ms->line)
			break ;
		if (*ms->line)
			add_history(ms->line);
		ms->startline = ms->line;
		lexer(ms);
		//print_mslist(ms);//
		parser(ms);
		//print_execlist(ms);//
		expansion(ms);
		//print_cmdredlist(ms);//
		redirect(ms);
		interpret(ms);
		cmd_exec(ms);//
		all_free(ms);
	}
	exit(ms->exit_status);
}

static void	signal_handler(int signum)
{
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_redisplay();
}
