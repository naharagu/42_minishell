/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:32:54 by shimakaori        #+#    #+#             */
/*   Updated: 2023/02/28 11:13:35 by shimakaori       ###   ########.fr       */
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
		other_error(ms, "error", "unclosed quotes", 1);
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
		if (red_lstsize(ms->exec->red) == 1 \
			&& ft_strlen(ms->exec->red->str) < 3)
			syntax_error(ms, "newline", 0);
		if (ms->exec->cmdtype == NO_CMD)
			other_error(ms, ms->exec->cmd->str, "command not found", 127);
		ms->exec = ms->exec->next;
	}
	ms->exec = startexec;
}

void	error_expansion( t_minishell *ms, t_execlist *exec, size_t i)
{
	char		*env;

	if (exec->redtype == 2 && i > 1)
	{
		env = ft_strjoin("$", exec->env->key);
		other_error(ms, env, "ambiguous redirect", 1);
		free(env);
	}
}
