/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:59:50 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/26 14:28:39 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **create_env_array(t_envlist *env)
{
	char **env_array;
	char *env_str;
	char *tmp_str;
	int	size;
	int i;

	size = env_lstsize(env);
	if (size == 0)
		return NULL;
	env_array = ft_calloc(size + 1, sizeof(char *));
	if (!env_array)
		return (NULL);
	i = 0;
	while (env)
	{
		tmp_str = ft_strjoin(env->key, "=");
		if (!tmp_str)
			return NULL;
		env_str = ft_strjoin(tmp_str, env->value);
		free(tmp_str);
		if (!env_str)
			return NULL;
		env_array[i] = env_str;
		// printf("envstr: %s\n", env_str);//
		i++;
		env = env->next;
	}
	return (env_array);
}

size_t	get_args_size(t_execlist *exec)
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
		return (NULL);
	args = ft_calloc(args_size + 1, sizeof(char *));
	if (!args)
		return (NULL);
	i = 0;
	tmp_cmd = exec->cmd;
	while (i < args_size)
	{
		args[i] = ft_strdup(tmp_cmd->str);
		if (!args[i])
			return (NULL);
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
