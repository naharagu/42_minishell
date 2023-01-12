/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:53:39 by shimakaori        #+#    #+#             */
/*   Updated: 2023/01/12 13:19:10 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//static int	check_arg(int argc, char **argv);

void	minishell(t_minishell *ms)
{
	char	*input;

	while (1)
	{
		input = readline("minishell$>");
		add_history(input);
		printf("%s\n", input);
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
