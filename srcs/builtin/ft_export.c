/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 22:40:44 by naharagu          #+#    #+#             */
/*   Updated: 2023/03/28 22:47:08 by naharagu         ###   ########.fr       */
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

static void	split_at_equal(t_minishell *ms, char *arg, char **key, char **value)
{
	char	*equal_ptr;

	equal_ptr = ft_strchr(arg, '=');
	if (!equal_ptr)
	{
		*key = ft_strdup(arg);
		if (!*key)
			exit_error(ms, "malloc");
		*value = NULL;
	}
	else
	{
		*key = ft_substr(arg, 0, equal_ptr - arg);
		if (!*key)
			exit_error(ms, "malloc");
		*value = ft_strdup(equal_ptr + 1);
		if (!*value)
		{
			free(*key);
			exit_error(ms, "malloc");
		}
	}
}

static void	update_env(t_minishell *ms, t_envlist *env, char *key, char *value)
{
	if (env == NULL)
		add_envlist(ms, key, value);
	else
	{
		free(key);
		if (env->value)
			free(env->value);
		env->value = value;
	}
}

static int	export_arg(t_minishell *ms, char *arg)
{
	char		*key;
	char		*value;

	split_at_equal(ms, arg, &key, &value);
	if (!is_valid_env_key((key)))
	{
		free(key);
		if (value)
			free(value);
		return (EXIT_FAILURE);
	}
	update_env(ms, get_env_from_key(ms, key), key, value);
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
		if (export_arg(ms, argv[i]) == EXIT_FAILURE)
		{
			put_error_nonvalid_env("export", argv[i]);
			status = EXIT_FAILURE;
		}
		i++;
	}
	return (status);
}
