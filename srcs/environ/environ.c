/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 22:40:44 by naharagu          #+#    #+#             */
/*   Updated: 2023/03/28 19:25:18 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	convert_to_envlist(t_minishell *ms, char *env_str)
{
	char	*equal_ptr;
	char	*key;
	char	*value;

	equal_ptr = ft_strchr(env_str, '=');
	if (!equal_ptr)
		add_envlist(ms, env_str, NULL);
	else
	{
		key = ft_substr(env_str, 0, equal_ptr - env_str);
		if (!key)
			exit_error(ms, "malloc");
		value = ft_strdup(equal_ptr + 1);
		if (!value)
			exit_error(ms, "malloc");
		add_envlist(ms, key, value);
		free(key);
		free(value);
	}
}

void	set_shelvl(t_minishell *ms)
{
	t_envlist	*tmp_env;
	int			shlvl_int;

	tmp_env = get_env_from_key(ms, "SHLVL");
	if (!tmp_env)
		add_envlist(ms, "SHLVL", "1");
	else if (!tmp_env->value)
		add_envlist(ms, "SHLVL", "1");
	else
	{
		shlvl_int = ft_atoi(tmp_env->value);
		if (shlvl_int < 0 || 99 < shlvl_int)
			shlvl_int = 0;
		shlvl_int++;
		free(tmp_env->value);
		tmp_env->value = ft_itoa(shlvl_int);
		if (!tmp_env->value)
			exit_error(ms, "malloc");
	}
}

void	init_env(t_minishell *ms)
{
	extern char	**environ;
	size_t		i;

	i = 0;
	ms->env = (t_envlist *)malloc(sizeof(t_envlist));
	if (!ms->env)
		exit_error (ms, "malloc");
	ms->env->key = NULL;
	ms->env->value = NULL;
	ms->env->next = NULL;
	while (environ[i])
	{
		convert_to_envlist(ms, environ[i]);
		i++;
	}
	set_shelvl(ms);
	return ;
}

bool	is_valid_env_key(char *key)
{
	size_t	i;

	i = 0;
	if (!key)
		return (false);
	if (!(key[i] == '_' || ft_isalpha(key[i])))
		return (false);
	i++;
	while (key[i])
	{
		if (!(key[i] == '_' || ft_isalnum(key[i])))
			return (false);
		i++;
	}
	return (true);
}
