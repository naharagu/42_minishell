/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 11:16:37 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/24 08:30:28 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_cmd(t_minishell *ms, t_cmdlist *cmd);
static void	expand_red(t_minishell *ms, t_redlist *red);
static void	assign_value_cmd(t_minishell *ms, t_cmdlist *cmd);
static void	assign_value_red(t_minishell *ms, t_redlist *red);

void	expansion(t_minishell *ms)
{
	t_execlist	*startexec;
	t_cmdlist	*startcmd;
	t_redlist	*startred;

	add_envlist(ms, "KEY", "hoge fuga");//
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
		// error_expansion_cmd(ms);
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

static void	expand_cmd( t_minishell *ms, t_cmdlist *cmd)
{
	t_envlist	*startenv;

	startenv = ms->exec->env;
	if (cmd->str && *cmd->str == '\'')
		cmd->quote = S_QUOTE;
	else if (cmd->str && *cmd->str == '\"')
		cmd->quote = D_QUOTE;
	if (cmd->str && (cmd->quote == S_QUOTE || cmd->quote == D_QUOTE))
		cmd->str = ft_strtrim(cmd->str, "\'\"");
	if (cmd->str && *cmd->str == '$' && cmd->quote != S_QUOTE)
	{
		cmd->str++;
		if (!(ft_strncmp(cmd->str, "?", ft_strlen(cmd->str))))
		{
			cmd->str--;
			cmd->str = ft_strdup(ft_itoa(ms->exit_status));
		}
		while (ms->exec->env)
		{
			assign_value_cmd (ms, cmd);
			ms->exec->env = ms->exec->env->next;
		}
	}
	ms->exec->env = startenv;
}

static void	assign_value_cmd(t_minishell *ms, t_cmdlist *cmd)
{
	char		**split;
	size_t		i;

	if (!(ft_strncmp(ms->exec->env->key, cmd->str, \
	ft_strlen(ms->exec->env->key))))
	{
		cmd->str--;
		if (cmd->quote == D_QUOTE)
			cmd->str = ft_strdup(ms->exec->env->value);
		else
		{
			split = ft_split(ms->exec->env->value, ' ');
			cmd->str = ft_strdup(split[0]);
			i = 0;
			while (split[++i])
				add_cmdlist(ms, split[i]);
		}
	}
	else
	{
		cmd->str--;
		cmd->str = ft_strdup("");
	}
}

static void	expand_red(t_minishell *ms, t_redlist *red)
{
	t_envlist	*startenv;

	startenv = ms->exec->env;
	if (red->str && *red->str == '\'')
		red->quote = S_QUOTE;
	else if (red->str && *red->str == '\"')
		red->quote = D_QUOTE;
	if (red->str && (red->quote == S_QUOTE || red->quote == D_QUOTE))
		red->str = ft_strtrim(red->str, "\'\"");
	if (red->str && *red->str == '$' && red->quote != S_QUOTE)
	{
		red->str++;
		if (!(ft_strncmp(red->str, "?", ft_strlen(red->str))))
		{
			red->str--;
			red->str = ft_strdup(ft_itoa(ms->exit_status));
		}
		while (ms->exec->env)
		{
			assign_value_red (ms, red);
			ms->exec->env = ms->exec->env->next;
		}
	}
	ms->exec->env = startenv;
}

static void	assign_value_red(t_minishell *ms, t_redlist *red)
{
	char		**split;
	size_t		i;

	if (!(ft_strncmp(ms->exec->env->key, red->str, \
	ft_strlen(ms->exec->env->key))))
	{
		red->str--;
		if (red->quote == D_QUOTE)
			red->str = ms->exec->env->value;
		else
		{
			split = ft_split(ms->exec->env->value, ' ');
			red->str = ft_strdup(split[0]);
			i = 0;
			while (split[++i])
				add_redlist(ms, split[i]);
			error_expansion_red(ms, i);
		}
	}
}
