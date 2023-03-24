/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 11:28:40 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/24 10:16:51 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_valid_fd(int fd)
{
	struct stat	st;

	if (fd < 0)
		return (false);
	errno = 0;
	if (fstat(fd, &st) < 0 && errno == EBADF)
		return (false);
	return (true);
}

static int	stash_fd(int fd_target)
{
	int	fd_stashed;

	if (!is_valid_fd(fd_target))
	{
		errno = EBADF;
		return (-1);
	}
	fd_stashed = 42;
	while (is_valid_fd(fd_stashed))
	{
		printf("%d\n", fd_stashed);
		fd_stashed++;
	}
	fd_stashed = dup2(fd_target, fd_stashed);
	close(fd_target);
	return (fd_stashed);
}

void	set_redirect(t_redlist *red)
{
	red->fd_stashed = stash_fd(red->fd_target);
	dup2(red->fd_file, red->fd_target);
	if (red->next->next)
		set_redirect(red->next->next);
	return ;
}

void	reset_redirect(t_redlist *red)
{
	if (red->next->next)
		reset_redirect(red->next->next);
	close(red->fd_file);
	close(red->fd_target);
	dup2(red->fd_stashed, red->fd_target);
	return ;
}
