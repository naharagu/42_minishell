/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:59:13 by shimakaori        #+#    #+#             */
/*   Updated: 2023/01/24 09:59:44 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer(t_minishell *ms)
{
	t_mslist	*tmp;
	char		*start;
	size_t		len;

	while (*ms->input)
	{
		len = 0;
		start = ms->input;
		while (*ms->input && is_quoted(*ms->input, ms))
			ms->input++;
		while (*ms->input && !(is_space(*ms->input)) \
			&& !(is_delimiter(*ms->input)))
			ms->input++;
		len = ms->input - start;
		if (len > 0)
		{
			tmp = ms_lstnew(len, start);
			ms_lstadd_back(&ms->list, tmp);
		}
		if (is_delimiter(*ms->input))
			ms->input = add_list(ms->input, &ms->list);
		ms->input++;
	}
}

char	*add_list(char *input, t_mslist	**list)
{
	t_mslist	*tmp;
	char		*start;
	size_t		len;

	len = 0;
	start = input;
	while (is_delimiter(*input))
		input++;
	len = input - start;
	tmp = ms_lstnew(len, start);
	ms_lstadd_back(list, tmp);
	input--;
	return (input);
}
