/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:32:54 by shimakaori        #+#    #+#             */
/*   Updated: 2023/02/25 17:07:21 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(t_minishell *ms, char *str, size_t flag)
{
	if (flag == EXIT_ERR)
	{
		ft_putendl_fd("error: ", STD_ERR);
		ft_putendl_fd(str, STD_ERR);
		all_free(ms);
		exit(EXIT_FAILURE);
	}
	else if (flag == SYNTAX_ERR)
	{
		ft_putstr_fd("minishell: ", STD_ERR);
		ft_putstr_fd("syntax error near unexpected token `", STD_ERR);
		ft_putstr_fd(str, STD_ERR);
		ft_putendl_fd("\'", STD_ERR);
	}
	else if (flag == OTHER_ERR)
	{
		ft_putstr_fd("minishell: ", STD_ERR);
		ft_putendl_fd(str, STD_ERR);
	}
	all_free(ms);
	minishell(ms);
}

void	error_lexer(t_minishell *ms)
{
	if (!(ms->list))
		minishell(ms);
	if (ms->list && *ms->list->str == '|')
	{
		ms->exit_status = 258;
		print_error(ms, "|", SYNTAX_ERR);
	}
	if (ms->quote == S_QUOTE || ms->quote == D_QUOTE)
	{
		print_error(ms, "error: unclosed quotes", OTHER_ERR);
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
			print_error(ms, "error: no command after pipe", OTHER_ERR);
		}
		ms->list = ms->list->next;
	}
	ms->list = start;
}

void	error_parser_execlist(t_minishell *ms)
{
	t_execlist	*startexec;
	char		*err_str;

	startexec = ms->exec;
	while (ms->exec)
	{
		if (red_lstsize(ms->exec->red) == 1 \
			&& ft_strlen(ms->exec->red->str) < 3)
		{
			print_error(ms, "newline", SYNTAX_ERR);
		}
		if (ms->exec->cmdtype == NO_CMD)
		{
			ms->exit_status = 127;
			err_str = ft_strjoin(ms->exec->cmd->str, ": command not found");
			print_error(ms, err_str, OTHER_ERR);
			free(err_str);
		}
		ms->exec = ms->exec->next;
	}
	ms->exec = startexec;
}

void	error_expansion(t_execlist *exec, size_t i, t_minishell *ms)
{
	char		*env;
	char		*err_str;

	if (exec->redtype == 2 && i > 1)
	{
		env = ft_strjoin("$", exec->env->key);
		err_str = ft_strjoin(env, ": ambiguous redirect");
		print_error(ms, err_str, OTHER_ERR);
		free(env);
		free(err_str);
	}
}
