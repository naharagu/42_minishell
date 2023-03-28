/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 22:40:44 by naharagu          #+#    #+#             */
/*   Updated: 2023/03/28 19:15:22 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_all_env(t_minishell *ms)
{
	t_envlist	*tmp_env;

	tmp_env = ms->env;
	while (tmp_env)
	{
		if (!tmp_env->key || !tmp_env->value)
			;
		else
			printf("declare -x %s=\"%s\"\n", tmp_env->key, tmp_env->value);
		tmp_env = tmp_env->next;
	}
	return ;
}

void	put_error_nonvalid_env(char *cmd, char *key)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(key, STDERR_FILENO);
	ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
}

int	update_env_value(t_minishell *ms, char *arg)
{
	char		*equal_ptr;
	char		*key;
	char		*value;
	t_envlist	*tmp_env;

	equal_ptr = ft_strchr(arg, '=');
	if (!equal_ptr)
	{
		key = ft_strdup(arg);
		if (!key)
			exit_error(ms, "malloc");
		value = NULL;
	}
	else
	{
		key = ft_substr(arg, 0, equal_ptr - arg);
		if (!key)
			exit_error(ms, "malloc");
		// printf("key: %s\n", key);
		if (!is_valid_env_key(key))
		{
			free(key);
			return (EXIT_FAILURE);
		}
		value = ft_strdup(equal_ptr + 1);
		if (!value)
		{
			free(key);
			exit_error(ms, "malloc");
		}
	}
	tmp_env = get_env_from_key(ms, key);
	if (tmp_env == NULL)
	{
		add_envlist(ms, key, value);
		free(key);
	}
	else
	{
		if (tmp_env->value)
			free(tmp_env->value);
		tmp_env->value = value;
	}
	return (EXIT_SUCCESS);
}

int	ft_export(t_minishell *ms, size_t argc, char **argv)
{
	size_t	i;
	int		status;

	status = EXIT_SUCCESS;
	if (argc == 1)
	{
		print_all_env(ms);
		return (status);
	}
	i = 1;
	while (argv[i])
	{
		if (update_env_value(ms, argv[i]) == EXIT_FAILURE)
		{
			put_error_nonvalid_env("export", argv[i]);
			status = EXIT_FAILURE;
		}
		i++;
	}
	return (status);
}
