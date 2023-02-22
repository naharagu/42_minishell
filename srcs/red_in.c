/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:06:00 by shimakaori        #+#    #+#             */
/*   Updated: 2023/02/22 16:12:11 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	file_inred(t_minishell *ms, int originfd, char *file);

void	red_in(t_minishell *ms, t_execlist	*exec, t_redlist *red)
{
	t_redlist	*startred;

	startred = red;
	while (red->next->str)
	{
		if (!(ft_strncmp("<", red->str, 1)) || \
			!(ft_strncmp("1<", red->str, 2)))
			file_inred(ms, STD_OUT, red->next->str);
		if (!(ft_strncmp("2<", red->str, 2)))
			file_inred(ms, STD_ERR, red->next->str);
		red = red->next;
	}
	red = startred;
}

void	file_inred(t_minishell *ms, int originfd, char *file)
{
	int		filefd;
	int		tmpfd;
	int		dupfd;

	tmpfd = 0;
	dupfd = 0;
	filefd = open(file, O_CREAT | O_RDONLY, 0644);
	if (filefd == -1)
		exit(EXIT_FAILURE);
	tmpfd = dup(originfd);
	if (filefd != originfd)
	{
		dupfd = dup2(originfd, filefd);
		if (dupfd == -1)
			exit(EXIT_FAILURE);
		exec_command(filefd);//
		close(filefd);
	}
	dup2(tmpfd, originfd);
}
