/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:32:54 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/26 09:43:07 by naharagu         ###   ########.fr       */
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
	t_execlist	*startexec;

	startexec = ms->exec;
	while (ms->exec)
	{
		if (ms->exec->redtype != NO_REDIRECT)
		{
			if (ft_strnstr(ms->exec->red->str, ">>>>", 4))
				syntax_error(ms, ">>", 1);
			else if (ft_strnstr(ms->exec->red->str, ">>>", 3))
				syntax_error(ms, ">", 1);
			else if (ft_strnstr(ms->exec->red->str, "<<<<", 4))
				syntax_error(ms, "<", 1);
			else if (red_lstsize(ms->exec->red) < 2 && \
				!(ft_strnstr(ms->exec->red->str, ">&", \
				ft_strlen(ms->exec->red->str))))
				syntax_error(ms, "newline", 258);
		}
		ms->exec = ms->exec->next;
	}
	ms->exec = startexec;
}

void	error_expansion_cmd( t_minishell *ms)
{
	if (ms->exec->cmdtype == NO_CMD && ms->exec->redtype == NO_REDIRECT)
		other_error(ms, ms->exec->cmd->str, "command not found", 127);
}

void	error_expansion_red( t_minishell *ms)
{
	char		*env;

	if (ms->exec->redtype == OUTPUT && ft_strchr(ms->exec->red->next->str, ' '))
	{
		env = ft_strjoin("$", ms->env->key);
		other_error(ms, env, "ambiguous redirect", 1);
		free(env);
	}
}