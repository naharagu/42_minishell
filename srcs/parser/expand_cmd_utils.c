/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:36:16 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/10 12:27:11 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_status;
static char	*trim_quote_cmd(char *str, int c);
static char	*expand_env_cmd(t_minishell *ms, t_cmdlist *cmd, char *str);
static char	*get_newstr(t_minishell *ms, t_cmdlist *cmd, char *str);

char	*assign_value_cmd(t_minishell *ms, t_cmdlist *cmd, char *str)
{
	char	*new;
	char	*tmp;

	new = NULL;
	tmp = NULL;
	if (!(ft_strncmp("\"\"", str, ft_strlen(str))) \
		|| !(ft_strncmp("\'\'", str, ft_strlen(str))))
		return (ft_strdup(""));
	if (ft_strnstr(str, "$", ft_strlen(str)) && (*str == '\'' || *str == '\"'))
	{
		tmp = trim_quote_cmd(str, *str);
		new = expand_env_cmd(ms, cmd, tmp);
		free (tmp);
	}
	else if (ft_strnstr(str, "$", ft_strlen(str)))
		new = expand_env_cmd(ms, cmd, str);
	else if (*str == '\'' || *str == '\"')
		new = trim_quote_cmd(str, *str);
	else
		new = ft_strdup(str);
	return (new);
}

static char	*trim_quote_cmd(char *str, int c)
{
	char	**split;
	char	*result;
	char	*old;
	size_t	i;

	i = 1;
	split = ft_split(str, c);
	if (!split)
		return (NULL);
	if (!split[0])
	{
		free(split);
		return (NULL);
	}
	old = ft_strdup(split[0]);
	while (split[i] && split[i][0] != '\0')
	{
		result = ft_strjoin(old, split[i]);
		free (old);
		old = result;
		i++;
	}
	free_split(split);
	return (old);
}

static char	*expand_env_cmd(t_minishell *ms, t_cmdlist *cmd, char *str)
{
	char		*start;
	char		*tmp;
	char		*old;
	char		*new;

	old = NULL;
	while (*str)
	{
		start = str;
		if (*str == '$')
			str++;
		while (*str && (*str == '\'' || *str == '\"'))
			str++;
		while (*str && *str != '$' && *str != '\'' && *str != '\"')
			str++;
		tmp = ft_substr(start, 0, str - start);
		start = str;
		new = get_newstr(ms, cmd, tmp);
		free(tmp);
		old = get_old(&new, &old);
	}
	return (old);
}

static char	*get_newstr(t_minishell *ms, t_cmdlist *cmd, char *str)
{
	t_envlist	*tmpenv;

	if (*str != '$' || cmd->quote == END_S_QUOTE)
		return (ft_strdup(str));
	else if (*str == '$' && cmd->quote != END_S_QUOTE && ft_strlen(str) > 1)
	{
		str++;
		if (!(ft_strncmp(str, "?", ft_strlen(str))))
			return (ft_itoa(g_status));
		tmpenv = ms->env->next;
		while (tmpenv)
		{
			if (!ft_strncmp(tmpenv->key, str, ft_strlen(str)))
				return (ft_strdup(tmpenv->value));
			tmpenv = tmpenv->next;
		}
		return (ft_strdup(""));
	}
	return (ft_strdup(str));
}
