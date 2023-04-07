/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 11:28:40 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/07 13:31:35 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	assign_redtype(t_redlist *red)
{
	if (red->str == NULL)
		return (syntax_error( "redirect", SYNTAX_ERROR));
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
		return (syntax_error( "redirect", SYNTAX_ERROR));
	return (EXIT_SUCCESS);
}

static int	validate_redirect(t_redlist *red)
{
	t_redlist	*tmp_red;

	tmp_red = red;
	while (tmp_red)
	{
		if (tmp_red->next == NULL)
			return (syntax_error( "redirect", SYNTAX_ERROR));
		if (assign_redtype(tmp_red) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		tmp_red = tmp_red->next;
		if (tmp_red->str == NULL)
			return (syntax_error( "redirect", SYNTAX_ERROR));
		tmp_red = tmp_red->next;
	}
	return (EXIT_SUCCESS);
}

int	check_redirect(t_minishell *ms)
{
	t_execlist	*tmp_exec;

	tmp_exec = ms->exec;
	while (tmp_exec)
	{
		if (tmp_exec->redtype != NO_REDIRECT)
		{
			if (validate_redirect(tmp_exec->red) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		tmp_exec = tmp_exec->next;
	}
	return (EXIT_SUCCESS);
}
