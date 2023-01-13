/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:53:39 by shimakaori        #+#    #+#             */
/*   Updated: 2023/01/13 14:15:28 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//static int	check_arg(int argc, char **argv);

bool	is_quoted(char c, t_mslist *list)
{
	printf("%c\n", c);//
	printf("%d\n", list->quote);//
	if (list->quote == S_QUOTE && c == '\'')
	{
		list->quote = END_S_QUOTE;
		return (true);
	}
	else if (c == '\'')
	{
		list->quote = S_QUOTE;
		return (true);
	}
	else if (list->quote == D_QUOTE && c == '\"')
	{
		list->quote = END_D_QUOTE;
		return (true);
	}
	else if (c == '\"')
	{
		list->quote = D_QUOTE;
		return (true);
	}
	return (false);
}

bool	is_delimiter(char c)
{
	if (c == ' ' || c == '|' || c == '<' || c == '>')
		return (true);
	else
		return (false);
}

void	check_input(char *input, t_token *token)
{
	t_mslist	*list;
	size_t		i;
	size_t		j;

	list = init_mslist(list);
	i = 0;
	j = 0;
	while (input[i] != '\0')
	{
		while (!(is_quoted(input[i], list)) && !(is_delimiter(input[i])))
			i++;
		printf("%zu\n", i);//
		list->str = ft_calloc(sizeof(char), (i + 1));
		if (!(list->str))
			return ;
		while (j < i)
		{
			list->str[j] = input[j];
			j++;
		}
		printf("%s\n", list->str);//
		list->prev = list;
		list = list->next;
	}
}

void	minishell(t_minishell *ms)
{
	char	*input;
	t_token	*token;

	token = init_token(token);
	// printf("%zu\n", token->num);
	// printf("%p\n", &token->num);
	while (1)
	{
		input = readline("minishell$>");
		add_history(input);
		//printf("%s\n", input);
		check_input(input, token);
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

// static int	check_arg(int argc, char **argv)
// {
// 	size_t	i;
// 	size_t	j;

// 	if (argc < 5 || argc > 6)
// 	{
// 		printf("Invalid Argument\n");
// 		return (1);
// 	}
// 	i = 1;
// 	while (i < argc)
// 	{
// 		j = 0;
// 		while (argv[i][j] != '\0')
// 		{
// 			if (ft_isdigit(argv[i][j]) == 0)
// 			{
// 				printf("Error: Invalid Argument\n");
// 				return (1);
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (0);
// }
