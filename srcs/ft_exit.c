/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:09:56 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/20 11:53:39 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	normal_exit(t_minishell *ms, int status);
void	numeric_error(t_minishell *ms, char *location, char *msg, int status);

void	ft_exit(t_minishell *ms, int argc, char **argv)
{
	char	*arg;

	if (argc == 1)
		normal_exit(ms, EXIT_SUCCESS);
	else if (argc > 1)
	{
		arg = argv[1];
		while (*arg)
		{
			if (!(ft_isdigit(*arg)))
				numeric_error(ms, argv[1], "numeric argument required", 255);
			arg++;
		}
		if (argc == 2 && (ft_atoi(argv[1]) || ft_atoi(argv[1]) == 0))
			normal_exit(ms, ft_atoi(argv[1]));
		if (!(ft_atoi(argv[1])) && ft_atoi(argv[1]) != 0)
			numeric_error(ms, argv[1], "numeric argument required", 255);
		if (argc > 2)
			other_error(ms, "exit", "too many arguments", 1);
	}
	else
		return ;
}

void	normal_exit(t_minishell *ms, int status)
{
	ms->exit_status = status;
	ft_putendl_fd("exit", STD_ERR);
	exit(ms->exit_status);
}

void	numeric_error(t_minishell *ms, char *location, char *msg, int status)
{
	ms->exit_status = status;
	ft_putendl_fd("exit", STD_ERR);
	ft_putstr_fd("minishell: exit: ", STD_ERR);
	ft_putstr_fd(location, STD_ERR);
	ft_putstr_fd(": ", STD_ERR);
	ft_putendl_fd(msg, STD_ERR);
	exit(ms->exit_status);
}
