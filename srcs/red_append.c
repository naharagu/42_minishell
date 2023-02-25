/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_append.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:34:34 by shimakaori        #+#    #+#             */
/*   Updated: 2023/02/25 16:56:48 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	std_append(t_minishell *ms, int originfd, int outfd);
void	file_append(t_minishell *ms, int originfd, char *file);
void	both_append(t_minishell *ms, char *file);
void	each_file_append(t_minishell *ms, t_execlist *exec, t_redlist *red);

void	red_append(t_minishell *ms, t_execlist	*exec, t_redlist *red)
{
	int			tmpfd_std;
	int			tmpfd_err;

	tmpfd_std = dup(STD_OUT);
	tmpfd_err = dup(STD_ERR);
	if (exec->std_fd == STD_ERR)
		std_append(ms, STD_OUT, STD_ERR);
	else if (exec->err_fd == STD_OUT)
		std_append(ms, STD_ERR, STD_OUT);
	else if (exec->std_fd == FILE_1 && exec->err_fd == FILE_1)
		both_append(ms, red->next->str);
	else if (exec->std_fd == FILE_1 || exec->err_fd == FILE_2)
		each_file_append(ms, exec, red);
	exec_command(exec);//
	dup2(tmpfd_std, STD_OUT);
	dup2(tmpfd_err, STD_ERR);
	close(tmpfd_std);
	close(tmpfd_err);
}

void	std_append(t_minishell *ms, int originfd, int outfd)
{
	int		dupfd;

	dupfd = 0;
	if (outfd != originfd)
	{
		dupfd = dup2(outfd, originfd);
		if (dupfd == -1)
			print_error(ms, "dup2", EXIT_ERR);
	}
}

void	file_append(t_minishell *ms, int originfd, char *file)
{
	int		filefd;
	int		dupfd;

	dupfd = 0;
	filefd = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (filefd == -1)
		print_error(ms, "open filefd", EXIT_ERR);
	if (filefd != originfd)
	{
		dupfd = dup2(filefd, originfd);
		if (dupfd == -1)
			print_error(ms, "dup2", EXIT_ERR);
	}
	close(filefd);
}

void	both_append(t_minishell *ms, char *file)
{
	int		filefd;
	int		dupfd;
	int		stdfd;

	stdfd = 1;
	filefd = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (filefd == -1)
		print_error(ms, "open filefd", EXIT_ERR);
	while (stdfd < 3)
	{
		dupfd = dup2(filefd, stdfd);
		if (dupfd == -1)
			print_error(ms, "dup2", EXIT_ERR);
		stdfd++;
	}
	close(filefd);
}

void	each_file_append(t_minishell *ms, t_execlist *exec, t_redlist *red)
{
	t_redlist	*startred;

	startred = red;
	{
		while (red->next->str)
		{
			if (!(ft_strncmp(">>", red->str, ft_strlen(">>"))) || \
				!(ft_strncmp("1>>", red->str, ft_strlen("1>>"))))
				file_append(ms, STD_OUT, red->next->str);
			if (!(ft_strncmp("2>>", red->str, ft_strlen("2>>"))))
				file_append(ms, STD_ERR, red->next->str);
			red = red->next;
		}
		red = startred;
	}
}
