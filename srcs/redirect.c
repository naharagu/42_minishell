/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 11:28:40 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/20 12:21:06 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_fd(t_execlist	*exec, t_redlist *red);

void	redirect(t_minishell *ms)
{
	t_execlist	*startexec;
	t_redlist	*startred;

	startexec = ms->exec;
	while (ms->exec)
	{
		startred = ms->exec->red;
		while (ms->exec->red)
		{
			check_fd(ms->exec, ms->exec->red);
			ms->exec->red = ms->exec->red->next;
		}
		ms->exec->red = startred;
		if (ms->exec->redtype == OUTPUT)
			red_out (ms, ms->exec, ms->exec->red);
		else if (ms->exec->redtype == APPEND)
			red_append (ms, ms->exec, ms->exec->red);
		else if (ms->exec->redtype == INPUT)
			red_in (ms, ms->exec->red);
		else if (ms->exec->redtype == HERE_DOC)
			red_heredoc (ms, ms->exec, ms->exec->red);
		ms->exec = ms->exec->next;
	}
	ms->exec = startexec;
}

void	check_fd(t_execlist	*exec, t_redlist *red)
{
	if (!(ft_strncmp(">", red->str, ft_strlen(red->str))) || \
		!(ft_strncmp("1>", red->str, ft_strlen(red->str))) || \
		!(ft_strncmp(">>", red->str, ft_strlen(red->str))) || \
		!(ft_strncmp("1>>", red->str, ft_strlen(red->str))))
		exec->std_fd = FILE_1;
	else if (!(ft_strncmp("2>", red->str, ft_strlen(red->str))) || \
		!(ft_strncmp("2>>", red->str, ft_strlen(red->str))))
		exec->err_fd = FILE_2;
	else if (!(ft_strncmp("&>", red->str, ft_strlen(red->str))) || \
		!(ft_strncmp(">&", red->str, ft_strlen(red->str))) || \
		!(ft_strncmp("&>>", red->str, ft_strlen(red->str))) || \
		!(ft_strncmp(">>&", red->str, ft_strlen(red->str))))
	{
		exec->std_fd = FILE_1;
		exec->err_fd = FILE_1;
	}
	if (!(ft_strncmp("2>&1", red->str, 4)))
		exec->err_fd = exec->std_fd;
	else if (!(ft_strncmp(">&2", red->str, 3)) || \
		!(ft_strncmp("1>&2", red->str, 4)))
		exec->std_fd = exec->err_fd;
}
