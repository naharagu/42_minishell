/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:09:56 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/29 18:56:57 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t g_status;
void	normal_exit(int status);
void	numeric_error(char *location, char *msg, int status);

void	ft_exit(t_minishell *ms, int argc, char **argv)
{
	char	*arg;

	if (argc == 1)
		normal_exit(EXIT_SUCCESS);
	else if (argc > 1)
	{
		arg = argv[1];
		while (*arg)
		{
			if (!(ft_isdigit(*arg)))
				numeric_error(argv[1], "numeric argument required", 255);
			arg++;
		}
		if (argc == 2 && (ft_atoi(argv[1]) || ft_atoi(argv[1]) == 0))
			normal_exit(ft_atoi(argv[1]));
		if (!(ft_atoi(argv[1])) && ft_atoi(argv[1]) != 0)
			numeric_error(argv[1], "numeric argument required", 255);
		if (argc > 2)
			other_error(ms, "exit", "too many arguments", 1);
	}
	else
		return ;
}

void	normal_exit(int status)
{
	g_status = status;
	ft_putendl_fd("exit", STDERR_FILENO);
	exit(g_status);
}

void	numeric_error(char *location, char *msg, int status)
{
	g_status = status;
	ft_putendl_fd("exit", STDERR_FILENO);
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(location, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(g_status);
}
