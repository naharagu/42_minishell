/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:53:39 by shimakaori        #+#    #+#             */
/*   Updated: 2023/01/14 16:55:37 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//static int	check_arg(int argc, char **argv);

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
	if (c == ' ' || c == '|' || c == '<' || c == '>' || c == '\n' || c == '\0')
		return (true);
	else
		return (false);
}

void	check_input(char *input, t_token *token)
{
	t_mslist	*list;
	t_mslist	*tmp;
	size_t		len;
	char		*str;

	list = ms_lstnew(0, NULL);
	while (*input)
	{
		printf("input= %s\n", input);//
		len = 0;
		str = ft_strdup(input);
		printf("str= %s\n", str);//
		while (*input && !(is_quoted(*input, list)) && !(is_delimiter(*input)))
		{
			input++;
			len++;
		}
		printf("input= %c\n", *input);//
		printf("len= %zu\n", len);//
		tmp = ms_lstnew(len, str);
		ms_lstadd_back(&list, tmp);
		printf("list->str= %s\n", list->str);//
		printf("list->next->str= %s\n", list->next->str);//
		input++;
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
		//printf("%s\n", input);//
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
