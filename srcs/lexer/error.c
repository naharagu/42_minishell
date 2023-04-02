/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:32:54 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/01 16:11:50 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_lexer(t_minishell *ms)
{
	if (!(ms->list))
		minishell(ms);
	if (ms->list && *ms->list->str == '|')
		syntax_error(ms, "|", 258);
	if (ms->quote == S_QUOTE || ms->quote == D_QUOTE)
		syntax_error(ms, "unclosed quotes", 1);
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

void	error_parser_execlist(t_minishell *ms)
{
	t_redlist	*startred;

	startred = ms->exec->red;
	if (ms->exec->redtype != NO_REDIRECT && ms->exec->red)
	{
		while (ms->exec->red)
		{
			if (ft_strnstr(ms->exec->red->str, ">>>>", \
				ft_strlen(ms->exec->red->str)))
				syntax_error(ms, ">>", 1);
			else if (ft_strnstr(ms->exec->red->str, ">>>", \
				ft_strlen(ms->exec->red->str)))
				syntax_error(ms, ">", 1);
			else if (ft_strnstr(ms->exec->red->str, "<<<<", \
				ft_strlen(ms->exec->red->str)))
				syntax_error(ms, "<", 1);
			else if (ft_strnstr(ms->exec->red->str, ">", \
				ft_strlen(ms->exec->red->str)) && !(ms->exec->red->next))
				syntax_error(ms, "newline", 258);
			ms->exec->red = ms->exec->red->next;
		}
	}
	ms->exec->red = startred;
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
