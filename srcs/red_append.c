/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_append.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:34:34 by shimakaori        #+#    #+#             */
/*   Updated: 2023/02/21 12:02:05 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	file_append(t_minishell *ms, int originfd, char *file);
void	both_append(t_minishell *ms, char *file);
void	std_append(t_minishell *ms, int originfd, int outfd);

void	red_append(t_minishell *ms, t_redlist *red)
{
	t_redlist	*startred;

	startred = red;
	if (!(red->next->str))
	{
		while (*red->str == '>' || *red->str == '&')
			red->str++;
		std_append(ms, red->fd, ft_atoi(red->str));
	}
	while (red->next->str)
	{
		if (red->next->str && (ft_strnstr(red->str, ">>", ft_strlen(red->str))))
		{
			if (red->next->next->str && ft_strchr(red->next->next->str, '&'))
				both_append(ms, red->next->str);
			else if (red->fd == STD_OUT || red->fd == STD_ERR)
				file_append(ms, red->fd, red->next->str);
			else if (red->fd == STD_OUTERR)
				both_append(ms, red->next->str);
		}
		red = red->next;
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
		exec_command(originfd);//
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
		exec_command(stdfd);//
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
		exec_command(originfd);//
	}
	dup2(tmpfd, originfd);
}
