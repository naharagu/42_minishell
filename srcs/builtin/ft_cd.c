/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:54:26 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/04 13:38:53 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_newdir(t_minishell *ms, size_t argc, char **argv)
{
	char	*newdir;

	if (argc == 1)
	{
		newdir = get_value_from_key(ms, "HOME");
		if (!newdir)
			other_error(ms, "cd", "HOME not set", EXIT_FAILURE);
	}
	else
		newdir = argv[1];
	if (!newdir)
		other_error(ms, "cd", "no such file or directory", EXIT_FAILURE);
	return (newdir);
}

int	ft_cd(t_minishell *ms, size_t argc, char **argv)
{
	char	*cwd;
	char	*newdir;

	newdir = get_newdir(ms, argc, argv);
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		exit_error(ms, "getcwd");
		return (EXIT_FAILURE);
	}
	if (chdir(newdir) < 0)
	{
		perror(newdir);
		return (EXIT_FAILURE);
	}
	cwd = getcwd(NULL, 0);
	return (EXIT_SUCCESS);
}
