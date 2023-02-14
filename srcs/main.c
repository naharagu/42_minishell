/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:53:39 by shimakaori        #+#    #+#             */
/*   Updated: 2023/02/14 14:20:08 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	minishell(t_minishell *ms);
static void	signal_handler(int signum);

//リダイレクト実装してない
//環境変数展開の分割対応
int	main(int argc, char **argv, char **env)
{
	t_minishell	*ms;

	ms = init_struct_ms(ms);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	minishell(ms);
	return (0);
}

static void	minishell(t_minishell *ms)
{
	char	*line;

	rl_outstream = stderr;
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		ms->input = line;
		lexer(ms);
		//print_mslist(ms);//
		parser(ms);
		//print_execlist(ms);//
		//print_cmdredlist(ms);//
		expansion(ms);
		print_cmdredlist(ms);//
		free(line);
		ms_lstclear(&ms->list);
		exec_lstclear(&ms->exec);
	}
	exit(ms->exit_status);
}

static void	signal_handler(int signum)
{
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_redisplay();
}
