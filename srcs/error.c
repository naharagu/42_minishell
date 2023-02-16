/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:32:54 by shimakaori        #+#    #+#             */
/*   Updated: 2023/02/16 12:39:02 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *str, size_t flag, t_minishell *ms)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (flag == SYNTAX)
	{
		ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd("\'", STDERR_FILENO);
	}
	else
	{
		ft_putendl_fd(str, STDERR_FILENO);
	}
	if (ms->startline)
		free(ms->startline);
	if (ms->list)
		ms_lstclear(&ms->list);
	if (ms->exec)
		exec_lstclear(&ms->exec);
	minishell(ms);
}

void	error_lexer(t_minishell *ms)
{
	if (*ms->list->str == '|')
	{
		ms->exit_status = 258;
		print_error("|", SYNTAX, ms);
	}
	if (ms->quote == S_QUOTE || ms->quote == D_QUOTE)
	{
		print_error("error: unclosed quotes", 0, ms);
	}
}

void	error_parser_mslist(t_minishell *ms)
{
	t_mslist	*start;

	start = ms->list;
	while (ms->list)
	{
		if (*ms->list->str == '|' && ms->list->next == NULL)
		{
			print_error("error: no command after pipe", 0, ms);
		}
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
		if (red_lstsize(ms->exec->red) == 1)
		{
			print_error("newline", SYNTAX, ms);
		}
		if (ms->exec->cmdtype == NO_CMD)
		{
			ms->exit_status = 127;
			print_error(ft_strjoin(ms->exec->cmd->str, \
				": command not found"), 0, ms);
		}
		ms->exec = ms->exec->next;
	}
	ms->exec = startexec;
}

void	error_expansion(t_execlist *exec, size_t i, t_minishell *ms)
{
	char		*env;

	if (exec->redtype == 2 && i > 1)
	{
		env = ft_strjoin("$", exec->env->key);
		print_error(ft_strjoin(env, ": ambiguous redirect"), 0, ms);
	}
}
