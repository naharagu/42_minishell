/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:59:13 by shimakaori        #+#    #+#             */
/*   Updated: 2023/02/28 16:35:43 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*add_mslist(char *line, t_mslist	**list);

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
		while (*ms->line && !(is_space(*ms->line)) && \
			!(is_delimiter(*ms->line)))
			ms->line++;
		len = ms->line - start;
		if (len > 0)
		{
			tmp = ms_lstnew(len, start);
			ms_lstadd_back(&ms->list, tmp);
		}
		else if (is_delimiter(*ms->line))
			ms->line = add_mslist(ms->line, &ms->list);
		if (*ms->line && is_space(*ms->line))
			ms->line++;
	}
	error_lexer(ms);
}

static char	*add_mslist(char *line, t_mslist **list)
{
	t_mslist	*tmp;
	char		*start;
	size_t		len;

	len = 0;
	start = line;
	while (is_delimiter(*line) || is_metachara(*line))
		line++;
	len = line - start;
	tmp = ms_lstnew(len, start);
	ms_lstadd_back(list, tmp);
	return (line);
}
