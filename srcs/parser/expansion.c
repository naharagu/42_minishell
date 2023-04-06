/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 11:16:37 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/06 19:49:12 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_status;
static void	expand_cmd( t_minishell *ms, t_cmdlist *cmd);
static void	expand_red(t_minishell *ms, t_redlist *red);

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

	(void)ms;
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
	assign_value_red (ms, red, &original);
	error_expandedred(ms, red, original);
}

char	*expand_env(t_minishell *ms, char *tmp)
{
	t_envlist	*startenv;
	char		*result;

	startenv = ms->env;
	ms->env = ms->env->next;
	while (tmp && ms->env)
	{
		if (!(ft_strncmp(tmp, "?", ft_strlen(tmp))))
		{
			result = ft_itoa(g_status);
			ms->env = startenv;
			return (result);
		}
		else if (!(ft_strncmp(ms->env->key, tmp, ft_strlen(tmp))))
		{
			result = ft_strdup(ms->env->value);
			ms->env = startenv;
			return (result);
		}
		ms->env = ms->env->next;
	}
	ms->env = startenv;
	return (NULL);
}

char	*joinstr(t_minishell *ms, char **split, char **tmp)
{
	char	*old;
	char	*new;

	old = ft_strdup(*tmp);
	free(*tmp);
	new = expand_env(ms, *split);
	*tmp = ft_strjoin(old, new);
	free(old);
	free(new);
	free(*split);
	return (*tmp);
}
