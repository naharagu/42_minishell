/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_append.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:34:34 by shimakaori        #+#    #+#             */
/*   Updated: 2023/02/24 16:14:20 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	file_append(t_minishell *ms, int originfd, char *file);
void	both_append(t_minishell *ms, char *file);
void	std_append(t_minishell *ms, int originfd, int outfd);

void	red_append(t_minishell *ms, t_execlist	*exec, t_redlist *red)
{
	t_redlist	*startred;

	startred = red;
	if (exec->std_fd == STD_ERR)
		std_append(ms, STD_OUT, STD_ERR);
	else if (exec->err_fd == STD_OUT)
		std_append(ms, STD_ERR, STD_OUT);
	else if (exec->std_fd == FILE_1 && exec->err_fd == FILE_1)
		both_append(ms, red->next->str);
	else if (exec->std_fd == FILE_1 || exec->err_fd == FILE_2)
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
	}
	red = startred;
}

void	file_append(t_minishell *ms, int originfd, char *file)
{
	int		filefd;
	int		tmpfd;
	int		dupfd;

	tmpfd = 0;
	dupfd = 0;
	filefd = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (filefd == -1)
		exit(EXIT_FAILURE);
	tmpfd = dup(originfd);
	if (filefd != originfd)
	{
		dupfd = dup2(filefd, originfd);
		if (dupfd == -1)
			exit(EXIT_FAILURE);
		//exec_command(originfd);//
		close(filefd);
	}
	dup2(tmpfd, originfd);
}

void	both_append(t_minishell *ms, char *file)
{
	int		filefd;
	int		tmpfd;
	int		dupfd;
	int		stdfd;

	tmpfd = 0;
	dupfd = 0;
	stdfd = 1;
	filefd = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (filefd == -1)
		exit(EXIT_FAILURE);
	while (stdfd < 3)
	{
		tmpfd = dup(stdfd);
		dupfd = dup2(filefd, stdfd);
		if (dupfd == -1)
			exit(EXIT_FAILURE);
		//exec_command(stdfd);//
		dup2(tmpfd, stdfd);
		stdfd++;
	}
	close(filefd);
}

void	std_append(t_minishell *ms, int originfd, int outfd)
{
	int		tmpfd;
	int		dupfd;

	tmpfd = 0;
	dupfd = 0;
	tmpfd = dup(originfd);
	if (outfd != originfd)
	{
		dupfd = dup2(outfd, originfd);
		if (dupfd == -1)
			exit(EXIT_FAILURE);
		//exec_command(originfd);//
	}
	dup2(tmpfd, originfd);
}
