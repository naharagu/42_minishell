/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:53:39 by shimakaori        #+#    #+#             */
/*   Updated: 2023/01/12 15:49:59 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//static int	check_arg(int argc, char **argv);

void	check_input(char *input, t_token *token)
{
	size_t	i;

	i = 0;
	token->split = ft_split(input, '|');
	while (token->split[i])
	{
		printf("%s\n", token->split[i]);
		// token->list->str = ft_split(token->split[i], ' ');
		// printf("%s\n", token->list->str[i]);
		i++;
	}
	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '|')
			token->num++;
		i++;
	}
	//printf("%zu\n", token->num);
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
		printf("%s\n", input);
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
