/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 11:28:40 by shimakaori        #+#    #+#             */
/*   Updated: 2023/02/17 12:07:38 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	out_redirect(t_minishell *ms, int newfd, char *file);

void	redirect(t_minishell *ms)
{
	t_execlist	*startexec;
	//t_redlist	*startred;

	ms->exec = startexec;
	while (ms->exec)
	{
		if (ms->exec->redtype == OUTPUT)
		{
			if (ms->exec->red->fd == STD_OUT || ms->exec->red->fd == STD_ERR)
				out_redirect(ms, ms->exec->red->fd, ms->exec->red->next->str);
			if (ms->exec->red->fd == STD_OUTERR)
			{
				out_redirect(ms, STD_OUT, ms->exec->red->next->str);
				out_redirect(ms, STD_ERR, ms->exec->red->next->str);
			}
		}
		// startred = ms->exec->red;
		// while (ms->exec->red->next)
		// {
		// 	ms->exec->red = ms->exec->red->next;
		// }
		// ms->exec->red = startred;
		ms->exec = ms->exec->next;
	}
	ms->exec = startexec;
}

void	exec_command(int newfd)
{
	write(1, "test", 4);
}

void	out_redirect(t_minishell *ms, int newfd, char *file)
{
	int	filefd;
	int	tmpfd;
	int	dupfd;

	tmpfd = 0;
	dupfd = 0;
	filefd = open(file, O_CREAT | O_WRONLY, 0644);
	if (filefd == -1)
		exit(EXIT_FAILURE);
	tmpfd = dup(newfd);
	if (filefd != newfd)
	{
		dupfd = dup2(filefd, newfd);
		if (dupfd == -1)
			exit(EXIT_FAILURE);
		close(filefd);
	}
	exec_command(newfd);
	dup2(tmpfd, newfd);
}
