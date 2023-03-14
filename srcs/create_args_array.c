/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_args_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:59:50 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/14 17:20:09 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_argv(t_minishell *ms, char **argv);

size_t	get_args_size(t_minishell *ms)
{
	size_t		size;
	t_cmdlist	*tmp;

	size = 0;
	tmp = ms->exec->cmd;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
}

char	**create_args_array(t_minishell *ms)
{
	char		**args;
	size_t		args_size;
	size_t		i;
	t_cmdlist	*tmp;

	args_size = get_args_size(ms);
	// printf("size is %lu\n", args_size);
	args = ft_calloc(args_size, sizeof(char *));
	if (!args)
		return (NULL);
	i = 0;
	tmp = ms->exec->cmd;
	while (i < args_size)
	{
		args[i] = ft_strdup(ms->exec->cmd->str);
		tmp = tmp->next;
		i++;
	}
	return (args);
}

// void	free_argv(t_minishell *ms, char **argv)
// {
// 	free(argv[0]);
// 	free(argv);
// }
