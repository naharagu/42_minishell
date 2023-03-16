/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_argv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 21:17:59 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/16 14:28:14 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_argv	*list_to_argv(t_minishell *ms, t_execlist *exec)
{
	t_cmdlist	*startcmd;
	t_argv		*argv;
	int			i;

	argv = init_argv(ms);
	i = 0;
	argv->argc = cmd_lstsize(exec->cmd);
	argv->argv = malloc(sizeof(char *) * argv->argc);
	if (!argv->argv)
		exit_error(ms, "malloc");
	startcmd = exec->cmd;
	while (i < argv->argc)
	{
		argv->argv[i] = ft_strdup(ms->exec->cmd->str);
		//printf("argv[%d]= %s\n", i, argv->argv[i]);//
		ms->exec->cmd = ms->exec->cmd->next;
		i++;
	}
	ms->exec->cmd = startcmd;
	return (argv);
}

t_argv	*init_argv(t_minishell *ms)
{
	t_argv		*argv;

	argv = malloc (sizeof(t_argv));
	if (!argv)
		exit_error(ms, "malloc");
	argv->argc = 0;
	argv->argv = NULL;
	return (argv);
}

void	free_argv(t_argv *argv)
{
	int	i;

	i = 0;
	while (i < argv->argc)
	{
		if (argv->argv[i])
			free(argv->argv[i]);
		i++;
	}
	free(argv->argv);
	free(argv);
}
