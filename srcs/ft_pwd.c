/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 22:40:44 by naharagu          #+#    #+#             */
/*   Updated: 2023/03/20 13:09:18 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(int argc, char **argv)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (EXIT_FAILURE);
	else
		ft_putstr_fd(pwd, 1);
	ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
