/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 22:40:44 by naharagu          #+#    #+#             */
/*   Updated: 2023/03/26 18:51:46 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_valid_key_name(char *key)
{
	bool	res;

	(void)key;
	res = true;
	//
	return (res);
}

void	update_env_value(t_minishell *ms)
{
	(void)ms;
	return ;
}

static int	print_all_env(t_minishell *ms)
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
	return (EXIT_SUCCESS);
}

int	ft_export(t_minishell *ms, size_t argc, char **argv)
{
	size_t	i;

	if (argc == 1)
	{
		print_all_env(ms);
		return (EXIT_SUCCESS);
	}
	i = 0;
	while (argv[i])
	{
		if (is_valid_key_name(argv[i]))
			update_env_value(ms);
		else
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
