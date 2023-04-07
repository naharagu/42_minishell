/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:32:54 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/07 12:58:57 by naharagu         ###   ########.fr       */
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
	t_execlist	*tmp_exec;
	t_redlist	*tmp_red;

	tmp_exec = ms->exec;
	tmp_red = ms->exec->red;
	if (tmp_exec && tmp_exec->redtype != NO_REDIRECT)
	{
		while (tmp_red)
		{
			if (ft_strnstr(tmp_red ->str, ">>>>", \
				ft_strlen(tmp_red ->str)))
				return (syntax_error( ">>", 1));
			else if (ft_strnstr(tmp_red ->str, ">>>", \
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
		tmp_exec = tmp_exec->next;
		tmp_red = tmp_exec->red;
	}
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
