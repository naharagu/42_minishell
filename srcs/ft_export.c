/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 22:40:44 by naharagu          #+#    #+#             */
/*   Updated: 2023/03/26 17:42:19 by naharagu         ###   ########.fr       */
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

void	print_all_env(t_minishell *ms)
{
	(void)ms;
	return ;
}

int	ft_export(t_minishell *ms, size_t argc, char **argv)
{
	int		status;
	size_t	i;

	(void)argc;
	status = EXIT_SUCCESS;
	if (!argv)
		print_all_env(ms);
	i = 0;
	while (argv[i])
	{
		if (is_valid_key_name(argv[i]))
			update_env_value(ms);
		else
			return (EXIT_FAILURE);
		i++;
	}
	return (status);
}
