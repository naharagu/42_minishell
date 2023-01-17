/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:53:39 by shimakaori        #+#    #+#             */
/*   Updated: 2023/01/17 11:56:33 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_quoted(char c, t_minishell *ms)
{
	if (c == '\'' && ms->quote == S_QUOTE)
		ms->quote = END_S_QUOTE;
	else if (c == '\'' && ms->quote == NO_QUOTE)
		ms->quote = S_QUOTE;
	else if (c == '\"' && ms->quote == D_QUOTE)
		ms->quote = END_D_QUOTE;
	else if (c == '\"' && ms->quote == NO_QUOTE)
		ms->quote = D_QUOTE;
	printf("c= %c\n", c);//
	printf("quote= %d\n", ms->quote);//
	if (ms->quote == S_QUOTE || ms->quote == D_QUOTE || \
		ms->quote == END_S_QUOTE || ms->quote == END_D_QUOTE)
		return (true);
	return (false);
}

bool	is_delimiter(char c, t_minishell *ms)
{
	if (c == ' ' || c == '|' || c == '>' || c == '<')
		return (true);
	else
		return (false);
}

//quote分割未対応
void	split_token(t_minishell *ms)
{
	t_mslist	*list;
	t_mslist	*tmp;
	size_t		len;
	char		*str;

	list = NULL;
	while (*ms->input)
	{
		len = 0;
		str = ft_strdup(ms->input);
		while (*ms->input && !(is_quoted(*ms->input, ms)) \
			&& !(is_delimiter(*ms->input, ms)))
		{
			// printf("c= %c\n", *ms->input);//
			// printf("quote= %d\n", ms->quote);//
			ms->input++;
			len++;
		}
		while (*ms->input && is_quoted(*ms->input, ms))
		{
			ms->input++;
			len++;
		}
		tmp = ms_lstnew(len, str);
		ms_lstadd_back(&list, tmp);
		printf("str= %s\n", list->str);//
		while (*ms->input == ' ')
			ms->input++;
		list = list->next;
	}
}

void	minishell(t_minishell *ms)
{
	while (1)
	{
		ms->input = readline("minishell$>");
		add_history(ms->input);
		//printf("%s\n", ms->input);//
		split_token(ms);
		//free(ms->input);
	}
	exit(ms->exit_status);
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	*ms;

	ms = init_struct_ms(ms);
	minishell(ms);
	return (0);
}
