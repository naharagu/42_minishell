/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 22:40:44 by naharagu          #+#    #+#             */
/*   Updated: 2023/03/28 12:04:21 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_all_n(char *s)
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

static bool	skip_n_option(char **argv, size_t *i)
{
	bool	n_option;

	n_option = false;
	while (argv[*i] && (*argv[*i] == '-'))
	{
		if (!is_all_n(argv[*i]))
			break ;
		n_option = true;
		(*i)++;
	}
	return (n_option);
}

int	ft_echo(size_t argc, char **argv)
{
	size_t	i;
	bool	n_option;

	i = 1;
	n_option = skip_n_option(argv, &i);
	while (i < argc)
	{
		ft_putstr_fd(argv[i], 1);
		if (i != argc - 1)
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (!n_option)
		write(STDOUT_FILENO, "\n", 1);
	return (EXIT_SUCCESS);
}
