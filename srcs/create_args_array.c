/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_args_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:59:50 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/20 12:42:25 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static size_t	get_args_size(t_execlist *exec)
{
	size_t		size;
	t_cmdlist	*tmp_cmd;

	size = 1;
	tmp_cmd = exec->cmd;
	while (tmp_cmd->next)
	{
		size++;
		// printf("now: %s\n", tmp->str);//
		tmp_cmd = tmp_cmd->next;
	}
	return (size);
}

char	**create_args_array(t_execlist *exec)
{
	char		**args;
	size_t		args_size;
	size_t		i;
	t_cmdlist	*tmp_cmd;

	args_size = get_args_size(exec);
	// printf("args size is %lu\n", args_size);//
	if (args_size == 0)
		return NULL;
	args = ft_calloc(args_size + 1, sizeof(char *));
	if (!args)
		return (NULL);
	i = 0;
	tmp_cmd = exec->cmd;
	while (i < args_size)
	{
		args[i] = ft_strdup(tmp_cmd->str);
		// printf("arg %zu is: %s\n", i, args[i]);//
		tmp_cmd = tmp_cmd->next;
		i++;
	}
	args[args_size] = NULL;
	return (args);
}

// void	free_args(t_minishell *ms, char **args)
// {
// 	free(args[0]);
// 	free(args);
// }
