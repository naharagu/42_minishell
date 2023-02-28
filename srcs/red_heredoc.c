/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 13:01:33 by shimakaori        #+#    #+#             */
/*   Updated: 2023/02/28 11:00:51 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	file_heredoc(t_minishell *ms, int originfd, char *delimiter);
int		read_heredoc(t_minishell *ms, const char *delimiter);

void	red_heredoc(t_minishell *ms, t_execlist	*exec, t_redlist *red)
{
	t_redlist	*startred;
	int			tmpfd_std;

	startred = red;
	tmpfd_std = dup(STD_OUT);
	while (red->next->str)
	{
		if (!(ft_strncmp("<<", red->str, 2)))
			file_heredoc(ms, STD_OUT, red->next->str);
		red = red->next;
	}
	red = startred;
	exec_command(exec);//
	dup2(tmpfd_std, STD_OUT);
	close(tmpfd_std);
}

void	file_heredoc(t_minishell *ms, int originfd, char *delimiter)
{
	int		filefd;
	int		dupfd;

	filefd = read_heredoc(ms, delimiter);
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

int	read_heredoc(t_minishell *ms, const char *delimiter)
{
	char	*line;
	int		pfd[2];

	if (pipe(pfd) < 0)
		exit_error(ms, "pipe");
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (!(ft_strncmp(line, delimiter, ft_strlen(line))))
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, pfd[1]);
		free(line);
	}
	close(pfd[1]);
	return (pfd[0]);
}
