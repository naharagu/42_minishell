/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_lstnew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:12:02 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/12 10:05:23 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_cmdline(t_execlist *new, t_mslist *list, size_t num);

t_execlist	*exec_lstnew(t_mslist *list, size_t num)
{
	t_execlist	*new;

	new = (t_execlist *)malloc(sizeof(t_execlist) * 1);
	fill_cmdline(new, list, num);
	new->cmdtype = NO_CMD;
	new->redtype = NO_REDIRECT;
	new->cmd = NULL;
	new->red = NULL;
	new->heredoc = heredoc_lstnew();
	new->pipe_in[0] = STDIN_FILENO;
	new->pipe_in[1] = -1;
	new->pipe_out[0] = -1;
	new->pipe_out[1] = STDOUT_FILENO;
	new->next = NULL;
	return (new);
}

void	fill_cmdline(t_execlist *new, t_mslist *list, size_t num)
{
	size_t		i;

	new->cmdline = (char **)ft_calloc(sizeof (char *), num + 1);
	if (!new || !new->cmdline)
		exit_error("malloc");
	i = 0;
	while (i < num && list->str)
	{
		new->cmdline[i] = ft_strdup(list->str);
		list = list->next;
		i++;
	}
}

t_heredoc	*heredoc_lstnew(void)
{
	t_heredoc	*heredoc;

	heredoc = malloc(sizeof(t_heredoc) * 1);
	if (!heredoc)
		exit_error("malloc");
	heredoc->docline = NULL;
	heredoc->expand = NULL;
	heredoc->delimiter = NULL;
	heredoc->quote = NO_QUOTE;
	return (heredoc);
}
