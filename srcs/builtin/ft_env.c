/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 22:40:44 by naharagu          #+#    #+#             */
/*   Updated: 2023/04/18 21:38:05 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(char *key, char *value, bool is_export)
{
	if (is_export)
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(key, STDOUT_FILENO);
	ft_putstr_fd("=", STDOUT_FILENO);
	ft_putstr_fd(value, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
}

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
			print_env(tmp_env->key, tmp_env->value, false);
		tmp_env = tmp_env->next;
	}
	return (EXIT_SUCCESS);
}
