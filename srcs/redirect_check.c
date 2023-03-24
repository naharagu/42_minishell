/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 11:28:40 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/24 10:17:28 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assign_redtype(t_redlist *red)
{
	if (red->str == NULL)
		exit(258); //
	if (ft_strnstr(red->str, ">>", ft_strlen(red->str)))
	{
		red->type = APPEND;
		red->fd_target = STDOUT_FILENO;
	}
	else if (ft_strnstr(red->str, ">", ft_strlen(red->str)))
	{
		red->type = OUTPUT;
		red->fd_target = STDOUT_FILENO;
	}
	else if (ft_strnstr(red->str, "<<", ft_strlen(red->str)))
	{
		red->type = HERE_DOC;
		red->fd_target = STDIN_FILENO;
	}
	else if (ft_strnstr(red->str, "<", ft_strlen(red->str)))
	{
		red->type = INPUT;
		red->fd_target = STDIN_FILENO;
	}
	else
		exit(258); //
}

void	validate_red(t_redlist *red)
{
	t_redlist	*tmp_red;

	tmp_red = red;
	while (tmp_red && tmp_red->str)
	{
		if (tmp_red->next == NULL)
			exit(258); //
		assign_redtype(tmp_red);
		tmp_red = tmp_red->next;
		if (tmp_red->str == NULL)
			exit(258); //
		tmp_red = tmp_red->next;
	}
	return ;
}

int	check_redirect(t_minishell *ms)
{
	t_execlist	*tmp_exec;

	tmp_exec = ms->exec;
	while (tmp_exec)
	{
		if (ms->exec->redtype != NO_REDIRECT)
			validate_red(tmp_exec->red);
		tmp_exec = tmp_exec->next;
	}
	return (0);
}
