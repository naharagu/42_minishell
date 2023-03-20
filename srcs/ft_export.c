/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 22:40:44 by naharagu          #+#    #+#             */
/*   Updated: 2023/03/20 23:11:15 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool is_valid_key_name(char *key)
{
	bool res;

	res = true;
	//
	return res;
}

void	update_env_value(t_minishell *ms)
{
	return ;
}

int	ft_export(t_minishell *ms, t_execlist *exe)
{
	char **args;
	int status;
	size_t i;

	args = create_args_array(ms);
	status = EXIT_SUCCESS;
	if (!args)
		return (EXIT_FAILURE);
	i = 0;
	while (args[i])
	{
		if (is_valid_key_name(args[i]))
			update_env_value(ms);
		else
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
