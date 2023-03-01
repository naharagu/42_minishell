/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:59:13 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/01 13:07:59 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*add_mslist(char *line, t_mslist	**list);

void	lexer(t_minishell *ms)
{
	t_mslist	*tmp;
	char		*start;
	size_t		len;

	while (*ms->line)
	{
		len = 0;
		start = ms->line;
		while (*ms->line && is_quoted(*ms->line, ms))
			ms->line++;
		while (*ms->line && !(is_space(*ms->line)) && \
			!(is_delimiter(*ms->line)))
			ms->line++;
		len = ms->line - start;
		if (len > 0)
		{
			tmp = ms_lstnew(len, start);
			ms_lstadd_back(&ms->list, tmp);
		}
		start = ms->line;
		if (is_delimiter(*ms->line))
		{
			while (*ms->line && (is_delimiter(*ms->line) || is_metachara(*ms->line)))
				ms->line++;
			len = ms->line - start;
			printf("len=  %zu\n", len);//
			tmp = ms_lstnew(len, start);
			printf("tmpstr2= %s\n", tmp->str);//
			ms_lstadd_back(&ms->list, tmp);
		}
		while (*ms->line && is_space(*ms->line))
			ms->line++;
		if (!(ft_strlen(ms->line)))
			break ;
	}
	error_lexer(ms);
}

// static char	*add_mslist(char *line, t_mslist **list)
// {
// 	t_mslist	*tmp;
// 	char		*start;
// 	size_t		len;

// 	len = 0;
// 	start = line;
// 	while (line && (is_delimiter(*line) || is_metachara(*line)))
// 		line++;
// 	len = line - start;
// 	printf("len=  %zu\n", len);//
// 	tmp = ms_lstnew(len, start);
// 	printf("tmpstr2= %s\n", tmp->str);//
// 	ms_lstadd_back(list, tmp);
// 	line++;
// 	return (line);
// }
