/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 18:35:40 by naharagu          #+#    #+#             */
/*   Updated: 2023/03/28 19:08:25 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
