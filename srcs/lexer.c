/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:59:13 by shimakaori        #+#    #+#             */
/*   Updated: 2023/02/17 10:26:35 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*add_mslist(char *line, t_mslist	**list);
static bool	is_quoted(char c, t_minishell *ms);
static bool	is_delimiter(char c);
static bool	is_space(char c);

void	lexer(t_minishell *ms)
{
	t_mslist	*tmp;
	char		*start;
	size_t		len;

	while (*ms->line)
	{
		len = 0;
		start = ms->line;
		while (*ms->line && is_quoted(*ms->line, ms))
			ms->line++;
		while (*ms->line && !(is_space(*ms->line)) \
			&& !(is_delimiter(*ms->line)))
			ms->line++;
		len = ms->line - start;
		if (len > 0)
		{
			tmp = ms_lstnew(len, start);
			ms_lstadd_back(&ms->list, tmp);
		}
		else if (is_delimiter(*ms->line))
			ms->line = add_mslist(ms->line, &ms->list);
		ms->line++;
	}
	error_lexer(ms);
}

static char	*add_mslist(char *line, t_mslist	**list)
{
	t_mslist	*tmp;
	char		*start;
	size_t		len;

	len = 0;
	start = line;
	while (is_delimiter(*line))
		line++;
	len = line - start;
	tmp = ms_lstnew(len, start);
	ms_lstadd_back(list, tmp);
	return (line);
}

static bool	is_quoted(char c, t_minishell *ms)
{
	if (c == '\'' && ms->quote == S_QUOTE)
		ms->quote = END_S_QUOTE;
	else if (c == '\"' && ms->quote == D_QUOTE)
		ms->quote = END_D_QUOTE;
	else if (c == '\'' && (ms->quote == NO_QUOTE || \
		ms->quote == END_S_QUOTE || ms->quote == END_D_QUOTE))
		ms->quote = S_QUOTE;
	else if (c == '\"' && (ms->quote == NO_QUOTE || \
		ms->quote == END_S_QUOTE || ms->quote == END_D_QUOTE))
		ms->quote = D_QUOTE;
	else if (c != '\'' && c != '\"' && \
		(ms->quote == END_S_QUOTE || ms->quote == END_D_QUOTE))
		ms->quote = NO_QUOTE;
	if (ms->quote == S_QUOTE || ms->quote == D_QUOTE || \
		ms->quote == END_S_QUOTE || ms->quote == END_D_QUOTE)
		return (true);
	else
		return (false);
}

static bool	is_delimiter(char c)
{
	if (c == '|' || c == ';')
		return (true);
	else
		return (false);
}

static bool	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\r' || c == '\n' \
	|| c == '\v' || c == '\f' || c == '\0')
		return (true);
	else
		return (false);
}
