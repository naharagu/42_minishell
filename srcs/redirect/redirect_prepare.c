/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_prepare.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 11:28:40 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/26 11:30:13 by naharagu         ###   ########.fr       */
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
	return (0);
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
			// fprintf(stderr, "open file fd is %d\n", tmp_red->fd_file);//
			if (tmp_red->fd_file < 0)
				return (-1);
			tmp_red = tmp_red->next->next;
		}
		tmp_exec = tmp_exec->next;
	}
	return (EXIT_SUCCESS);
}

void	prepare_redirect(t_minishell *ms)
{
	if (check_redirect(ms) == -1)
		return ; //exit status
	if (open_and_assign_fd(ms) == -1)
		return ; //exit status
}
