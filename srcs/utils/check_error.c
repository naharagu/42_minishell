/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:32:54 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/08 15:35:00 by shimakaori       ###   ########.fr       */
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

char	*get_errchar(size_t count_in, size_t count_out)
{
	if (count_in > 3 && count_out > 0)
		return ("<>");
	else if (count_in > 3)
		return ("<");
	else if (count_out > 3 || (count_in > 1 && count_out > 1))
		return (">>");
	else if (count_out > 2 || (count_in > 1 && count_out > 0))
		return (">");
	return (NULL);
}

int	error_parser_execlist(t_minishell *ms)
{
	t_redlist	*tmp_red;
	size_t		count_out;
	size_t		count_in;
	char		*err;

	if (ms->exec->redtype == NO_REDIRECT)
		return (EXIT_SUCCESS);
	tmp_red = ms->exec->red;
	count_out = 0;
	count_in = 0;
	while (tmp_red)
	{
		if (ft_strnstr(tmp_red->str, "<", ft_strlen(tmp_red->str)))
			count_in++;
		if (ft_strnstr(tmp_red->str, ">", ft_strlen(tmp_red->str)))
			count_out++;
		if (ft_strnstr(tmp_red->str, ">", ft_strlen(tmp_red->str)) \
			&& !(tmp_red->next))
			return (syntax_error("newline", 258));
		tmp_red = tmp_red->next;
	}
	err = get_errchar(count_in, count_out);
	if (err)
		return (syntax_error(err, 1));
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
