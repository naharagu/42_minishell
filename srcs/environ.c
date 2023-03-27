/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 22:40:44 by naharagu          #+#    #+#             */
/*   Updated: 2023/03/26 21:34:54 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	convert_to_envlist(t_minishell *ms, char *str_envrion)
{
	char	*after_key;
	char	*key;
	char	*value;

	after_key = ft_strchr(str_envrion, '=');
	if (!after_key)
		add_envlist(ms, str_envrion, NULL);
	else
	{
		key = ft_substr(str_envrion, 0, after_key - str_envrion);
		if (!key)
			exit_error(ms, "malloc");
		value = ft_strdup(after_key + 1);
		if (!value)
			exit_error(ms, "malloc");
		add_envlist(ms, key, value);
	}
}

void	set_shelvl(t_minishell *ms)
{
	char	*shlvl_str;
	int		shlvl_int;

	shlvl_str = getenv("SHLVL");
	if (!shlvl_str)
		ms->env = env_lstnew(ms, "SHLVL", ft_strdup("1"));
	else
	{
		shlvl_int = ft_atoi(shlvl_str);
		shlvl_int++;
		if (shlvl_int > 100)
			shlvl_int = 1;
		ms->env = env_lstnew(ms, "SHLVL", ft_itoa(shlvl_int));
	}
}

void	init_env(t_minishell *ms)
{
	extern char	**environ;
	size_t		i;

	i = 0;
	set_shelvl(ms);
	while (environ[i])
	{
		convert_to_envlist(ms, environ[i]);
		i++;
	}
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
