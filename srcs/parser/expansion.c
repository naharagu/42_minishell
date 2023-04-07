/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 11:16:37 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/07 14:18:29 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_status;
static void	expand_cmd( t_minishell *ms, t_cmdlist *cmd);
static int	expand_red(t_minishell *ms, t_redlist *red);

int	expansion(t_minishell *ms)
{
	t_execlist	*tmp_exec;
	t_cmdlist	*tmp_cmd;
	t_redlist	*tmp_red;

	tmp_exec = ms->exec;
	while (tmp_exec)
	{
		tmp_cmd = tmp_exec->cmd;
		while (tmp_cmd)
		{
			expand_cmd(ms, tmp_cmd);
			tmp_cmd = tmp_cmd->next;
		}
		tmp_red = tmp_exec->red;
		while (tmp_red)
		{
			if (expand_red(ms, tmp_red) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			tmp_red = tmp_red->next;
		}
		tmp_exec = tmp_exec->next;
	}
	return (EXIT_SUCCESS);
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

static int	expand_red(t_minishell *ms, t_redlist *red)
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
	return (error_expandedred(red, original));
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
