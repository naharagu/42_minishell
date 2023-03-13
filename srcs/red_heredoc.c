/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 13:01:33 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/10 18:34:05 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_heredoc(t_minishell *ms, t_execlist	*exec, t_heredoc *heredoc);
int		read_heredoc(t_minishell *ms, t_execlist *exec, t_heredoc *heredoc);
size_t	assign_value(t_minishell *ms, t_execlist *exec, t_heredoc *heredoc);
char	*expand_heredoc(t_minishell *ms, t_execlist *exec, t_heredoc *heredoc);

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
		{
			exec->heredoc->delimiter = red->next->str;
			exec->heredoc->quote = red->next->quote;
			dup_heredoc(ms, exec, exec->heredoc);
		}
		red = red->next;
	}
	red = startred;
	read_fd(ms, STD_OUT);//
	dup2(tmpfd, STD_OUT);
	close(tmpfd);
}

void	dup_heredoc(t_minishell *ms, t_execlist	*exec, t_heredoc *heredoc)
{
	int		filefd;
	int		dupfd;

	filefd = read_heredoc(ms, exec, heredoc);
	if (filefd == -1)
		exit_error(ms, "read_heredoc");
	if (filefd != STD_OUT)
	{
		dupfd = dup2(filefd, STD_OUT);
		if (dupfd == -1)
			exit_error(ms, "dup2");
	}
	close(filefd);
}

int	read_heredoc(t_minishell *ms, t_execlist *exec, t_heredoc *heredoc)
{
	int		pfd[2];

	if (pipe(pfd) < 0)
		exit_error(ms, "pipe");
	handle_signal(ms, SIGINT, HEREDOC);
	while (1)
	{
		heredoc->docline = readline("> ");
		if (heredoc->docline && !(ft_strncmp(heredoc->docline, \
			heredoc->delimiter, ft_strlen(heredoc->delimiter))))
		{
			free(heredoc->docline);
			break ;
		}
		if (heredoc->docline && ft_strchr(heredoc->docline, '$') \
			&& heredoc->quote == NO_QUOTE)
			heredoc->docline = expand_heredoc(ms, exec, heredoc);
		ft_putendl_fd(heredoc->docline, pfd[1]);
		free(heredoc->docline);
	}
	close(pfd[1]);
	handle_signal(ms, SIGINT, DEFAULT);
	return (pfd[0]);
}

size_t	assign_value(t_minishell *ms, t_execlist *exec, t_heredoc *heredoc)
{
	t_execlist	*startexec;
	t_envlist	*startenv;

	startexec = ms->exec;
	while (ms->exec)
	{
		startenv = ms->exec->env;
		while (ms->exec->env)
		{
			if (ft_strnstr(heredoc->docline, ms->exec->env->key, \
				ft_strlen(ms->exec->env->key)))
			{
				heredoc->expand = ft_strjoin(heredoc->expand, \
					ms->exec->env->value);
				return (ft_strlen(ms->exec->env->key));
			}
			ms->exec->env = ms->exec->env->next;
		}
		ms->exec->env = startenv;
		ms->exec = ms->exec->next;
	}
	ms->exec = startexec;
	return (0);
}

char	*expand_heredoc(t_minishell *ms, t_execlist *exec, t_heredoc *heredoc)
{
	size_t		len;

	while (*heredoc->docline)
	{
		len = 0;
		while (*heredoc->docline && *heredoc->docline != '$')
			len++;
		if (!heredoc->expand)
			heredoc->expand = ft_substr(heredoc->docline, 0, len);
		else
			heredoc->expand = ft_strjoin(heredoc->expand, \
			ft_substr(heredoc->docline, 0, len));
		heredoc->docline += len;
		if (*heredoc->docline == '$')
		{
			while (*heredoc->docline && *heredoc->docline == '$')
				heredoc->docline++;
			heredoc->docline += assign_value(ms, exec, heredoc);
		}
		heredoc->docline++;
	}
	return (heredoc->expand);
}
