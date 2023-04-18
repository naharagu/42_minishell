/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 10:17:33 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/18 21:52:36 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error(char *location)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	perror(location);
	exit(EXIT_FAILURE);
}

void	exit_error_with_status(char *location, char *message, int status)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(location, STDERR_FILENO);
	ft_putstr_fd(" : ", STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(status);
}

int	syntax_error(char *location, int status)
{
	g_status = status;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("syntax error near ", STDERR_FILENO);
	if (!(ft_strncmp("redirect", location, ft_strlen(location))) \
	|| !(ft_strncmp("unclosed quotes", location, ft_strlen(location))))
		ft_putendl_fd(location, STDERR_FILENO);
	else
	{
		ft_putstr_fd("unexpected token `", STDERR_FILENO);
		ft_putstr_fd(location, STDERR_FILENO);
		ft_putendl_fd("\'", STDERR_FILENO);
	}
	return (EXIT_FAILURE);
}

int	other_error(char *location, char *msg, int status)
{
	g_status = status;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(location, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	return (g_status);
}
