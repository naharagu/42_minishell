/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_red_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:38:12 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/06 19:56:10 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_status;
static void	ms_strtrim_red(t_redlist *red, char c, char **original);
static char	**make_split_red(t_redlist *red, char c, char **original);

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
	char	**split;
	char	*tmp;
	size_t	i;

	i = 1;
	split = NULL;
	tmp = NULL;
	if (ft_strnstr(red->str, "$", ft_strlen(red->str)) \
		&& red->quote != S_QUOTE)
		split = make_split_red(red, '$', original);
	if (!split || !split[0])
		return ;
	tmp = expand_env(ms, split[0]);
	free(split[0]);
	while (split[i] && split[i][0] != '\0')
	{
		tmp = joinstr(ms, &split[i], &tmp);
		i++;
	}
	free(*original);
	red->str = ft_strdup(tmp);
	free(tmp);
	free(split);
}

static void	ms_strtrim_red(t_redlist *red, char c, char **original)
{
	char	**split;
	char	*tmp;
	char	*old;
	size_t	i;

	i = 1;
	split = make_split_red(red, c, original);
	if (!split || !split[0])
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

static char	**make_split_red(t_redlist *red, char c, char **original)
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
