/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:59:13 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/10 22:08:14 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		add_mslist(t_minishell *ms, char *start, char *line);
static int		count_metachara(t_minishell *ms, char *start, char *tmp);

int	lexer(t_minishell *ms)
{
	char	*tmp;
	char	*start;

	tmp = ms->line;
	while (*tmp)
	{
		start = tmp;
		while (*tmp && !(is_space(*tmp)) && !(is_metachara(*tmp)) \
			&& *tmp != '\'' && *tmp != '\"' && *tmp != '=')
			tmp++;
		if (*tmp == '=')
			tmp++;
		while (*tmp && is_quoted(*tmp, ms))
			tmp++;
		while (*tmp && !(is_space(*tmp)) && !(is_metachara(*tmp)) \
			&& *tmp != '\'' && *tmp != '\"')
			tmp++;
		add_mslist(ms, start, tmp);
		start = tmp;
		tmp += count_metachara(ms, start, tmp);
		while (*tmp && is_space(*tmp))
			tmp++;
	}
	return (error_lexer(ms));
}

static void	add_mslist(t_minishell *ms, char *start, char *line)
{
	t_mslist	*tmp;
	size_t		len;

	len = line - start;
	if (len > 0)
	{
		tmp = ms_lstnew(len, start);
		ms_lstadd_back(&ms->list, tmp);
	}
}

static int	count_metachara(t_minishell *ms, char *start, char *tmp)
{
	char	chara;
	int		count;

	count = 0;
	if (*tmp && is_metachara(*tmp))
	{
		chara = *tmp;
		tmp++;
		count++;
		if (*tmp == chara)
		{
			tmp++;
			count++;
		}
		add_mslist(ms, start, tmp);
		return (count);
	}
	else
		return (0);
}
