/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:36:16 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/05 23:06:01 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_status;
static void	ms_strtrim_cmd(t_cmdlist *cmd, char c, char **original);
static char	**make_split_cmd(t_cmdlist *cmd, char c, char **original);
static void	expand_env_cmd(t_minishell *ms, t_cmdlist *cmd, char *tmp, \
			char **original);

void	trim_quote_cmd(t_cmdlist *cmd, char c, char **original)
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

void	assign_value_cmd(t_minishell *ms, t_cmdlist *cmd, char **original)
{
	char	**split;
	char	*tmp;
	char	*old;
	size_t	i;

	i = 0;
	if (ft_strnstr(cmd->str, "$", ft_strlen(cmd->str)) \
		&& cmd->quote != S_QUOTE)
		split = make_split_cmd(cmd, '$', original);
	else if
	if (!split)
		return ;
	while (split[i] && split[i][0] != '\0')
	{
		tmp = expand_env_cmd(ms, cmd, split[i]);
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

static void	ms_strtrim_cmd(t_cmdlist *cmd, char c, char **original)
{
	char	**split;
	char	*tmp;
	char	*old;
	size_t	i;

	i = 1;
	split = make_split_cmd(cmd, c, original);
	if (!split)
		return ;
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
// splitにquoteflag持たせる？

char	**make_split_cmd(t_cmdlist *cmd, char c, char **original)
{
	char	**split;

	split = ft_split(cmd->str, c);
	if (!split || !split[0])
	{
		free(*original);
		cmd->str = NULL;
		return (NULL);
	}
	return (split);
}

void	expand_env_cmd(t_minishell *ms, t_cmdlist *cmd, char *tmp)
{
	t_envlist	*startenv;

	startenv = ms->env;
	ms->env = ms->env->next;
	while (tmp && ms->env)
	{
		if (tmp && !(ft_strncmp(tmp, "?", ft_strlen(tmp))))
		{
			ms->env = startenv;
			return (ft_itoa(g_status));
		}
		if (!(ft_strncmp(ms->env->key, tmp, ft_strlen(tmp))))
		{
			ms->env = startenv;
			return (ft_strdup(ms->env->value));
		}
		ms->env = ms->env->next;
	}
	ms->env = startenv;
	return (NULL);
}
