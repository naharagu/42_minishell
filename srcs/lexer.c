/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:59:13 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/14 16:04:12 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_mslist(t_minishell *ms, char *start, char *line);

void	lexer(t_minishell *ms)
{
	char		*start;

	while (*ms->line)
	{
		start = ms->line;
		while (*ms->line && is_quoted(*ms->line, ms))
			ms->line++;
		while (*ms->line && !(is_space(*ms->line)) && \
			!(is_metachara(*ms->line)))
			ms->line++;
		add_mslist(ms, start, ms->line);
		while (*ms->line && is_space(*ms->line))
			ms->line++;
		start = ms->line;
		if (is_metachara(*ms->line) || ft_isdigit(*ms->line))
		{
			while (*ms->line && (is_metachara(*ms->line) \
			|| ft_isdigit(*ms->line) || ft_isalpha(*ms->line)))
				ms->line++;
			add_mslist(ms, start, ms->line);
		}
		while (*ms->line && is_space(*ms->line))
			ms->line++;
	}
	error_lexer(ms);
}

void	add_mslist(t_minishell *ms, char *start, char *line)
{
	t_mslist	*tmp;
	size_t		len;

	len = line - start;
	if (len > 0)
	{
		tmp = ms_lstnew(len, start);
		ms_lstadd_back(&ms->list, tmp);
	}
}
