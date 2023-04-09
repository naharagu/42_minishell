/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:36:16 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/09 23:54:43 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_status;
static char	*trim_quote_cmd(char *str, int c);
static char	*get_newstr(t_minishell *ms, t_cmdlist *cmd, char *str);

char	*assign_value_cmd(t_minishell *ms, t_cmdlist *cmd, char *str)
{
	char	*new;

	new = NULL;
	if (!str)
		return (NULL);
	if (!(ft_strncmp("", str, ft_strlen(str))))
		return ("");
	if (*str == '\'' || *str == '\"')
		str = trim_quote_cmd(str, *str);
	if (ft_strnstr(str, "$", ft_strlen(str)))
		new = expand_env_cmd(ms, cmd, str);
	else
		new = ft_strdup(str);
	return (new);
}

static char	*trim_quote_cmd(char *str, int c)
{
	char	**split;
	char	*tmp;
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
	char		*start;
	char		*tmp;
	char		*old;
	char		*new;
	char		*result;

	old = NULL;
	//printf("str= %s\n", str);//
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
		//printf("1tmp= %s\n", tmp);//
		start = str;
		new = get_newstr(ms, cmd, tmp);
		free(tmp);
		//printf("new= %s\n", new);//
		if (old)
		{
			result = ft_strjoin(old, new);
			free(old);
			free(new);
			old = result;
		}
		else if (!old)
		{
			old = ft_strdup(new);
			printf("old= %s\n", old);//
			free(new);
		}
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
		return (NULL);
	}
	return (ft_strdup(str));
}
