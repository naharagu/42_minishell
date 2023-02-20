/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_out.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:10:30 by shimakaori        #+#    #+#             */
/*   Updated: 2023/02/20 12:42:24 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	file_redirect(t_minishell *ms, int originfd, char *file);
void	both_redirect(t_minishell *ms, char *file);
void	std_redirect(t_minishell *ms, int originfd, int outfd);
void	exec_command(int originfd);

void	red_out(t_minishell *ms, t_redlist *red)
{
	t_redlist	*startred;

	startred = red;
	if (!(red->next->str))
	{
		while (*red->str == '>' || *red->str == '&')
			red->str++;
		std_redirect(ms, red->fd, ft_atoi(red->str));
	}
	while (red->next->str)
	{
		if (red->next->str && (ft_strchr(red->str, '>')))
		{
			if (red->next->next->str && ft_strchr(red->next->next->str, '&'))
				both_redirect(ms, red->next->str);
			else if (red->fd == STD_OUT || red->fd == STD_ERR)
				file_redirect(ms, red->fd, red->next->str);
			else if (red->fd == STD_OUTERR)
				both_redirect(ms, red->next->str);
		}
		red = red->next;
	}
	red = startred;
}

void	file_redirect(t_minishell *ms, int originfd, char *file)
{
	int		filefd;
	int		tmpfd;
	int		dupfd;

	tmpfd = 0;
	dupfd = 0;
	filefd = open(file, O_CREAT | O_WRONLY, 0644);
	if (filefd == -1)
		exit(EXIT_FAILURE);
	tmpfd = dup(originfd);
	if (filefd != originfd)
	{
		dupfd = dup2(filefd, originfd);
		if (dupfd == -1)
			exit(EXIT_FAILURE);
		close(filefd);
	}
	exec_command(originfd);//
	dup2(tmpfd, originfd);
}

void	both_redirect(t_minishell *ms, char *file)
{
	int		filefd;
	int		tmpfd;
	int		dupfd;
	int		stdfd;

	tmpfd = 0;
	dupfd = 0;
	stdfd = 1;
	filefd = open(file, O_CREAT | O_WRONLY, 0644);
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

void	std_redirect(t_minishell *ms, int originfd, int outfd)
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
	}
	exec_command(originfd);//
	dup2(tmpfd, originfd);
}

void	exec_command(int originfd)
{
	char	*str;

	str = ft_strdup("test");
	ft_putnbr_fd(originfd, originfd);
	ft_putchar_fd('\n', originfd);
	ft_putendl_fd(str, originfd);
	free(str);
}
