/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_prepare.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 11:28:40 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/17 22:45:15 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_redirect_file(t_redlist *red, t_minishell *ms)
{
	char	*arg;

	arg = red->next->str;
	if (red->type == OUTPUT)
		return (open(arg, O_CREAT | O_WRONLY | O_TRUNC, 0644));
	else if (red->type == INPUT)
		return (open(arg, O_RDONLY));
	else if (red->type == APPEND)
		return (open(arg, O_CREAT | O_WRONLY | O_APPEND, 0644));
	else if (red->type == HERE_DOC)
		return (run_heredoc(arg, red, ms));
	return (EXIT_SUCCESS);
}

static int	open_and_assign_fd(t_minishell *ms)
{
	t_execlist	*tmp_exec;
	t_redlist	*tmp_red;

	tmp_exec = ms->exec;
	while (tmp_exec)
	{
		tmp_red = tmp_exec->red;
		while (tmp_red)
		{
			tmp_red->fd_file = open_redirect_file(tmp_red, ms);
			if (tmp_red->fd_file < 0)
				return (-1);
			tmp_red = tmp_red->next->next;
		}
		tmp_exec = tmp_exec->next;
	}
	return (EXIT_SUCCESS);
}

static bool	is_heredoc(t_minishell *ms)
{
	t_execlist	*tmp_exec;
	t_redlist	*tmp_red;

	tmp_exec = ms->exec;
	while (tmp_exec)
	{
		tmp_red = tmp_exec->red;
		while (tmp_red)
		{
			if (tmp_red->type == HERE_DOC)
				return (true);
			tmp_red = tmp_red->next->next;
		}
		tmp_exec = tmp_exec->next;
	}
	return (false);
}

int	prepare_redirect(t_minishell *ms)
{
	if (check_redirect(ms) == EXIT_FAILURE)
	{
		g_status = 258;
		return (EXIT_FAILURE);
	}
	if (open_and_assign_fd(ms) == -1)
	{
		perror("minishell");
		g_status = 1;
		return (EXIT_FAILURE);
	}
	if (is_heredoc(ms) && g_status == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
