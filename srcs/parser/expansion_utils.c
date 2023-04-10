/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 12:13:46 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/10 12:32:29 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_quoted_cmd(t_cmdlist *cmd, char c)
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

bool	is_quoted_red(t_redlist *red, char c)
{
	if (c == '\'' && red->quote == S_QUOTE)
		red->quote = END_S_QUOTE;
	else if (c == '\"' && red->quote == D_QUOTE)
		red->quote = END_D_QUOTE;
	else if (c == '\'' && (red->quote == NO_QUOTE || \
		red->quote == END_S_QUOTE || red->quote == END_D_QUOTE))
		red->quote = S_QUOTE;
	else if (c == '\"' && (red->quote == NO_QUOTE || \
		red->quote == END_S_QUOTE || red->quote == END_D_QUOTE))
		red->quote = D_QUOTE;
	else if (c != '\'' && c != '\"' && \
		(red->quote == END_S_QUOTE || red->quote == END_D_QUOTE))
		red->quote = NO_QUOTE;
	if (red->quote == S_QUOTE || red->quote == D_QUOTE || \
		red->quote == END_S_QUOTE || red->quote == END_D_QUOTE)
		return (true);
	else
		return (false);
}

char	*get_old(char **new, char **old)
{
	char	*result;

	result = NULL;
	if (!(*old))
		result = ft_strdup(*new);
	else if (old)
	{
		result = ft_strjoin(*old, *new);
		free(*old);
	}
	free(*new);
	return (result);
}

void	free_split(char **split)
{
	size_t	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
