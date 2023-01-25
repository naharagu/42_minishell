/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:59:13 by shimakaori        #+#    #+#             */
/*   Updated: 2023/01/24 10:34:21 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*add_list(char *input, t_mslist	**list);
bool		is_quoted(char c, t_minishell *ms);
bool		is_delimiter(char c);
bool		is_space(char c);

void	lexer(t_minishell *ms)
{
	t_mslist	*tmp;
	char		*start;
	size_t		len;

	while (*ms->input)
	{
		len = 0;
		start = ms->input;
		while (*ms->input && is_quoted(*ms->input, ms))
			ms->input++;
		while (*ms->input && !(is_space(*ms->input)) \
			&& !(is_delimiter(*ms->input)))
			ms->input++;
		len = ms->input - start;
		if (len > 0)
		{
			tmp = ms_lstnew(len, start);
			ms_lstadd_back(&ms->list, tmp);
		}
		if (is_delimiter(*ms->input))
			ms->input = add_list(ms->input, &ms->list);
		ms->input++;
	}
}

char	*add_list(char *input, t_mslist	**list)
{
	t_mslist	*tmp;
	char		*start;
	size_t		len;

	len = 0;
	start = input;
	while (is_delimiter(*input))
		input++;
	len = input - start;
	tmp = ms_lstnew(len, start);
	ms_lstadd_back(list, tmp);
	input--;
	return (input);
}

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
	//printf("c= %c\n", c);//
	//printf("quote= %d\n", ms->quote);//
	if (ms->quote == S_QUOTE || ms->quote == D_QUOTE || \
		ms->quote == END_S_QUOTE || ms->quote == END_D_QUOTE)
		return (true);
	else
		return (false);
}

bool	is_delimiter(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == ';')
		return (true);
	else
		return (false);
}

bool	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\r'
		|| c == '\n' || c == '\v' || c == '\f')
		return (true);
	else
		return (false);
}
