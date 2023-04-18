/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 11:16:37 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/18 10:52:00 by shimakaori       ###   ########.fr       */
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
			if (!(ft_strncmp("<<", tmp_red->str, 2)) && tmp_red->next)
				tmp_red = tmp_red->next;
			else if (expand_red(ms, tmp_red, tmp_red->str) == EXIT_FAILURE)
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

char	*trim_quote(char *str, int c)
{
	char	**split;
	char	*result;
	char	*old;
	size_t	i;

	i = 1;
	split = ft_split(str, c);
	if (!split)
		return (NULL);
	if (!split[0])
	{
		free(split);
		return (NULL);
	}
	old = ft_strdup(split[0]);
	while (split[i] && split[i][0] != '\0')
	{
		result = ft_strjoin(old, split[i]);
		free (old);
		old = result;
		i++;
	}
	free_split(split);
	return (old);
}

void	free_split(char **split)
{
	size_t	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
