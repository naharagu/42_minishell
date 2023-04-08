/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 22:40:44 by naharagu          #+#    #+#             */
/*   Updated: 2023/04/07 13:42:47 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_minishell *ms, size_t argc)
{
	t_envlist	*tmp_env;

	if (argc > 1)
	{
		other_error("env", "too many arguments", 1);
		return (EXIT_FAILURE);
	}
	tmp_env = ms->env;
	while (tmp_env)
	{
		if (!tmp_env->key || !tmp_env->value)
			;
		else
			printf("%s=%s\n", tmp_env->key, tmp_env->value);
		tmp_env = tmp_env->next;
	}
	return (EXIT_SUCCESS);
}
