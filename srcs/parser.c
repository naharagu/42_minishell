/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:01:50 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/15 21:20:12 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include "../include/minishell.h"

void		add_execlist(t_minishell *ms, t_mslist	*first, size_t num);
static void	check_execlist(t_minishell *ms);
static void	copy_cmd_red_list(t_minishell *ms, char *str);

void	parser(t_minishell *ms)
{
	t_mslist	*start;
	t_mslist	*first;

	start = ms->list;
	first = ms->list;
	ms->cmd_size = 0;
	while (ms->list)
	{
		check_pipe(ms, ms->list->str);
		if (ms->list->pipe != NO_PIPE)
		{
			add_execlist(ms, first, ms->cmd_size);
			first = ms->list->next;
			ms->cmd_size = 0;
		}
		else
			ms->cmd_size++;
		ms->list = ms->list->next;
	}
	add_execlist(ms, first, ms->cmd_size);
	ms->list = start;
	check_execlist(ms);
	error_parser_mslist(ms);
	error_parser_execlist(ms);
}

void	add_execlist(t_minishell *ms, t_mslist	*first, size_t num)
{
	t_execlist	*tmp;

	tmp = exec_lstnew(ms, first, num);
	exec_lstadd_back(&ms->exec, tmp);
}

static void	check_execlist(t_minishell *ms)
{
	t_execlist	*startexec;
	t_cmdlist	*startcmd;
	t_redlist	*startred;
	size_t		i;

	startexec = ms->exec;
	while (ms->exec)
	{
		startcmd = ms->exec->cmd;
		startred = ms->exec->red;
		i = 0;
		while (ms->exec->cmdline[i])
		{
			if (!toupper_char(ms->exec->cmdline[i]))
				exit_error(ms, "malloc");
			check_cmdtype(ms, toupper_char(ms->exec->cmdline[i]));
			free(toupper_char(ms->exec->cmdline[i]));
			check_redtype(ms, ms->exec->cmdline[i]);
			copy_cmd_red_list(ms, ms->exec->cmdline[i]);
			i++;
		}
		ms->exec->cmd = startcmd;
		ms->exec->red = startred;
		ms->exec = ms->exec->next;
	}
	ms->exec = startexec;
}

static void	copy_cmd_red_list(t_minishell *ms, char *str)
{
	if (ms->exec->redtype == NO_REDIRECT)
	{
		ms->exec->cmd->str = str;
		ms->exec->cmd->next = cmd_lstnew(ms, ms->exec->cmd->next);
		ms->exec->cmd = ms->exec->cmd->next;
	}
	else if (ms->exec->redtype != NO_REDIRECT)
	{
		ms->exec->red->str = str;
		ms->exec->red->next = red_lstnew(ms, ms->exec->red->next);
		ms->exec->red = ms->exec->red->next;
	}
}
