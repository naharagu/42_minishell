/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 22:40:44 by naharagu          #+#    #+#             */
/*   Updated: 2023/03/23 22:53:30 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_valid_key_name(char *key)
{
	bool	res;

	res = true;
	//
	return (res);
}

static void	delete_env_value(t_minishell *ms)
{
	return ;
}

int	ft_unset(t_minishell *ms, t_execlist *exe)
{
	char	**args;
	int		status;
	size_t	i;

	args = create_args_array(ms);
	status = EXIT_SUCCESS;
	if (!args)
		return (EXIT_FAILURE);
	i = 0;
	while (args[i])
	{
		if (is_valid_key_name(args[i]))
			delete_env_value(ms);
		else
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
