/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:36:16 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/09 13:58:10 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*trim_quote_cmd(t_cmdlist *cmd, char *tmp);
static bool	is_quoted_cmd(t_cmdlist *cmd, char c);

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
