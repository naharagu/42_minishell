/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 11:16:37 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/04 12:43:54 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_status;
static void	expand_cmd(t_minishell *ms, t_cmdlist *cmd);
static void	expand_red(t_minishell *ms, t_redlist *red);
static void	assign_value_cmd(t_minishell *ms, t_cmdlist *cmd, char **original);
static void	assign_value_red(t_minishell *ms, t_redlist *red, char **original);

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
	char	*original;
	char	*tmp;

	original = cmd->str;
	tmp = cmd->str;
	while (*tmp)
	{
		if (*tmp == '\'' && cmd->quote != D_QUOTE)
		{
			cmd->quote = S_QUOTE;
			free(original);
			cmd->str = ms_strtrim(cmd->str, '\'');
		}
		else if (*tmp == '\"' && cmd->quote != S_QUOTE)
		{
			cmd->quote = D_QUOTE;
			free(original);
			cmd->str = ms_strtrim(cmd->str, '\"');
		}
		tmp++;
	}
	if (cmd->str && *cmd->str == '$' && cmd->quote != S_QUOTE \
		&& ft_strlen(cmd->str) > 1)
	{
		assign_value_cmd (ms, cmd, &original);
	}
}

static void	assign_value_cmd(t_minishell *ms, t_cmdlist *cmd, char **original)
{
	t_envlist	*startenv;

	startenv = ms->env;
	cmd->str++;
	if (cmd->str && !(ft_strncmp(cmd->str, "?", ft_strlen(cmd->str))))
	{
		free(*original);
		cmd->str = ft_itoa(g_status);
		return ;
	}
	while (cmd->str && ms->env)
	{
		ms->env = ms->env->next;
		if (!(ft_strncmp(ms->env->key, cmd->str, ft_strlen(cmd->str))))
		{
			//printf("%s\n", cmd->str);//
			free(*original);
			cmd->str = ft_strdup(ms->env->value);
			ms->env = startenv;
			return ;
		}
	}
	ms->env = startenv;
	free(*original);
	cmd->str = NULL;
}

static void	expand_red(t_minishell *ms, t_redlist *red)
{
	char		*original;

	original = red->str;
	if (red->str && *red->str == '\'')
		red->quote = S_QUOTE;
	else if (red->str && *red->str == '\"')
		red->quote = D_QUOTE;
	if (red->str && (red->quote == S_QUOTE || red->quote == D_QUOTE))
		red->str = ft_strtrim(red->str, "\'\"");
	if (red->str && *red->str == '$' && red->quote != S_QUOTE \
		&& ft_strlen(red->str) > 1)
	{
		assign_value_red (ms, red, &original);
		error_expandedred(ms, red, original);
	}
}

static void	assign_value_red(t_minishell *ms, t_redlist *red, char **original)
{
	t_envlist	*startenv;

	startenv = ms->env;
	red->str++;
	if (red->str && !(ft_strncmp(red->str, "?", ft_strlen(red->str))))
	{
		free(*original);
		red->str = ft_itoa(g_status);
		return ;
	}
	while (red->str && ms->env)
	{
		ms->env = ms->env->next;
		if (!(ft_strncmp(ms->env->key, red->str, ft_strlen(red->str))))
		{
			free(*original);
			red->str = ft_strdup(ms->env->value);
			ms->env = startenv;
			return ;
		}
	}
	ms->env = startenv;
	free(*original);
	red->str = NULL;
}
