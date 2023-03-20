/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 10:17:33 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/20 15:47:40 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error(t_minishell *ms, char *location)
{
	(void)ms;
	ft_putstr_fd("minishell: ", STD_ERR);
	perror(location);
	exit(EXIT_FAILURE);
}

void	syntax_error(t_minishell *ms, char *location, int status)
{
	ms->exit_status = status;
	ft_putstr_fd("minishell: ", STD_ERR);
	ft_putstr_fd("syntax error near ", STD_ERR);
	if (!(ft_strncmp("|", location, ft_strlen(location))) || \
		!(ft_strncmp("newline", location, ft_strlen(location))) || \
		(ft_strnstr(location, ">", 1)) || (ft_strnstr(location, "<", 1)))
	{
		ft_putstr_fd("unexpected token `", STD_ERR);
		ft_putstr_fd(location, STD_ERR);
		ft_putendl_fd("\'", STD_ERR);
	}
	else
		ft_putendl_fd(location, STD_ERR);
	clear_ms(ms);
	minishell(ms);
}

void	other_error(t_minishell *ms, char *location, char *msg, int status)
{
	ms->exit_status = status;
	ft_putstr_fd("minishell: ", STD_ERR);
	ft_putstr_fd(location, STD_ERR);
	ft_putstr_fd(": ", STD_ERR);
	ft_putendl_fd(msg, STD_ERR);
	clear_ms(ms);
	minishell(ms);
}
