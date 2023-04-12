/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:59:50 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/12 09:05:12 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_path(char **path)
{
	size_t	i;

	i = 0;
	if (!path)
		return ;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
}

static char	*search_path(t_minishell *ms, char *file)
{
	char	**path;
	char	*tmp;
	char	*res;
	size_t	i;

	path = ft_split(get_value_from_key(ms, "PATH"), ':');
	i = 0;
	while (path && path[i])
	{
		tmp = ft_strjoin(path[i++], "/");
		if (!tmp)
			exit_error("malloc");
		res = ft_strjoin(tmp, file);
		free(tmp);
		if (!res)
			exit_error("malloc");
		if (access(res, X_OK) == 0)
		{
			free_path(path);
			return (res);
		}
		free(res);
	}
	free_path(path);
	return (NULL);
}

static int	validate_path(char *path, t_execlist *exec)
{
	char	*location;

	if (!exec->cmd->str)
		location = "";
	else
		location = exec->cmd->str;
	if (!path)
		exit_error_with_status(location, "No such file or directory", \
				NOT_FOUND);
	if (access(path, F_OK) < 0)
		exit_error_with_status(location, "command not found", NOT_FOUND);
	if (access(path, X_OK) < 0)
		exit_error_with_status(location, "permission denied", NOT_EXECUTABLE);
	return (EXIT_SUCCESS);
}

char	*get_and_validate_path(char *path, t_minishell *ms, t_execlist *exec)
{
	if (!(ft_strchr(path, '/')))
		path = search_path(ms, path);
	else
	{
		if (access(path, F_OK) < 0)
			exit_error_with_status(path, "No such file or directory", \
					NOT_FOUND);
	}
	validate_path(path, exec);
	return (path);
}
