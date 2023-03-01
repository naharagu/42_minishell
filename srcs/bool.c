/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:37:06 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/01 12:44:08 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_quoted(char c, t_minishell *ms)
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

bool	is_delimiter(char c)
{
	if (c == '|' || c == ';' || c == '<' || c == '>')
		return (true);
	else
		return (false);
}

bool	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\r' || c == '\n' \
	|| c == '\v' || c == '\f' || c == '\0')
		return (true);
	else
		return (false);
}

bool	is_metachara(char c)
{
	if (ft_strchr("&;()<> \t\n", c))
		return (true);
	else
		return (false);
}
