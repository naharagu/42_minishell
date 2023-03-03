/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:06:00 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/03 16:03:19 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	file_inred(t_minishell *ms, int originfd, char *file);

void	red_in(t_minishell *ms, t_execlist	*exec, t_redlist *red)
{
	t_redlist	*startred;
	int			tmpfd;

	startred = red;
	while (red->next->str)
	{
		if (!(ft_strncmp("<", red->str, ft_strlen(red->str))) || \
			!(ft_strncmp("1<", red->str, ft_strlen(red->str))))
		{
			tmpfd = dup(STD_IN);
			file_inred(ms, STD_IN, red->next->str);
			read_fd(ms, STD_IN);//
			dup2(tmpfd, STD_IN);
		}
		else if (ft_strnstr(red->str, "<", ft_strlen(red->str)))
		{
			tmpfd = dup(ft_atoi(red->str));
			file_inred(ms, ft_atoi(red->str), red->next->str);
			read_fd(ms, ft_atoi(red->str));//
			dup2(tmpfd, ft_atoi(red->str));
		}
		red = red->next;
	}
	red = startred;
	close(tmpfd);
}

void	file_inred(t_minishell *ms, int originfd, char *file)
{
	int		filefd;
	int		dupfd;

	filefd = open(file, O_RDONLY);
	if (filefd == -1)
		exit_error(ms, "open");
	if (filefd != originfd)
	{
		dupfd = dup2(filefd, originfd);
		if (dupfd == -1)
			exit_error(ms, "dup2");
	}
	close(filefd);
}
