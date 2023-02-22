/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 11:28:40 by shimakaori        #+#    #+#             */
/*   Updated: 2023/02/22 16:09:40 by shimakaori       ###   ########.fr       */
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
		//printf ("redtype= %d\n", ms->exec->redtype);//
		startred = ms->exec->red;
		while (ms->exec->red->str)
		{
			check_fd(ms->exec, ms->exec->red);
			ms->exec->red = ms->exec->red->next;
		}
		ms->exec->red = startred;
		//printf ("stdfd= %d\n", ms->exec->std_fd);//
		//printf ("errfd= %d\n", ms->exec->err_fd);//
		if (ms->exec->redtype == OUTPUT)
			red_out (ms, ms->exec, ms->exec->red);
		else if (ms->exec->redtype == APPEND)
			red_append (ms, ms->exec, ms->exec->red);
		if (ms->exec->redtype == INPUT)
			red_in (ms, ms->exec, ms->exec->red);
		// if (ms->exec->redtype == HERE_DOC)
		// 	here_document (ms, ms->exec->red);
		ms->exec = ms->exec->next;
	}
	ms->exec = startexec;
}

void	check_fd(t_execlist	*exec, t_redlist *red)
{
	if (!(ft_strncmp(">/dev/null", red->str, 10)) || \
		!(ft_strncmp("1>/dev/null", red->str, 10)))
		exec->std_fd = DELETE;
	else if (!(ft_strncmp("2>/dev/null", red->str, 10)))
		exec->err_fd = DELETE;
	else if (!(ft_strncmp(">", red->str, 1)) || \
		!(ft_strncmp("1>", red->str, 2)))
		exec->std_fd = FILE_1;
	else if (!(ft_strncmp("2>", red->str, 2)))
		exec->err_fd = FILE_2;
	else if ((ft_strnstr(red->str, "&>", 2)))
	{
		exec->std_fd = FILE_1;
		exec->err_fd = FILE_1;
	}
	if (!(ft_strncmp("2>&1", red->str, 4)))
		exec->err_fd = exec->std_fd;
	else if (!(ft_strncmp(">&2", red->str, 3)) || \
		(!(ft_strncmp("1>&2", red->str, 4))))
		exec->std_fd = exec->err_fd;
}
