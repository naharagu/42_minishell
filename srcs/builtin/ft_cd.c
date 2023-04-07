/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:54:26 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/07 13:42:32 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_newdir(t_minishell *ms, size_t argc, char **argv)
{
	char	*newdir;

	if (argc == 1)
	{
		newdir = get_value_from_key(ms, "HOME");
		if (!newdir)
			other_error("cd", "HOME not set", EXIT_FAILURE);
		return (NULL);
	}
	else
		newdir = argv[1];
	if (!newdir)
		other_error("cd", "no such file or directory", EXIT_FAILURE);
	return (newdir);
}

int	ft_cd(t_minishell *ms, size_t argc, char **argv)
{
	char	*cwd;
	char	*newdir;

	newdir = get_newdir(ms, argc, argv);
	if (chdir(newdir) < 0)
	{
		perror(newdir);
		return (EXIT_FAILURE);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("getcwd");
		return (EXIT_FAILURE);
	}
	free(cwd);
	return (EXIT_SUCCESS);
}
