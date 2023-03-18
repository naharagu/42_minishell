/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 11:16:37 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/18 16:05:39 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_cmd(t_minishell *ms, t_cmdlist *cmd, t_execlist *exec);
static void	expand_red(t_minishell *ms, t_redlist *red, t_execlist *exec);
static void	assign_value_cmd(t_minishell *ms, t_cmdlist *cmd, t_execlist *exec);
static void	assign_value_red(t_minishell *ms, t_redlist *red, t_execlist *exec);

void	expansion(t_minishell *ms)
{
	t_execlist	*startexec;
	t_cmdlist	*startcmd;
	t_redlist	*startred;

	startexec = ms->exec;
	while (ms->exec)
	{
		add_envlist(ms, "key", "hoge fuga");
		startcmd = ms->exec->cmd;
		startred = ms->exec->red;
		while (ms->exec->cmd)
		{
			expand_cmd(ms, ms->exec->cmd, ms->exec);
			ms->exec->cmd = ms->exec->cmd->next;
		}
		while (ms->exec->red)
		{
			expand_red(ms, ms->exec->red, ms->exec);
			ms->exec->red = ms->exec->red->next;
		}
		ms->exec->cmd = startcmd;
		ms->exec->red = startred;
		ms->exec = ms->exec->next;
	}
	ms->exec = startexec;
}

static void	expand_cmd( t_minishell *ms, t_cmdlist *cmd, t_execlist *exec)
{
	t_envlist	*startenv;

	startenv = exec->env;
	printf("cmdstrinexpand= %s\n", cmd->str);//
	if (*cmd->str == '\'')
		cmd->quote = S_QUOTE;
	else if (*cmd->str == '\"')
		cmd->quote = D_QUOTE;
	if (cmd->quote == S_QUOTE || cmd->quote == D_QUOTE)
		cmd->str = ft_strtrim(cmd->str, "\'\"");
	if (*cmd->str == '$' && cmd->quote != S_QUOTE)
	{
		cmd->str++;
		while (exec->env)
		{
			assign_value_cmd (ms, cmd, exec);
			exec->env = exec->env->next;
		}
	}
	exec->env = startenv;
}

static void	expand_red(t_minishell *ms, t_redlist *red, t_execlist *exec)
{
	t_envlist	*startenv;

	startenv = exec->env;
	if (*red->str == '\'')
		red->quote = S_QUOTE;
	else if (*red->str == '\"')
		red->quote = D_QUOTE;
	if (red->quote == S_QUOTE || red->quote == D_QUOTE)
		red->str = ft_strtrim(red->str, "\'\"");
	if (*red->str == '$' && red->quote != S_QUOTE)
	{
		red->str++;
		while (exec->env)
		{
			assign_value_red (ms, red, exec);
			exec->env = exec->env->next;
		}
	}
	exec->env = startenv;
}

static void	assign_value_cmd(t_minishell *ms, t_cmdlist *cmd, t_execlist *exec)
{
	char		**split;
	size_t		i;

	i = 0;
	if (!(ft_strncmp(exec->env->key, cmd->str, ft_strlen(exec->env->key))))
	{
		if (cmd->quote == D_QUOTE)
			cmd->str = exec->env->value;
		else
		{
			split = ft_split(exec->env->value, ' ');
			while (split[i])
			{
				add_cmdlist(ms, split[i]);
				i++;
			}
		}
	}
}

static void	assign_value_red(t_minishell *ms, t_redlist *red, t_execlist *exec)
{
	char		**split;
	size_t		i;

	i = 0;
	if (!(ft_strncmp(exec->env->key, red->str, ft_strlen(exec->env->key))))
	{
		if (red->quote == D_QUOTE)
			red->str = exec->env->value;
		else
		{
			split = ft_split(exec->env->value, ' ');
			while (split[i])
			{
				add_redlist(ms, split[i]);
				i++;
			}
			error_expansion(ms, exec, i);
		}
	}
}
