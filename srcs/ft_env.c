/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 22:40:44 by naharagu          #+#    #+#             */
/*   Updated: 2023/03/26 10:06:54 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(size_t argc, char **argv, char **env)
{
	int	i;

	(void)argc;
	(void)argv;
	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}

// int	main(int argc, char **argv, char **env)
// {
// 	ft_env(argc, argv, env);
// 	return (EXIT_SUCCESS);
// }

//echo -n -n -nnn hello
// > hello