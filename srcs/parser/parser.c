/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:01:50 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/12 15:52:59 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_execlist(t_minishell *ms);
static void	copy_cmd_red_list(t_minishell *ms, t_execlist *exec);

int	parser(t_minishell *ms)
{
	t_mslist	*tmplist;
	t_mslist	*first;

	tmplist = ms->list;
	while (tmplist)
	{
		ms->cmd_size = 0;
		first = tmplist;
		while (tmplist->str && (ft_strncmp("|", tmplist->str,
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
	size_t		i;

	startexec = ms->exec;
	while (ms->exec)
	{
		i = 0;
		while (ms->exec->cmdline[i])
		{
			check_redtype(ms, ms->exec->cmdline[i]);
			check_cmdtype(ms, ms->exec->cmdline[i]);
			if (error_redirect(ms->exec, ms->exec->cmdline[i]) == EXIT_FAILURE)
			{
				ms->exec = startexec;
				return (EXIT_FAILURE);
			}
			i++;
		}
		copy_cmd_red_list(ms, ms->exec);
		ms->exec = ms->exec->next;
	}
	ms->exec = startexec;
	return (EXIT_SUCCESS);
}

static void	copy_cmd_red_list(t_minishell *ms, t_execlist *exec)
{
	size_t	i;

	i = 0;
	while (exec->cmdline[i])
	{
		if (ft_strcmp(exec->cmdline[i], ">>") == 0 || \
			ft_strcmp(exec->cmdline[i], ">") == 0 || \
			ft_strcmp(exec->cmdline[i], "<") == 0 || \
			ft_strcmp(exec->cmdline[i], "<<") == 0)
		{
			add_redlist(ms, exec->cmdline[i]);
			i++;
			if (exec->cmdline[i])
				add_redlist(ms, exec->cmdline[i]);
			else
				break ;
		}
		else
			add_cmdlist(ms, exec->cmdline[i]);
		i++;
	}
}
