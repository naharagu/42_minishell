/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 13:01:33 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/04 13:56:16 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_heredoc(t_minishell *ms, int stdfd, char *delimiter, t_quote quote);
int		read_heredoc(t_minishell *ms, char *delimiter, t_quote quote);
char	*expand_heredoc(t_minishell *ms, char *line);

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
			dup_heredoc(ms, STD_OUT, red->next->str, red->next->quote);
		red = red->next;
	}
	red = startred;
	read_fd(ms, STD_OUT);//
	dup2(tmpfd, STD_OUT);
	close(tmpfd);
}

void	dup_heredoc(t_minishell *ms, int stdfd, char *delimiter, t_quote quote)
{
	int		filefd;
	int		dupfd;

	filefd = read_heredoc(ms, delimiter, quote);
	if (filefd == -1)
		exit_error(ms, "read_heredoc");
	if (filefd != stdfd)
	{
		dupfd = dup2(filefd, stdfd);
		if (dupfd == -1)
			exit_error(ms, "dup2");
	}
	close(filefd);
}

int	read_heredoc(t_minishell *ms, char *delimiter, t_quote quote)
{
	char	*line;
	int		pfd[2];

	if (pipe(pfd) < 0)
		exit_error(ms, "pipe");
	printf("quote= %d\n", quote);//
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
		if (quote == NO_QUOTE && ft_strchr(line, '$'))
			line = expand_heredoc(ms, line);
		ft_putendl_fd(line, pfd[1]);
		free(line);
	}
	close(pfd[1]);
	return (pfd[0]);
}

char	*expand_heredoc(t_minishell *ms, char *line)
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

// t_quote	is_delquoted(t_minishell *ms, char *delimiter)
// {
// 	t_quote	quote;

// 	quote = NO_QUOTE;
// 	while (*delimiter)
// 	{
// 		if (*delimiter == '\'' && quote == S_QUOTE)
// 			quote = END_S_QUOTE;
// 		else if (*delimiter == '\"' && quote == D_QUOTE)
// 			quote = END_D_QUOTE;
// 		else if (*delimiter == '\'' && (quote == NO_QUOTE || \
// 			quote == END_S_QUOTE || quote == END_D_QUOTE))
// 			quote = S_QUOTE;
// 		else if (*delimiter == '\"' && (quote == NO_QUOTE || \
// 			quote == END_S_QUOTE || quote == END_D_QUOTE))
// 			quote = D_QUOTE;
// 		delimiter++;
// 	}
// 	if (quote == END_S_QUOTE || quote == END_D_QUOTE)
// 		return (QUOTED);
// 	else
// 		return (quote);
// }
