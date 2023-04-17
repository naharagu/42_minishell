/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 12:13:46 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/17 12:15:35 by shimakaori       ###   ########.fr       */
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

int	quotedstr(char *str)
{
	char	*start;

	start = str;
	while (*str && (*str == '\'' || *str == '\"'))
		str++;
	while (*str && (*str != '\'' || *str != '\"'))
		str++;
	while (*str && (*str == '\'' || *str == '\"'))
		str++;
	return (str - start);
}

bool	is_upperchar(char c)
{
	if ((c >= 'A' && c <= 'Z') || c == '_')
		return (true);
	else
		return (false);
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
