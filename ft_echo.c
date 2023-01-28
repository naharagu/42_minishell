/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 22:40:44 by naharagu          #+#    #+#             */
/*   Updated: 2023/01/28 23:15:43 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdbool.h>

static bool is_consective_n(char *s)
{
	size_t	i;

	if (!s[1])
		return (false);
	i = 1;
	while (s[i])
	{
		if (s[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

int	ft_echo(int argc, char **argv)
{
	bool option_n;
	size_t i;

	i = 1;
	option_n = is_consective_n(argv[1]);
	while (i < argc)
	{
		ft_putstr_fd(argv[i], 1);
		if (i != argc - 1)
			write(1, " ", 1);
		i++;
	}
	if (!is_consective_n(argv[1]))
		write(1, "\n", 1);
	return (EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
	if (argc > 1)
	{
		ft_echo(argc, argv);
	}
	return 0;
}
