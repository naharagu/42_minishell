/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 11:16:37 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/10 21:56:26 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_cmd( t_minishell *ms, t_cmdlist *cmd, char *str);
static int	expand_red(t_minishell *ms, t_redlist *red, char *str);

int	expansion(t_minishell *ms)
{
	t_execlist	*tmp_exec;
	t_cmdlist	*tmp_cmd;
	t_redlist	*tmp_red;

	tmp_exec = ms->exec;
	while (tmp_exec)
	{
		tmp_cmd = tmp_exec->cmd;
		while (tmp_cmd)
		{
			expand_cmd(ms, tmp_cmd, tmp_cmd->str);
			tmp_cmd = tmp_cmd->next;
		}
		tmp_red = tmp_exec->red;
		while (tmp_red)
		{
			if (expand_red(ms, tmp_red, tmp_red->str) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			tmp_red = tmp_red->next;
		}
		tmp_exec = tmp_exec->next;
	}
	return (EXIT_SUCCESS);
}

static void	expand_cmd( t_minishell *ms, t_cmdlist *cmd, char *str)
{
	char	*start;
	char	*tmp;
	char	*old;
	char	*new;

	old = NULL;
	while (*str)
	{
		start = str;
		while (*str && is_quoted_cmd(cmd, *str))
			str++;
		if (*str == '$')
			str++;
		while (*str && *str != '$')
			str++;
		tmp = ft_substr(start, 0, str - start);
		start = str;
		new = assign_value_cmd (ms, cmd, &tmp);
		old = get_old(&new, &old);
	}
	free(cmd->str);
	cmd->str = old;
}

static int	expand_red(t_minishell *ms, t_redlist *red, char *str)
{
	char	*original;
	char	*start;
	char	*tmp;
	char	*old;
	char	*new;

	original = str;
	old = NULL;
	while (*str)
	{
		start = str;
		while (*str && is_quoted_red(red, *str))
			str++;
		if (*str == '$')
			str++;
		while (*str && *str != '$')
			str++;
		tmp = ft_substr(start, 0, str - start);
		start = str;
		new = assign_value_red (ms, red, &tmp);
		old = get_old(&new, &old);
	}
	free(red->str);
	red->str = old;
	return (error_expandedred(red, original));
}
