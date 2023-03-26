/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 22:40:44 by naharagu          #+#    #+#             */
/*   Updated: 2023/03/26 17:40:02 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_valid_key_name(char *key)
{
	bool	res;

	(void) key;
	res = true;
	//
	return (res);
}

static void	delete_env_value(t_minishell *ms)
{
	(void) ms;
	return ;
}

int	ft_unset(t_minishell *ms, size_t argc, char **argv)
{
	size_t	i;

	(void) argc;
	if (!argv)
		return (EXIT_FAILURE);
	i = 0;
	while (argv[i])
	{
		if (is_valid_key_name(argv[i]))
			delete_env_value(ms);
		else
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
