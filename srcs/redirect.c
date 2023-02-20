/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 11:28:40 by shimakaori        #+#    #+#             */
/*   Updated: 2023/02/18 14:54:44 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	in_redirect(t_minishell *ms, t_redlist *red);

void	redirect(t_minishell *ms)
{
	t_execlist	*startexec;

	ms->exec = startexec;
	while (ms->exec)
	{
		if (ms->exec->redtype == OUTPUT)
			red_out (ms, ms->exec->red);
		// else if (ms->exec->redtype == APPEND)
		// 	append (ms, ms->exec->red);
		// if (ms->exec->redtype == INPUT)
		// 	in_redirect (ms, ms->exec->red);
		// if (ms->exec->redtype == HERE_DOC)
		// 	here_document (ms, ms->exec->red);
		ms->exec = ms->exec->next;
	}
	ms->exec = startexec;
}

void	in_redirect(t_minishell *ms, t_redlist *red)
{
	
}
