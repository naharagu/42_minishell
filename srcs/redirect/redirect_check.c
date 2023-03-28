/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 11:28:40 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/28 21:19:19 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	assign_redtype(t_minishell *ms, t_redlist *red)
{
	if (red->str == NULL)
		syntax_error(ms, "redirect", SYNTAX_ERROR);
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
		syntax_error(ms, "redirect", SYNTAX_ERROR);
}

static void	validate_redirect(t_minishell *ms, t_redlist *red)
{
	t_redlist	*tmp_red;

	tmp_red = red;
	while (tmp_red)
	{
		if (tmp_red->next == NULL)
			syntax_error(ms, "redirect", SYNTAX_ERROR);
		assign_redtype(ms, tmp_red);
		if (tmp_red->str == NULL)
			syntax_error(ms, "redirect", SYNTAX_ERROR);
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
		if (tmp_exec->redtype != NO_REDIRECT)
			validate_redirect(ms, tmp_exec->red);
		tmp_exec = tmp_exec->next;
	}
	return (EXIT_SUCCESS);
}
