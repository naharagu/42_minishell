/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:06:00 by shimakaori        #+#    #+#             */
/*   Updated: 2023/02/25 12:49:26 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	file_inred(t_minishell *ms, int originfd, char *file);

void	red_in(t_minishell *ms, t_execlist	*exec, t_redlist *red)
{
	t_redlist	*startred;
	int			tmpfd_std;
	int			tmpfd_err;

	tmpfd_std = dup(STD_OUT);
	tmpfd_err = dup(STD_ERR);
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
	exec_command(exec);//
	dup2(tmpfd_std, STD_OUT);
	dup2(tmpfd_err, STD_ERR);
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
