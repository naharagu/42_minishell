/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:53:39 by shimakaori        #+#    #+#             */
/*   Updated: 2023/01/14 22:36:53 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_quoted(char c, t_mslist *list)
{
	//printf("c= %c\n", c);//
	//printf("quote= %d\n", list->quote);//
	// if (list->quote == S_QUOTE && c == '\'')
	// {
	// 	list->quote = END_S_QUOTE;
	// 	return (true);
	// }
	// else if (c == '\'')
	// {
	// 	list->quote = S_QUOTE;
	// 	return (true);
	// }
	// else if (list->quote == D_QUOTE && c == '\"')
	// {
	// 	list->quote = END_D_QUOTE;
	// 	return (true);
	// }
	// else if (c == '\"')
	// {
	// 	list->quote = D_QUOTE;
	// 	return (true);
	// }
	return (false);
}

bool	is_delimiter(char c)
{
	if (c == ' ')
		return (true);
	else
		return (false);
}

void	split_input(char *input)
{
	t_mslist	*list;
	t_mslist	*tmp;
	size_t		len;
	char		*str;

	list = NULL;
	while (*input)
	{
		len = 0;
		str = ft_strdup(input);
		while (*input && !(is_quoted(*input, list)) && !(is_delimiter(*input)))
		{
			input++;
			len++;
		}
		tmp = ms_lstnew(len, str);
		ms_lstadd_back(&list, tmp);
		printf("list->str= %s\n", list->str);//
		while ((is_quoted(*input, list)) || (is_delimiter(*input)))
			input++;
		list = list->next;
	}
}

void	minishell(t_minishell *ms)
{
	char	*input;

	while (1)
	{
		input = readline("minishell$>");
		add_history(input);
		//printf("%s\n", input);//
		split_input(input);
		free(input);
	}
	exit(ms->exit_status);
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	*ms;

	init_struct_ms(ms);
	minishell(ms);
	return (0);
}
