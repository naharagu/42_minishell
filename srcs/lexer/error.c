/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:32:54 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/07 12:50:46 by naharagu         ###   ########.fr       */
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

void	error_parser_mslist(t_minishell *ms)
{
	t_mslist	*start;

	start = ms->list;
	while (ms->list)
	{
		if (*ms->list->str == '|' && ms->list->next == NULL)
			other_error(ms, "error", "no command after pipe", 1);
		ms->list = ms->list->next;
	}
	ms->list = start;
}

int	error_parser_execlist(t_minishell *ms)
{
	t_redlist	*startred;

	startred = ms->exec->red;
	if (ms->exec->redtype != NO_REDIRECT && ms->exec->red)
	{
		while (ms->exec->red)
		{
			if (ft_strnstr(ms->exec->red->str, ">>>>", \
				ft_strlen(ms->exec->red->str)))
				return (syntax_error( ">>", 1));
			else if (ft_strnstr(ms->exec->red->str, ">>>", \
				ft_strlen(ms->exec->red->str)))
				return (syntax_error( ">", 1));
			else if (ft_strnstr(ms->exec->red->str, "<<<<", \
				ft_strlen(ms->exec->red->str)))
				return (syntax_error( "<", 1));
			else if (ft_strnstr(ms->exec->red->str, ">", \
				ft_strlen(ms->exec->red->str)) && !(ms->exec->red->next))
				return (syntax_error( "newline", 258));
			ms->exec->red = ms->exec->red->next;
		}
	}
	ms->exec->red = startred;
	return (EXIT_SUCCESS);
}

void	error_expandedred(t_minishell *ms, t_redlist *red, char *original)
{
	if (!(red->str) || ft_strchr(red->str, ' '))
		other_error(ms, original, "ambiguous redirect", 1);
}

void	error_command( t_minishell *ms)
{
	if (ms->exec->cmdtype == NO_CMD && ms->exec->redtype == NO_REDIRECT)
		other_error(ms, ms->exec->cmdline[0], "command not found", 127);
}
