/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 22:40:44 by naharagu          #+#    #+#             */
/*   Updated: 2023/03/28 20:59:48 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_error_nonvalid_env(char *cmd, char *key)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(key, STDERR_FILENO);
	ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
}

static void	delete_env(t_minishell *ms, char *arg_str)
{
	t_envlist	*env_curr;
	t_envlist	*env_prev;

	env_curr = ms->env->next;
	env_prev = ms->env;
	while (env_curr)
	{
		if (!env_curr->key)
			return ;
		if (ft_strcmp(env_curr->key, arg_str) == 0)
		{
			env_prev->next = env_curr->next;
			free(env_curr->key);
			free(env_curr->value);
			free(env_curr);
			return ;
		}
		env_prev = env_curr;
		env_curr = env_curr->next;
	}
	return ;
}

int	ft_unset(t_minishell *ms, size_t argc, char **argv)
{
	size_t	i;
	int		status;

	status = EXIT_SUCCESS;
	if (argc == 1)
		return (status);
	i = 1;
	while (i < argc)
	{
		if (is_valid_env_key(argv[i]))
			delete_env(ms, argv[i]);
		else
		{
			put_error_nonvalid_env("unset", argv[i]);
			status = EXIT_FAILURE;
		}
		i++;
	}
	return (status);
}
