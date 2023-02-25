/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_out.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:10:30 by shimakaori        #+#    #+#             */
/*   Updated: 2023/02/25 14:45:08 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	std_outred(t_minishell *ms, int originfd, int outfd);
void	file_outred(t_minishell *ms, int originfd, char *file);
void	both_outred(t_minishell *ms, char *file);
void	each_file_outred(t_minishell *ms, t_execlist *exec, t_redlist *red);

void	red_out(t_minishell *ms, t_execlist	*exec, t_redlist *red)
{
	int		tmpfd_std;
	int		tmpfd_err;

	tmpfd_std = dup(STD_OUT);
	tmpfd_err = dup(STD_ERR);
	if (exec->std_fd == STD_ERR)
		std_outred(ms, STD_OUT, STD_ERR);
	else if (exec->err_fd == STD_OUT)
		std_outred(ms, STD_ERR, STD_OUT);
	else if (exec->std_fd == DELETE && exec->err_fd == DELETE)
		both_outred(ms, "/dev/null");
	else if (exec->std_fd == DELETE)
		file_outred(ms, STD_OUT, "/dev/null");
	else if (exec->err_fd == DELETE)
		file_outred(ms, STD_ERR, "/dev/null");
	else if (exec->std_fd == FILE_1 && exec->err_fd == FILE_1)
		both_outred(ms, red->next->str);
	else if (exec->std_fd == FILE_1 || exec->err_fd == FILE_2)
		each_file_outred(ms, exec, red);
	exec_command(exec);//
	dup2(tmpfd_std, STD_OUT);
	dup2(tmpfd_err, STD_ERR);
	close(tmpfd_std);
	close(tmpfd_err);
}

void	std_outred(t_minishell *ms, int originfd, int outfd)
{
	int		dupfd;

	if (outfd != originfd)
	{
		dupfd = dup2(outfd, originfd);
		if (dupfd == -1)
			exit(EXIT_FAILURE);
	}
}

void	file_outred(t_minishell *ms, int originfd, char *file)
{
	int		filefd;
	int		dupfd;

	filefd = open(file, O_CREAT | O_WRONLY, 0644);
	if (filefd == -1)
		exit(EXIT_FAILURE);
	if (filefd != originfd)
	{
		dupfd = dup2(filefd, originfd);
		if (dupfd == -1)
			exit(EXIT_FAILURE);
	}
	close(filefd);
}

void	both_outred(t_minishell *ms, char *file)
{
	int		filefd;
	int		dupfd;
	int		stdfd;

	stdfd = 1;
	filefd = open(file, O_CREAT | O_WRONLY, 0644);
	if (filefd == -1)
		exit(EXIT_FAILURE);
	while (stdfd < 3)
	{
		dupfd = dup2(filefd, stdfd);
		if (dupfd == -1)
			exit(EXIT_FAILURE);
		stdfd++;
	}
	close(filefd);
}

void	each_file_outred(t_minishell *ms, t_execlist *exec, t_redlist *red)
{
	t_redlist	*startred;

	startred = red;
	{
		while (red->next->str)
		{
			if (!(ft_strncmp(">", red->str, 1)) || \
				!(ft_strncmp("1>", red->str, 2)))
				file_outred(ms, STD_OUT, red->next->str);
			if (!(ft_strncmp("2>", red->str, 2)))
				file_outred(ms, STD_ERR, red->next->str);
			red = red->next;
		}
		red = startred;
	}
}
