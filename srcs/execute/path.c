/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:59:50 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/28 18:27:40 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_path(char **path)
{
	size_t	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
}

char	*search_path(t_minishell *ms, char *file)
{
	char	**path;
	char	*value;
	char	*res;
	size_t	i;

	value = getenv("PATH"); //should fix
	path = ft_split(value, ':');
	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], "/");
		path[i] = ft_strjoin(path[i], file);
		if (!(access(path[i], F_OK)))
		{
			res = ft_strdup(path[i]);
			if (!res)
				exit_error(ms, "malloc");
			free_path(path);
			return (res);
		}
		i++;
	}
	free_path(path);
	return (NULL);
}

int	validate_path(char *path, t_execlist *exec)
{
	char *location;

	if (!exec->cmd->str)
		location = "";
	else
		location = exec->cmd->str;
	if (!path)
		exit_error_with_status(location, "command not found", EXIT_CMD_NOT_FOUND);
	if (access(path, F_OK) < 0)
		exit_error_with_status(location, "command not found", EXIT_CMD_NOT_FOUND);
	if (access(path, X_OK) < 0)
		exit_error_with_status(location, "permission denied", EXIT_CMD_NOT_EXECUTABLE);
	return EXIT_SUCCESS;
}
