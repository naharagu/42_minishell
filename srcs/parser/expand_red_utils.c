/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_red_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:38:12 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/06 09:07:27 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_status;
static void	ms_strtrim_red(t_redlist *red, char c, char **original);
static char	**make_split_red(t_redlist *red, char c, char **original);
static void	expand_env_red(t_minishell *ms, t_redlist *red, char *tmp, \
			char **original);

void	trim_quote_red(t_redlist *red, char c, char **original)
{
	if (c == '\'' && red->quote == NO_QUOTE)
	{
		red->quote = S_QUOTE;
		ms_strtrim_red(red, '\'', original);
	}
	else if (c == '\"' && red->quote == NO_QUOTE)
	{
		red->quote = D_QUOTE;
		ms_strtrim_red(red, '\"', original);
	}
}

void	assign_value_red(t_minishell *ms, t_redlist *red, char **original)
{
	char		*tmp;

	tmp = NULL;
	if (red->str && *red->str == '$' && red->quote != S_QUOTE \
		&& ft_strlen(red->str) > 1)
	tmp = red->str;
	tmp++;
	if (tmp && !(ft_strncmp(tmp, "?", ft_strlen(tmp))))
	{
		free(*original);
		red->str = ft_itoa(g_status);
		return ;
	}
	else
		expand_env_red(ms, red, tmp, original);
}

static void	ms_strtrim_red(t_redlist *red, char c, char **original)
{
	char	**split;
	char	*tmp;
	char	*old;
	size_t	i;

	i = 1;
	split = make_split_red(red, c, original);
	if (!split)
		return ;
	tmp = split[0];
	while (split[i] && split[i][0] != '\0')
	{
		old = ft_strdup(tmp);
		free(tmp);
		tmp = ft_strjoin(old, split[i]);
		free(old);
		free(split[i]);
		i++;
	}
	free(*original);
	red->str = ft_strdup(tmp);
	free(tmp);
	free(split);
}

char	**make_split_red(t_redlist *red, char c, char **original)
{
	char	**split;

	split = ft_split(red->str, c);
	if (!split || !split[0])
	{
		free(*original);
		red->str = NULL;
		return (NULL);
	}
	return (split);
}

void	expand_env_red(t_minishell *ms, t_redlist *red, char *tmp, \
		char **original)
{
	t_envlist	*startenv;

	startenv = ms->env;
	ms->env = ms->env->next;
	while (tmp && ms->env)
	{
		if (!(ft_strncmp(ms->env->key, tmp, ft_strlen(tmp))))
		{
			free(*original);
			red->str = ft_strdup(ms->env->value);
			ms->env = startenv;
			return ;
		}
		ms->env = ms->env->next;
	}
	ms->env = startenv;
	free(*original);
	red->str = NULL;
}
