/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 11:28:40 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/24 10:15:44 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assign_redtype(t_redlist *red)
{
	if (red->str == NULL)
		exit(258); //
	if (ft_strnstr(red->str, ">>", ft_strlen(red->str)))
	{
		red->type = APPEND;
		red->fd_target = STDOUT_FILENO;
	}
	else if (ft_strnstr(red->str, ">", ft_strlen(red->str)))
	{
		red->type = OUTPUT;
		red->fd_target = STDOUT_FILENO;
	}
	else if (ft_strnstr(red->str, "<<", ft_strlen(red->str)))
	{
		red->type = HERE_DOC;
		red->fd_target = STDIN_FILENO;
	}
	else if (ft_strnstr(red->str, "<", ft_strlen(red->str)))
	{
		red->type = INPUT;
		red->fd_target = STDIN_FILENO;
	}
	else
		exit(258); //
}

void	validate_red(t_redlist *red)
{
	t_redlist	*tmp_red;

	tmp_red = red;
	while (tmp_red && tmp_red->str)
	{
		if (tmp_red->next == NULL)
			exit(258); //
		assign_redtype(tmp_red);
		tmp_red = tmp_red->next;
		if (tmp_red->str == NULL)
			exit(258); //
		tmp_red = tmp_red->next;
	}
	return ;
}

int	check_redirect(t_minishell *ms)
{
	t_execlist	*tmp_exec;

	tmp_exec = ms->exec;
	while (tmp_exec)
	{
		if (ms->exec->redtype != NO_REDIRECT)
			validate_red(tmp_exec->red);
		tmp_exec = tmp_exec->next;
	}
	return (0);
}

int	open_redirect_file(t_redlist *red)
{
	char	*file;

	file = red->next->str;
	// printf("file name is %s\n", file);//
	if (red->type == OUTPUT)
		return (open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644));
	else if (red->type == INPUT)
		return (open(file, O_RDONLY));
	else if (red->type == APPEND)
		return (open(file, O_CREAT | O_WRONLY | O_APPEND, 0644));
	// else if (red->type == HERE_DOC)
	return (0);
}

int	open_and_assign_fd(t_minishell *ms)
{
	t_execlist	*tmp_exec;
	t_redlist	*tmp_red;

	tmp_exec = ms->exec;
	while (tmp_exec)
	{
		tmp_red = tmp_exec->red;
		while (tmp_red)
		{
			tmp_red->fd_file = open_redirect_file(tmp_red);
			// printf("file fd is %d\n", tmp_red->fd_file);//
			if (tmp_red->fd_file < 0)
				return (-1);
			tmp_red = tmp_red->next->next;
		}
		tmp_exec = tmp_exec->next;
	}
	return (0);
}

void	prepare_redirect(t_minishell *ms)
{
	if (check_redirect(ms) == -1)
		return ; //exit status
	if (open_and_assign_fd(ms) == -1)
		return ; //exit status
}

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
