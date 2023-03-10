/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:05:41 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/02 13:11:03 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_mslist(t_minishell *ms)
{
	t_mslist	*start;
	size_t		i;

	start = ms->list;
	i = 0;
	printf("lstsize= %d\n", ms_lstsize(ms->list));
	while (ms->list)
	{
		printf("list[%ld]: %s(%zu)\n", i, ms->list->str, \
			ft_strlen(ms->list->str));
		ms->list = ms->list->next;
		i++;
	}
	ms->list = start;
}

void	print_execlist(t_minishell *ms)
{
	t_execlist	*startexec;
	size_t		i;
	size_t		j;

	startexec = ms->exec;
	printf("execsize= %d\n", exec_lstsize(ms->exec));
	j = 0;
	while (ms->exec)
	{
		i = 0;
		while (ms->exec->cmdline[i])
		{
			printf("[exec:%ld]cmdline[%ld]= %s(%zu)\n", j, i, \
				ms->exec->cmdline[i], ft_strlen(ms->exec->cmdline[i]));
			i++;
		}
		ms->exec = ms->exec->next;
		j++;
	}
	ms->exec = startexec;
}

void	print_cmdredlist(t_minishell *ms)
{
	t_execlist	*startexec;
	t_cmdlist	*startcmd;
	t_redlist	*startred;
	size_t		i;
	size_t		j;

	ms->exec = startexec;
	j = 0;
	while (ms->exec)
	{
		startcmd = ms->exec->cmd;
		startred = ms->exec->red;
		i = 0;
		while (ms->exec->cmd && ms->exec->cmd->next)
		{
			printf("[exec:%ld]cmd[%ld]= %s(%zu)\n", j, i, \
				ms->exec->cmd->str, ft_strlen(ms->exec->cmd->str));
			ms->exec->cmd = ms->exec->cmd->next;
			i++;
		}
		i = 0;
		while (ms->exec->red && ms->exec->red->next)
		{
			printf("[exec:%ld]red[%ld]= %s(%zu)\n", j, i, \
				ms->exec->red->str, ft_strlen(ms->exec->red->str));
			ms->exec->red = ms->exec->red->next;
			i++;
		}
		ms->exec->cmd = startcmd;
		ms->exec->red = startred;
		ms->exec = ms->exec->next;
		j++;
	}
	ms->exec = startexec;
}
