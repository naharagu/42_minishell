/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:32:54 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/18 22:07:29 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_lexer(t_minishell *ms)
{
	if (!(ms->list))
		return (EXIT_FAILURE);
	if (ms->list && *ms->list->str == '|')
		return (syntax_error("|", 258));
	if (ms->quote == S_QUOTE || ms->quote == D_QUOTE)
		return (syntax_error("unclosed quotes", 2));
	return (EXIT_SUCCESS);
}

int	errror_parser_mslist(t_minishell *ms)
{
	t_mslist	*tmp_list;

	tmp_list = ms->list;
	while (tmp_list)
	{
		if (*tmp_list->str == '|' && tmp_list->next == NULL)
		{
			other_error("error", "no command after pipe", 1);
			return (EXIT_FAILURE);
		}
		tmp_list = tmp_list->next;
	}
	return (EXIT_SUCCESS);
}

int	error_expandedred(t_redlist *red, char *original)
{
	if (!(red->str) || ft_strchr(red->str, ' '))
	{
		other_error(original, "ambiguous redirect", 1);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
