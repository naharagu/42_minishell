/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 11:16:37 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/16 09:32:23 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*get_old(char **new, char **old)
{
	char	*result;

	result = NULL;
	if (!(*old))
		result = ft_strdup(*new);
	else if (old)
	{
		result = ft_strjoin(*old, *new);
		free(*old);
	}
	free(*new);
	return (result);
}

char	*get_env(t_minishell *ms, char *str)
{
	t_envlist	*tmpenv;

	if (*str == '$' && ft_strlen(str) > 1)
		str++;
	if (!(ft_strncmp(str, "?", ft_strlen(str))))
		return (ft_itoa(g_status));
	tmpenv = ms->env->next;
	while (tmpenv)
	{
		if (!ft_strncmp(tmpenv->key, str, ft_strlen(str)))
			return (ft_strdup(tmpenv->value));
		tmpenv = tmpenv->next;
	}
	return (ft_strdup(""));
}
