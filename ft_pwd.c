/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 22:40:44 by naharagu          #+#    #+#             */
/*   Updated: 2023/02/10 07:42:46 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdbool.h>

int	ft_pwd(int argc, char **argv)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (EXIT_FAILURE);
	else
		ft_putstr_fd(pwd, 1);
	ft_putchar_fd('\n', 1);
	return (EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
	ft_pwd(argc, argv);
	return 0;
}
