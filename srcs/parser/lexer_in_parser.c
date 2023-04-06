/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_in_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:03:38 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/06 15:31:44 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_status;
bool	is_quoted_cmd(char c, t_cmdlist *cmd);

char	**lexer_cmd(t_cmdlist *cmd, char **original)
{
	char	**split;
	char	*first;
	char	*start;
	char	*tmp;
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	tmp = ft_strdup(cmd->str);
	first = tmp;
	while (*tmp)
	{
		if (*tmp == '$')
			count++;
		tmp++;
	}
	tmp = first;
	split = ft_calloc(sizeof(char *), count + 1);
	if (!split)
		return (NULL);
	while (*tmp)
	{
		start = tmp;
		while (*tmp && is_quoted_cmd(*tmp, cmd))
			tmp++;
		if ((tmp - start) > 0)
			split[i] = ft_substr(start, 0, tmp - start);
		start = tmp;
		if (*tmp == '$')
		{
			tmp++;
			while (*tmp && *tmp != '$')
				tmp++;
		}
		if ((tmp - start) > 0 && split[i])
			split[i + 1] = ft_substr(start, 0, tmp - start);
		else if ((tmp - start) > 0 && !split[i])
			split[i] = ft_substr(start, 0, tmp - start);
		i++;
	}
	if (!split[0])
	{
		free(first);
		free(*original);
		cmd->str = NULL;
		return (NULL);
	}
	i = 0;
	while (split[i])
	{
		printf("split[%zu]= %s", i, split[i]);
		i++;
	}
	free(first);
	return (split);
}

bool	is_quoted_cmd(char c, t_cmdlist *cmd)
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
