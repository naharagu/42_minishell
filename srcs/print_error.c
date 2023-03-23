/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 10:17:33 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/23 22:03:00 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error(t_minishell *ms, char *location)
{
	(void)ms;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	perror(location);
	exit(EXIT_FAILURE);
}

void	syntax_error(t_minishell *ms, char *location, int status)
{
	ms->exit_status = status;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("syntax error near ", STDERR_FILENO);
	if (!(ft_strncmp("|", location, ft_strlen(location))) || \
		!(ft_strncmp("newline", location, ft_strlen(location))) || \
		(ft_strnstr(location, ">", 1)) || (ft_strnstr(location, "<", 1)))
	{
		ft_putstr_fd("unexpected token `", STDERR_FILENO);
		ft_putstr_fd(location, STDERR_FILENO);
		ft_putendl_fd("\'", STDERR_FILENO);
	}
	else
		ft_putendl_fd(location, STDERR_FILENO);
	clear_ms(ms);
	minishell(ms);
}

void	other_error(t_minishell *ms, char *location, char *msg, int status)
{
	ms->exit_status = status;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(location, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	clear_ms(ms);
	minishell(ms);
}
