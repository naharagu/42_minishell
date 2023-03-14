/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_args_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:59:50 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/14 16:21:18 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_argv(t_minishell *ms, char **argv);

size_t	get_args_size(t_minishell *ms)
{
	size_t		size;
	t_execlist	*tmp;

	size = 0;
	tmp = ms->exec;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
}

char	**create_args_array(t_minishell *ms)
{
	char	**argv;
	size_t	args_size;

	args_size = get_args_size(ms);
	// printf("size is %lu\n", args_size);
	argv = ft_calloc(args_size, sizeof(char *));
	if (!argv)
		return NULL;
	return (argv);
}

// void	free_argv(t_minishell *ms, char **argv)
// {
// 	free(argv[0]);
// 	free(argv);
// }
