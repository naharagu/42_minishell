/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 11:28:40 by shimakaori        #+#    #+#             */
/*   Updated: 2023/02/17 13:02:03 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	out_redirect(t_minishell *ms, t_redlist *red);
void	file_redirect(t_minishell *ms, int originfd, char *file);
void	std_redirect(t_minishell *ms, int originfd, int outfd);
void	exec_command(int originfd);

void	redirect(t_minishell *ms)
{
	t_execlist	*startexec;

	ms->exec = startexec;
	while (ms->exec)
	{
		if (ms->exec->redtype == OUTPUT)
			out_redirect (ms, ms->exec->red);
		ms->exec = ms->exec->next;
	}
	ms->exec = startexec;
}

void	out_redirect(t_minishell *ms, t_redlist *red)
{
	int	outfd;

	if (red->next->str)
	{
		if (red->fd == STD_OUT || red->fd == STD_ERR)
			file_redirect(ms, red->fd, red->next->str);
		else if (red->fd == STD_OUTERR)
		{
			file_redirect(ms, STD_OUT, red->next->str);
			file_redirect(ms, STD_ERR, red->next->str);
		}
	}
	else
	{
		while (*red->str == '>' || *red->str == '&')
			red->str++;
		std_redirect(ms, red->fd, ft_atoi(red->str));
	}
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
	exec_command(originfd);
	dup2(tmpfd, originfd);
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
	write(originfd, "test\n", 5);
}
