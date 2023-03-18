/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:09:56 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/18 23:39:37 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	numeric_error(t_minishell *ms, char *location, char *msg, int status);

void	ft_exit(t_minishell *ms, int argc, char **argv)
{
	char	*arg;

	if (argc > 2)
		other_error(ms, "exit", "too many arguments", 1);
	else if (argc == 2)
	{
		arg = argv[1];
		while (*arg)
		{
			if (!(ft_isdigit(*arg)))
			{
				ft_putendl_fd("exit", STDOUT_FILENO);
				numeric_error(ms, argv[1], "numeric argument required", 255);
			}
			arg++;
		}
	}
	else if (argc == 1)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	else
		return ;
}

void	numeric_error(t_minishell *ms, char *location, char *msg, int status)
{
	ms->exit_status = status;
	ft_putstr_fd("minishell: exit: ", STD_ERR);
	ft_putstr_fd(location, STD_ERR);
	ft_putstr_fd(": ", STD_ERR);
	ft_putendl_fd(msg, STD_ERR);
	exit(ms->exit_status);
}
