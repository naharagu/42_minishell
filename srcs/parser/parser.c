/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:01:50 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/10 15:27:04 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_execlist(t_minishell *ms);
static void	copy_cmd_red_list(t_minishell *ms, char *str);

int	parser(t_minishell *ms)
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
	if (errror_parser_mslist(ms) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (check_execlist(ms));
}

static int	check_execlist(t_minishell *ms)
{
	t_execlist	*tmp_exec;
	char		*upchar;
	size_t		i;

	tmp_exec = ms->exec;
	while (tmp_exec)
	{
		i = 0;
		while (tmp_exec->cmdline[i])
		{
			check_redtype(ms, tmp_exec->cmdline[i]);
			upchar = toupper_char(tmp_exec->cmdline[i]);
			check_cmdtype(ms, upchar);
			free(upchar);
			copy_cmd_red_list(ms, tmp_exec->cmdline[i]);
			i++;
		}
		if (error_parser_execlist(ms) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		tmp_exec = tmp_exec->next;
	}
	return (EXIT_SUCCESS);
}

static void	copy_cmd_red_list(t_minishell *ms, char *str)
{
	if (cmd_lstsize(ms->exec->cmd) == 0 && red_lstsize(ms->exec->red) == 0)
	{
		if (ms->exec->redtype != NO_REDIRECT)
			ms->exec->flag = RED_FIRST;
	}
	if (ms->exec->flag != RED_FIRST)
	{
		if (ms->exec->redtype != NO_REDIRECT)
			add_redlist(ms, str);
		else if (ms->exec->redtype == NO_REDIRECT)
			add_cmdlist(ms, str);
	}
	else if (ms->exec->flag == RED_FIRST)
	{
		if (ms->exec->cmdtype != NO_CMD \
		|| !(ft_strncmp("CAT", toupper_char(str), ft_strlen(str))))
			add_cmdlist(ms, str);
		else if (ms->exec->cmdtype == NO_CMD)
			add_redlist(ms, str);
	}
}
