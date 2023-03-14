/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_args_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:59:50 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/14 21:13:47 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static size_t	get_args_size(t_execlist *exec)
{
	size_t		size;
	t_cmdlist	*tmp;

	size = 0;
	tmp = exec->cmd;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	return (size - 1);
}

char	**create_args_array(t_execlist *exec)
{
	char		**args;
	size_t		args_size;
	size_t		i;
	t_cmdlist	*tmp;

	args_size = get_args_size(exec);
	printf("args size is %lu\n", args_size);
	if (args_size == 0)
		return NULL;
	args = ft_calloc(args_size + 1, sizeof(char *));
	if (!args)
		return (NULL);
	i = 0;
	tmp = exec->cmd->next;
	while (i < args_size)
	{
		args[i] = ft_strdup(tmp->str);
		tmp = tmp->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

// void	free_args(t_minishell *ms, char **args)
// {
// 	free(args[0]);
// 	free(args);
// }
