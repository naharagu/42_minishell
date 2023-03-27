/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 22:40:44 by naharagu          #+#    #+#             */
/*   Updated: 2023/03/26 21:27:54 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	delete_env(t_minishell *ms, char *arg_str)
{
	t_envlist	*env_curr;
	t_envlist	*env_prev;

	env_curr = ms->env;
	env_prev = env_curr;
	while (env_curr)
	{
		if (ft_strcmp(env_curr->key, arg_str) == 0)
		{
			if (env_curr == env_prev)
				ms->env = env_curr->next;
			else
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

	(void)argc;
	if (!argv)
		return (EXIT_FAILURE);
	i = 1;
	while (argv[i])
	{
		if (is_valid_env_key(argv[i]))
			delete_env(ms, argv[i]);
		else
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
