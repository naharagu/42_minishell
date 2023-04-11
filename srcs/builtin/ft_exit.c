/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:09:56 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/11 20:54:22 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_status;

static void	normal_exit(int status)
{
	g_status = status;
	ft_putendl_fd("exit", STDERR_FILENO);
	exit(g_status);
}

static void	numeric_error(char *location, char *msg, int status)
{
	g_status = status;
	ft_putendl_fd("exit", STDERR_FILENO);
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(location, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(g_status);
}

static bool	is_numeric_argument(char *arg)
{
	if (*arg == '\0')
		return (false);
	errno = 0;
	ft_atol(arg);
	if (errno == ERANGE)
		return (false);
	if (*arg == '-' || *arg == '+')
		arg++;
	while (*arg)
	{
		if (!(ft_isdigit(*arg)))
			return (false);
		arg++;
	}
	return (true);
}

int	ft_exit(int argc, char **argv)
{
	if (argc == 1)
		normal_exit(g_status);
	g_status = ft_atoi(argv[1]);
	if (!is_numeric_argument(argv[1]))
		numeric_error(argv[1], "numeric argument required", 255);
	if (argc > 2)
	{
		other_error("exit", "too many arguments", 255);
		return (EXIT_FAILURE);
	}
	normal_exit(g_status);
	exit(255);
}
