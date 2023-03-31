/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:59:50 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/31 11:18:50 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**create_env_array(t_minishell *ms, t_envlist *env)
{
	char	**env_array;
	int		i;

	env_array = ft_calloc(env_lstsize(env) + 1, sizeof(char *));
	if (!env_array)
		exit_error(ms, "env");
	i = 0;
	while (env)
	{
		if (!env->key)
		{
			env = env->next;
			continue ;
		}
		env_array[i] = create_str_from_envlist(ms, env);
		env = env->next;
		i++;
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
		tmp_cmd = tmp_cmd->next;
	}
	return (size);
}

void	allocate_args_memory(char ***args, size_t args_size, t_minishell *ms)
{
	*args = ft_calloc(args_size + 1, sizeof(char *));
	if (!args)
		exit_error(ms, "malloc");
}

char	**create_args_array(t_minishell *ms, t_execlist *exec)
{
	char		**args;
	size_t		args_size;
	size_t		i;
	t_cmdlist	*tmp_cmd;

	args_size = get_args_size(exec);
	allocate_args_memory(&args, args_size, ms);
	i = 0;
	tmp_cmd = exec->cmd;
	while (args_size && i < args_size)
	{
		if (!tmp_cmd->str)
			break ;
		args[i] = ft_strdup(tmp_cmd->str);
		if (!args[i])
		{
			free_arg_array(i, args);
			exit_error(ms, "malloc");
		}
		tmp_cmd = tmp_cmd->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

void	free_arg_array(size_t argc, char **argv)
{
	size_t	i;

	i = 0;
	while (i < argc)
	{
		free(argv[i]);
		i++;
	}
	free(argv);
	return ;
}
