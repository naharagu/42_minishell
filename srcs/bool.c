/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:37:06 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/04 12:58:35 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_quoted(char c, t_minishell *ms)
{
	if (c == '\'' && ms->quote == S_QUOTE)
		ms->quote = END_S_QUOTE;
	else if (c == '\"' && ms->quote == D_QUOTE)
		ms->quote = END_D_QUOTE;
	else if (c == '\'' && (ms->quote == NO_QUOTE || \
		ms->quote == END_S_QUOTE || ms->quote == END_D_QUOTE))
		ms->quote = S_QUOTE;
	else if (c == '\"' && (ms->quote == NO_QUOTE || \
		ms->quote == END_S_QUOTE || ms->quote == END_D_QUOTE))
		ms->quote = D_QUOTE;
	else if (c != '\'' && c != '\"' && \
		(ms->quote == END_S_QUOTE || ms->quote == END_D_QUOTE))
		ms->quote = NO_QUOTE;
	if (ms->quote == S_QUOTE || ms->quote == D_QUOTE || \
		ms->quote == END_S_QUOTE || ms->quote == END_D_QUOTE)
		return (true);
	else
		return (false);
}

bool	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\r' || c == '\n' \
	|| c == '\v' || c == '\f' || c == '\0')
		return (true);
	else
		return (false);
}

bool	is_metachara(char c)
{
	if (ft_strchr("12|&;()<> \t", c))
		return (true);
	else
		return (false);
}

// bool	is_env(t_minishell *ms, char *delimiter)
// {
// 	t_execlist	*startexec;
// 	t_envlist	*startenv;

// 	startexec = ms->exec;
// 	while (ms->exec)
// 	{
// 		startenv = ms->exec->env;
// 		while (ms->exec->env)
// 		{
// 			if (ft_strnstr(delimiter, ms->exec->key, ft_strlen(delimiter)))
// 				return (true);
// 			else
// 				return (false);
// 			ms->exec->env = ms->exec->env->next;
// 		}
// 		ms->exec->env = startenv;
// 		ms->exec = ms->exec->next;
// 	}
// 	ms->exec = startexec;
// }
