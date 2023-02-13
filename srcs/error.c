/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:32:54 by shimakaori        #+#    #+#             */
/*   Updated: 2023/02/13 22:35:37 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_exit(char *str, size_t flag)
{
	if (flag == SYNTAX)
		printf("minishell: syntax error near unexpected token `%s'\n", str);
	else
		printf("minishell: error `%s'\n", str);
	exit(EXIT_FAILURE);
}

void	error_lexer(t_minishell *ms)
{
	if (*ms->list->str == '|')
		error_exit("|", SYNTAX);
	if (ms->quote == S_QUOTE || ms->quote == D_QUOTE)
		error_exit("unclosed quotes", 0);
}

void	error_parser(t_minishell *ms)
{
	t_mslist	*start;
	t_execlist	*startexec;

	start = ms->list;
	startexec = ms->exec;
	while (ms->list)
	{
		if (*ms->list->str == '|' && ms->list->next == NULL)
			error_exit("No Command After Pipe", 0);
		ms->list = ms->list->next;
	}
	ms->list = start;
	while (ms->exec)
	{
		if (red_lstsize(ms->exec->red) == 1)
			error_exit("newline", SYNTAX);
		ms->exec = ms->exec->next;
	}
	ms->exec = startexec;
}
