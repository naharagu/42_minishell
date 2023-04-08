/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:36:16 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/08 18:25:23 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_quoted_cmd(t_cmdlist *cmd, char c);
static void	ms_strtrim_cmd(t_cmdlist *cmd, char c, char **original);
static char	**make_split_cmd(t_cmdlist *cmd, char c, char **original);

char	*assign_value_cmd(t_minishell *ms, t_cmdlist *cmd, char *str)
{
	char	*start;
	char	*tmp;
	char	*old;

	old = NULL;
	while (*str)
	{
		start = str;
		while (*str && is_quoted_cmd(cmd, *str))
			str++;
		while (*str && *str != '$')
			str++;
		tmp = ft_substr(str, 0, str - start);
		start = str;
		if (tmp && ft_strnstr(tmp, "$", ft_strlen(tmp)))
			tmp = expand_env(ms, cmd, tmp);
		else if (tmp && cmd->quote != NO_QUOTE)
			tmp = trim_quote_cmd(cmd, tmp);
		if (old)
			tmp = ft_strjoin(old, tmp);
		old = ft_strdup(tmp);
		free(tmp);
		str++;
	}
	return (old);
}

char	*trim_quote_cmd(t_cmdlist *cmd, char *tmp)
{
	char	*result;

	if (cmd->quote == END_S_QUOTE)
	{
		result = strtrim_cmd(tmp, '\'');
	}
	else if (cmd->quote == END_D_QUOTE)
	{
		result = strtrim_cmd(tmp, '\"');
	}
	return (result);
}

char	*strtrim_cmd(char *str, char c)
{
	char	**split;
	char	*tmp;
	char	*old;
	size_t	i;

	i = 1;
	split = split_cmd(str, c);
	if (!split || !split[0])
		return (NULL);
	tmp = ft_strdup(split[0]);
	free(split[0]);
	while (split[i] && split[i][0] != '\0')
	{
		old = ft_strdup(tmp);
		free(tmp);
		tmp = ft_strjoin(old, split[i]);
		free(old);
		free(split[i]);
		i++;
	}
	free(split);
	return (tmp);
}

static char	**split_cmd(char *tmp, char c)
{
	char	**split;

	split = ft_split(tmp, c);
	if (!split || !split[0])
	{
		free(split[0]);
		free(split);
		return (NULL);
	}
	return (split);
}

static bool	is_quoted_cmd(t_cmdlist *cmd, char c)
{
	if (c == '\'' && cmd->quote == S_QUOTE)
		cmd->quote = END_S_QUOTE;
	else if (c == '\"' && cmd->quote == D_QUOTE)
		cmd->quote = END_D_QUOTE;
	else if (c == '\'' && (cmd->quote == NO_QUOTE || \
		cmd->quote == END_S_QUOTE || cmd->quote == END_D_QUOTE))
		cmd->quote = S_QUOTE;
	else if (c == '\"' && (cmd->quote == NO_QUOTE || \
		cmd->quote == END_S_QUOTE || cmd->quote == END_D_QUOTE))
		cmd->quote = D_QUOTE;
	else if (c != '\'' && c != '\"' && \
		(cmd->quote == END_S_QUOTE || cmd->quote == END_D_QUOTE))
		cmd->quote = NO_QUOTE;
	if (cmd->quote == S_QUOTE || cmd->quote == D_QUOTE || \
		cmd->quote == END_S_QUOTE || cmd->quote == END_D_QUOTE)
		return (true);
	else
		return (false);
}
