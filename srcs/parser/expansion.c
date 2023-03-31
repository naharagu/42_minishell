/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 11:16:37 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/31 10:38:04 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_status;
static void	expand_cmd(t_minishell *ms, t_cmdlist *cmd);
static void	expand_red(t_minishell *ms, t_redlist *red);
static void	assign_value_cmd(t_minishell *ms, t_cmdlist *cmd);
static void	assign_value_red(t_minishell *ms, t_redlist *red);

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

static void	expand_cmd( t_minishell *ms, t_cmdlist *cmd)
{
	t_envlist	*startenv;

	startenv = ms->env;
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
			cmd->str = ft_strdup(ft_itoa(g_status));
			return ;
		}
		while (ms->env)
		{
			if (cmd->str && ms->env->key)
				assign_value_cmd (ms, cmd);
			ms->env = ms->env->next;
		}
	}
	ms->env = startenv;
}

static void	assign_value_cmd(t_minishell *ms, t_cmdlist *cmd)
{
	char		**split;

	if (!(ft_strcmp(ms->env->key, cmd->str)))
	{
		cmd->str--;
		if (cmd->quote == D_QUOTE)
			cmd->str = ft_strdup(ms->env->value);
		else
		{
			split = ft_split(ms->env->value, ' ');
			cmd->str = ft_strdup(split[0]);
		}
	}
	else if (ft_strcmp(ms->env->key, cmd->str))
	{
		cmd->str--;
		cmd->str = NULL;
	}
}

static void	expand_red(t_minishell *ms, t_redlist *red)
{
	t_envlist	*startenv;

	startenv = ms->env;
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
			red->str = ft_strdup(ft_itoa(g_status));
		}
		while (ms->env)
		{
			if (red->str)
				assign_value_red (ms, red);
			ms->env = ms->env->next;
		}
	}
	ms->env = startenv;
}

static void	assign_value_red(t_minishell *ms, t_redlist *red)
{
	char		**split;
	char		*tmp;

	tmp = red->str;
	if (!(ft_strncmp(ms->env->key, red->str, ft_strlen(red->str))))
	{
		red->str--;
		if (red->quote == D_QUOTE)
		{
			red->str = ft_strdup(ms->env->value);
			if (ft_strchr(red->str, ' '))
				error_expansion_red(ms, tmp);
		}
		else
		{
			split = ft_split(ms->env->value, ' ');
			red->str = ft_strdup(split[0]);
		}
	}
	else if (ft_strncmp(ms->env->key, red->str, ft_strlen(red->str)))
	{
		red->str--;
		red->str = NULL;
		error_expansion_red(ms, tmp);
	}
}
