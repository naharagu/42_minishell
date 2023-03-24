/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:05:41 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/24 21:52:39 by shimakaori       ###   ########.fr       */
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
		printf("list[%zu]: %s(%zu)\n", i, ms->list->str, \
			ft_strlen(ms->list->str));
		ms->list = ms->list->next;
		i++;
	}
	ms->list = start;
}

void	print_cmdline(t_minishell *ms)
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
			printf("[exec:%zu]cmdline[%zu]= %s(%zu)\n", j, i, \
				ms->exec->cmdline[i], ft_strlen(ms->exec->cmdline[i]));
			i++;
		}
		printf("[exec:%zu]cmdtype= %d\n", j, ms->exec->cmdtype);
		printf("[exec:%zu]cmdtype= %d\n", j, ms->exec->redtype);
		ms->exec = ms->exec->next;
		j++;
	}
	ms->exec = startexec;
}

void	print_execlist(t_minishell *ms)
{
	t_execlist	*startexec;
	t_cmdlist	*startcmd;
	t_redlist	*startred;
	t_envlist	*startenv;
	size_t		i;
	size_t		j;

	startexec = ms->exec;
	printf("execsize= %d\n", exec_lstsize(ms->exec));
	j = 0;
	while (ms->exec)
	{
		startcmd = ms->exec->cmd;
		startred = ms->exec->red;
		startenv = ms->exec->env;
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
		printf("envsize= %d\n", env_lstsize(ms->exec->env));
		while (ms->exec->env && ms->exec->env->key && ms->exec->env->value)
		{
			printf("[exec:%zu]KEY[%zu]= %s(%zu) VALUE[%zu]= %s(%zu)\n", \
			j, i, ms->exec->env->key, ft_strlen(ms->exec->env->key), \
			i, ms->exec->env->value, ft_strlen(ms->exec->env->value));
			ms->exec->env = ms->exec->env->next;
			i++;
		}
		ms->exec->cmd = startcmd;
		ms->exec->red = startred;
		ms->exec->env = startenv;
		ms->exec = ms->exec->next;
		j++;
	}
	ms->exec = startexec;
}
