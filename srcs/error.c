/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:32:54 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/28 15:06:17 by shimakaori       ###   ########.fr       */
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

	if (ms->exec->cmdtype == NO_CMD && ms->exec->redtype == NO_REDIRECT)
		other_error(ms, ms->exec->cmd->str, "command not found", 127);
	startred = ms->exec->red;
	if (ms->exec->redtype != NO_REDIRECT)
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

void	error_expansion_red( t_minishell *ms)
{
	char		*env;

	if (ms->exec->redtype == OUTPUT && ft_strchr(ms->exec->red->str, ' '))
	{
		env = ft_strjoin("$", ms->exec->env->key);
		other_error(ms, env, "ambiguous redirect", 1);
		free(env);
	}
}
