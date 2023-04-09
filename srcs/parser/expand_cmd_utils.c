/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:36:16 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/09 14:53:23 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_status;
static char	*trim_quote_cmd(t_cmdlist *cmd, char *str, int c);

char	*assign_value_cmd(t_minishell *ms, t_cmdlist *cmd, char *str)
{
	char	*new;

	if (!str)
		return (NULL);
	if (!(ft_strncmp("", str, ft_strlen(str))))
		return ("");
	if (*str == '\'' || *str == '\"')
		str = trim_quote_cmd(cmd, str, *str);
	if (ft_strnstr(str, "$", ft_strlen(str)))
		new = expand_env_cmd(ms, cmd, str);
	// else if (cmd->quote == END_S_QUOTE)
	// 	new = trim_quote_cmd(cmd, str, '\'');
	// else if (cmd->quote == END_D_QUOTE)
	// 	new = trim_quote_cmd(cmd, str, '\"');
	else
		new = ft_strdup(str);
	return (new);
}

static char	*trim_quote_cmd(t_cmdlist *cmd, char *str, int c)
{
	char	**split;
	char	*tmp;
	char	*old;
	size_t	i;

	(void)cmd;
	i = 1;
	split = ft_split(str, c);
	if (!split)
		return (NULL);
	if (!split[0])
	{
		free(split);
		return (NULL);
	}
	tmp = ft_strdup(split[0]);
	free(split[0]);
	while (split[i] && split[i][0] != '\0')
	{
		old = tmp;
		tmp = ft_strjoin(old, split[i]);
		free(split[i]);
		i++;
	}
	free(split);
	return (tmp);
}

char	*expand_env_cmd(t_minishell *ms, t_cmdlist *cmd, char *str)
{
	t_envlist	*tmpenv;
	char		*start;
	char		*tmp;
	char		*old;
	char		*new;

	tmpenv = ms->env->next;
	while (*str)
	{
		start = str;
		if (*str == '$')
			str++;
		while (*str && *str == '\'' && *str == '\"')
			str++;
		while (*str && *str != '$' && *str != '\'' && *str != '\"')
			str++;
		tmp = ft_substr(start, 0, str - start);
		start = str;
		if (*tmp == '$' && cmd->quote != END_S_QUOTE && ft_strlen(tmp) > 1)
		{
			tmp++;
			if (!(ft_strncmp(tmp, "?", ft_strlen(tmp))))
			{
				new = ft_itoa(g_status);
				tmp++;
			}
			while (tmpenv)
			{
				if (!(ft_strncmp(tmpenv->key, tmp, ft_strlen(tmp))))
				{
					new = ft_strdup(tmpenv->value);
					tmp += ft_strlen(tmpenv->key);
				}
				tmpenv = tmpenv->next;
			}
		}
		new = ft_strjoin(old, new);
		old = ft_strdup(new);
		free(tmp);
		free(new);
	}
	return (old);
}
