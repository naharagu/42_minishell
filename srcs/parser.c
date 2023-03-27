/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:01:50 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/27 20:17:42 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	check_execlist(t_minishell *ms)
{
	t_execlist	*startexec;
	char		*upchar;
	size_t		i;

	startexec = ms->exec;
	while (ms->exec)
	{
		i = 0;
		while (ms->exec->cmdline[i])
		{
			upchar = toupper_char(ms->exec->cmdline[i]);
			check_cmdtype(ms, upchar);
			free(upchar);
			check_redtype(ms, ms->exec->cmdline[i]);
			copy_cmd_red_list(ms, ms->exec->cmdline[i]);
			i++;
		}
		ms->exec = ms->exec->next;
	}
	ms->exec = startexec;
}

static void	copy_cmd_red_list(t_minishell *ms, char *str)
{
	if (cmd_lstsize(ms->exec->cmd) == 0 && red_lstsize(ms->exec->red) == 0)
	{
		if (ms->exec->cmdtype != NO_CMD)
			add_cmdlist(ms, str);
		if (ms->exec->redtype != NO_REDIRECT)
			add_redlist(ms, str);
	}
	else if (cmd_lstsize(ms->exec->cmd) > 0 && red_lstsize(ms->exec->red) == 0)
	{
		if (ms->exec->redtype == NO_REDIRECT)
			add_cmdlist(ms, str);
		if (ms->exec->redtype != NO_REDIRECT)
			add_redlist(ms, str);
	}
	else if (cmd_lstsize(ms->exec->cmd) == 0 && red_lstsize(ms->exec->red) > 0)
	{
		if (ms->exec->cmdtype == NO_CMD)
			add_redlist(ms, str);
		if (ms->exec->cmdtype != NO_CMD)
			add_cmdlist(ms, str);
	}
	else if (cmd_lstsize(ms->exec->cmd) > 0 && red_lstsize(ms->exec->red) > 0 \
		&& ms->exec->redtype != NO_REDIRECT)
		add_redlist(ms, str);
}
