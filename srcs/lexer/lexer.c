/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:59:13 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/10 15:43:35 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_mslist(t_minishell *ms, char *start, char *line);

int	lexer(t_minishell *ms)
{
	char		*tmp;
	char		*start;

	tmp = ms->line;
	while (*tmp)
	{
		start = tmp;
		while (*tmp && is_quoted(*tmp, ms))
			tmp++;
		while (*tmp && !(is_space(*tmp)) && !(is_metachara(*tmp)))
			tmp++;
		add_mslist(ms, start, tmp);
		start = tmp;
		if (*tmp && is_metachara(*tmp))
		{
			tmp++;
			add_mslist(ms, start, tmp);
			start = tmp;
		}
		while (*tmp && is_space(*tmp))
			tmp++;
	}
	return (error_lexer(ms));
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
