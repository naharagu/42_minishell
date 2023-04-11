/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:01:50 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/11 09:32:35 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_execlist(t_minishell *ms);
static void	copy_cmd_red_list(t_minishell *ms, char *str);

int	parser(t_minishell *ms)
{
	t_mslist	*tmplist;
	t_mslist	*first;

	tmplist = ms->list;
	while (tmplist)
	{
		ms->cmd_size = 0;
		first = tmplist;
		while (tmplist->str && (ft_strncmp("|", tmplist->str, \
			ft_strlen(tmplist->str))))
		{
			if (!tmplist->next)
			{
				ms->cmd_size++;
				break ;
			}
			tmplist = tmplist->next;
			ms->cmd_size++;
		}
		add_execlist(ms, first, ms->cmd_size);
		tmplist = tmplist->next;
	}
	if (errror_parser_mslist(ms) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (check_execlist(ms));
}

static int	check_execlist(t_minishell *ms)
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
			check_redtype(ms, ms->exec->cmdline[i]);
			upchar = toupper_char(ms->exec->cmdline[i]);
			check_cmdtype(ms, upchar);
			free(upchar);
			copy_cmd_red_list(ms, ms->exec->cmdline[i]);
			i++;
		}
		if (error_parser_execlist(ms) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		ms->exec = ms->exec->next;
	}
	ms->exec = startexec;
	return (EXIT_SUCCESS);
}

static void	copy_cmd_red_list(t_minishell *ms, char *str)
{
	char	*upchar;

	upchar = toupper_char(str);
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
		|| !(ft_strncmp("CAT", upchar, ft_strlen(str))))
			add_cmdlist(ms, str);
		else if (ms->exec->cmdtype == NO_CMD)
			add_redlist(ms, str);
	}
	free(upchar);
}
