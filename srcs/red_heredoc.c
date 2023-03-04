/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 13:01:33 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/03 23:49:03 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_heredoc(t_minishell *ms, int originfd, char *delimiter);
int		read_heredoc(t_minishell *ms, char *delimiter);
char	*expand_line(t_minishell *ms, char *line);

void	red_heredoc(t_minishell *ms, t_execlist	*exec, t_redlist *red)
{
	t_redlist	*startred;
	int			tmpfd;

	startred = red;
	tmpfd = dup(STD_OUT);
	while (red->next->str)
	{
		if (!(ft_strncmp("<<", red->str, ft_strlen(red->str))) || \
			!(ft_strncmp("1<<", red->str, ft_strlen(red->str))))
			dup_heredoc(ms, STD_OUT, red->next->str);
		red = red->next;
	}
	red = startred;
	read_fd(ms, STD_OUT);//
	dup2(tmpfd, STD_OUT);
	close(tmpfd);
}

void	dup_heredoc(t_minishell *ms, int originfd, char *delimiter)
{
	int		filefd;
	int		dupfd;

	filefd = read_heredoc(ms, delimiter);
	if (filefd == -1)
		exit_error(ms, "read_heredoc");
	if (filefd != originfd)
	{
		dupfd = dup2(filefd, originfd);
		if (dupfd == -1)
			exit_error(ms, "dup2");
	}
	close(filefd);
}

int	read_heredoc(t_minishell *ms, char *delimiter)
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
		if (!(is_delquoted(ms, delimiter)) && ft_strchr(line, '$'))
			line = expand_line(ms, line);
		ft_putendl_fd(line, pfd[1]);
		free(line);
	}
	close(pfd[1]);
	return (pfd[0]);
}

char	*expand_line(t_minishell *ms, char *line)
{
	t_execlist	*startexec;
	t_envlist	*startenv;
	char		*tmp;
	size_t		len;

	tmp = NULL;
	while (*line)
	{
		len = 0;
		while (*line && *line != '$')
			len++;
		tmp = ft_substr(line, 0, len);
		if (!tmp)
			return (NULL);
		line += len;
		while (*line && *line == '$')
			line++;
		startexec = ms->exec;
		while (ms->exec)
		{
			startenv = ms->exec->env;
			while (ms->exec->env)
			{
				if (ft_strnstr(line, ms->exec->env->key, \
					ft_strlen(ms->exec->env->key)))
				{
					tmp = ft_strjoin(tmp, ms->exec->env->value);
					line += ft_strlen(ms->exec->env->key);
				}
				ms->exec->env = ms->exec->env->next;
			}
			ms->exec->env = startenv;
			ms->exec = ms->exec->next;
		}
		ms->exec = startexec;
		line++;
	}
	return (tmp);
}
