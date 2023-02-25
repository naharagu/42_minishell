/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:06:00 by shimakaori        #+#    #+#             */
/*   Updated: 2023/02/25 14:47:36 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	file_inred(t_minishell *ms, int originfd, char *file);

void	red_in(t_minishell *ms, t_execlist	*exec, t_redlist *red)
{
	t_redlist	*startred;
	int			tmpfd_in;

	tmpfd_in = dup(STD_IN);
	startred = red;
	while (red->next->str)
	{
		if (!(ft_strncmp("<", red->str, 1)) || \
			!(ft_strncmp("1<", red->str, 2)))
			file_inred(ms, STD_IN, red->next->str);
		red = red->next;
	}
	red = startred;
	exec_command(exec);//
	dup2(tmpfd_in, STD_IN);
	close(tmpfd_in);
}

void	file_inred(t_minishell *ms, int originfd, char *file)
{
	int		filefd;
	int		dupfd;

	filefd = open(file, O_RDONLY);
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
