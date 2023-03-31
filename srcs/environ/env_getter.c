/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_getter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 18:35:40 by naharagu          #+#    #+#             */
/*   Updated: 2023/03/31 11:28:45 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_str_from_envlist(t_minishell *ms, t_envlist *env)
{
	char	*res_str;
	char	*tmp_str;

	tmp_str = ft_strjoin(env->key, "=");
	if (!tmp_str)
		exit_error(ms, "malloc");
	if (env->value)
	{
		res_str = ft_strjoin(tmp_str, env->value);
		free(tmp_str);
		if (!res_str)
			exit_error(ms, "malloc");
	}
	else
		res_str = tmp_str;
	return (res_str);
}

t_envlist	*get_env_from_key(t_minishell *ms, char *key)
{
	t_envlist	*tmp_env;

	tmp_env = ms->env;
	while (tmp_env)
	{
		if (tmp_env->key)
		{
			if (ft_strcmp(tmp_env->key, key) == 0)
				return (tmp_env);
		}
		tmp_env = tmp_env->next;
	}
	return (NULL);
}

char	*get_value_from_key(t_minishell *ms, char *key)
{
	t_envlist	*tmp_env;

	tmp_env = get_env_from_key(ms, key);
	if (tmp_env == NULL)
		return (NULL);
	else
		return (tmp_env->value);
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
