/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:53:39 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/13 18:57:40 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_status;
static void	minishell(t_minishell *ms);
static void	prompt_helper(t_minishell *ms);

int	main(void)
{
	t_minishell	ms;

	rl_outstream = stderr;//delete later
	init_ms(&ms);
	minishell(&ms);
}

void	print_execlist(t_minishell *ms)
{
	t_execlist	*startexec;
	t_cmdlist	*startcmd;
	t_redlist	*startred;
	size_t		i;
	size_t		j;

	startexec = ms->exec;
	printf("\x1b[32mexecsize= %d\n", exec_lstsize(ms->exec));
	j = 0;
	while (ms->exec)
	{
		startcmd = ms->exec->cmd;
		startred = ms->exec->red;
		i = 0;
		printf("[exec:%zu]cmdtype= %d\n", j, ms->exec->cmdtype);
		printf("[exec:%zu]redtype= %d\n", j, ms->exec->redtype);
		printf("cmdsize= %d\n", cmd_lstsize(ms->exec->cmd));
		while (ms->exec->cmd && ms->exec->cmd->str)
		{
			printf("[exec:%zu]cmd[%zu]= %s(%zu)\n", j, i, \
				ms->exec->cmd->str, ft_strlen(ms->exec->cmd->str));
			ms->exec->cmd = ms->exec->cmd->next;
			i++;
		}
		i = 0;
		printf("redsize= %d\n", red_lstsize(ms->exec->red));
		while (ms->exec->red && ms->exec->red->str)
		{
			printf("[exec:%zu]red[%zu]= %s(%zu)\n", j, i, \
				ms->exec->red->str, ft_strlen(ms->exec->red->str));
			printf("redtype is %d\n", ms->exec->redtype);
			ms->exec->red = ms->exec->red->next;
			i++;
		}
		i = 0;
		ms->exec->cmd = startcmd;
		ms->exec->red = startred;
		ms->exec = ms->exec->next;
		j++;
	}
	ms->exec = startexec;
	printf("\x1b[39m\n");
}

static void	minishell(t_minishell *ms)
{
	char	*line;

	init_env(ms);
	while (1)
	{
		set_signal_for_shell_prompt();
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		ms->line = line;
		prompt_helper(ms);
		free(line);
		clear_ms(ms);
	}
	env_lstclear(&ms->env);
	exit(g_status);
}

static void	prompt_helper(t_minishell *ms)
{
	if (lexer(ms) == EXIT_FAILURE)
		return ;
	if (parser(ms) == EXIT_FAILURE)
		return ;
	if (expansion(ms) == EXIT_FAILURE)
		return ;
	if (prepare_redirect(ms) == EXIT_FAILURE)
		return ;
	g_status = execute(ms);
	return ;
}
