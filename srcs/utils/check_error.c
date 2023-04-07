/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:32:54 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/07 14:02:22 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_lexer(t_minishell *ms)
{
	if (!(ms->list))
		return (EXIT_FAILURE);
	if (ms->list && *ms->list->str == '|')
		return (syntax_error( "|", 258));
	if (ms->quote == S_QUOTE || ms->quote == D_QUOTE)
		return (syntax_error( "unclosed quotes", 2));
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

int	error_parser_execlist(t_minishell *ms)
{
	t_redlist	*tmp_red;

	if (ms->exec->redtype == NO_REDIRECT)
		return (EXIT_SUCCESS);
	tmp_red = ms->exec->red;
	while (tmp_red)
	{
		if (ft_strnstr(tmp_red->str, ">>>>", \
			ft_strlen(tmp_red->str)))
			return (syntax_error( ">>", 1));
		else if (ft_strnstr(tmp_red->str, ">>>", \
			ft_strlen(tmp_red->str)))
			return (syntax_error( ">", 1));
		else if (ft_strnstr(tmp_red->str, "<<<<", \
			ft_strlen(tmp_red->str)))
			return (syntax_error( "<", 1));
		else if (ft_strnstr(tmp_red->str, ">", \
			ft_strlen(tmp_red->str)) && !(tmp_red->next))
			return (syntax_error( "newline", 258));
		tmp_red = tmp_red->next;
	}
	return (EXIT_SUCCESS);
}

void	error_expandedred(t_redlist *red, char *original)
{
	if (!(red->str) || ft_strchr(red->str, ' '))
		other_error(original, "ambiguous redirect", 1);
}
