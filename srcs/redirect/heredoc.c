/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 13:01:33 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/28 21:19:59 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_loop(int fd_heredoc[2], char *delimiter)
{
	char	*line;

	while (true)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd_heredoc[1], line, ft_strlen(line));
		write(fd_heredoc[1], "\n", 1);
		free(line);
	}
}

int	run_heredoc(char *delimiter, t_redlist *red, t_minishell *ms)
{
	int	fd_heredoc[2];

	(void)ms;
	(void)red;
	if (delimiter == NULL)
		return (-1);
	pipe(fd_heredoc);
	heredoc_loop(fd_heredoc, delimiter);
	close(fd_heredoc[1]);
	return (fd_heredoc[0]);
}
