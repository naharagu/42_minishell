/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 11:16:37 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/05 12:46:11 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_status;
void	expand_cmd( t_minishell *ms, t_cmdlist *cmd);
void	expand_red(t_minishell *ms, t_redlist *red);

void	expansion(t_minishell *ms)
{
	t_execlist	*startexec;
	t_cmdlist	*startcmd;
	t_redlist	*startred;

	startexec = ms->exec;
	while (ms->exec)
	{
		startcmd = ms->exec->cmd;
		while (ms->exec->cmd)
		{
			expand_cmd(ms, ms->exec->cmd);
			ms->exec->cmd = ms->exec->cmd->next;
		}
		ms->exec->cmd = startcmd;
		startred = ms->exec->red;
		while (ms->exec->red)
		{
			expand_red(ms, ms->exec->red);
			ms->exec->red = ms->exec->red->next;
		}
		ms->exec->red = startred;
		ms->exec = ms->exec->next;
	}
	ms->exec = startexec;
}

void	expand_cmd( t_minishell *ms, t_cmdlist *cmd)
{
	char	*original;
	char	*copy;
	char	*tmp;

	original = cmd->str;
	tmp = ft_strdup(cmd->str);
	copy = tmp;
	while (*tmp)
	{
		trim_quote_cmd(cmd, *tmp, &original);
		tmp++;
	}
	free(copy);
	original = cmd->str;
	if (cmd->str && *cmd->str == '$' && cmd->quote != S_QUOTE \
		&& ft_strlen(cmd->str) > 1)
		assign_value_cmd (ms, cmd, &original);
}

void	expand_red(t_minishell *ms, t_redlist *red)
{
	char	*original;
	char	*copy;
	char	*tmp;

	original = red->str;
	tmp = ft_strdup(red->str);
	copy = tmp;
	while (*tmp)
	{
		trim_quote_red(red, *tmp, &original);
		tmp++;
	}
	free(copy);
	original = red->str;
	if (red->str && *red->str == '$' && red->quote != S_QUOTE \
		&& ft_strlen(red->str) > 1)
	{
		assign_value_red (ms, red, &original);
		error_expandedred(ms, red, original);
	}
}
