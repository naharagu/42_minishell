/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:36:16 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/05 12:15:05 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_status;
static void	trim_quote_cmd(t_cmdlist *cmd, char c, char **original);
static void	ms_strtrim_cmd(t_cmdlist *cmd, char c, char **original);
static void	assign_value_cmd(t_minishell *ms, t_cmdlist *cmd, char **original);
static void	expand_env_cmd(t_minishell *ms, t_cmdlist *cmd, char *tmp, \
			char **original);

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

static void	trim_quote_cmd(t_cmdlist *cmd, char c, char **original)
{
	if (c == '\'' && cmd->quote == NO_QUOTE)
	{
		cmd->quote = S_QUOTE;
		ms_strtrim_cmd(cmd, '\'', original);
	}
	else if (c == '\"' && cmd->quote == NO_QUOTE)
	{
		cmd->quote = D_QUOTE;
		ms_strtrim_cmd(cmd, '\"', original);
	}
}

static void	ms_strtrim_cmd(t_cmdlist *cmd, char c, char **original)
{
	char	**split;
	char	*tmp;
	char	*old;
	size_t	i;

	i = 1;
	split = ft_split(cmd->str, c);
	tmp = split[0];
	while (split[i] && split[i][0] != '\0')
	{
		old = ft_strdup(tmp);
		free(tmp);
		tmp = ft_strjoin(old, split[i]);
		free(old);
		free(split[i]);
		i++;
	}
	free(*original);
	cmd->str = ft_strdup(tmp);
	free(tmp);
	free(split);
}

static void	assign_value_cmd(t_minishell *ms, t_cmdlist *cmd, char **original)
{
	char		*tmp;

	tmp = cmd->str;
	tmp++;
	if (tmp && !(ft_strncmp(tmp, "?", ft_strlen(tmp))))
	{
		free(*original);
		cmd->str = ft_itoa(g_status);
		return ;
	}
	expand_env_cmd(ms, cmd, tmp, original);
	free(*original);
	cmd->str = NULL;
}

void	expand_env_cmd(t_minishell *ms, t_cmdlist *cmd, char *tmp, \
		char **original)
{
	t_envlist	*startenv;

	startenv = ms->env;
	ms->env = ms->env->next;
	while (tmp && ms->env)
	{
		if (!(ft_strncmp(ms->env->key, tmp, ft_strlen(tmp))))
		{
			free(*original);
			cmd->str = ft_strdup(ms->env->value);
			ms->env = startenv;
			return ;
		}
		ms->env = ms->env->next;
	}
	ms->env = startenv;
}
