/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 11:28:40 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/23 22:00:30 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	assign_redtype(t_redlist *red)
{
	if (red->str == NULL)
		exit(258);//
	if (ft_strnstr(red->str, ">>", ft_strlen(red->str)))
		red->next->type = APPEND;
	else if (ft_strnstr(red->str, ">", ft_strlen(red->str)))
		red->next->type = OUTPUT;
	else if (ft_strnstr(red->str, "<<", ft_strlen(red->str)))
		red->next->type = HERE_DOC;
	else if (ft_strnstr(red->str, "<", ft_strlen(red->str)))
		red->next->type = INPUT;
	else
		exit(258);
}


void	validate_red(t_minishell *ms, t_redlist *red)
{
	t_redlist *tmp_red;

	(void) ms;
	tmp_red = red;
	while (tmp_red && tmp_red->str)
	{
		printf("%s\n", tmp_red->str);
		assign_redtype(tmp_red);
		if (tmp_red->next == NULL)
			exit(258);
		tmp_red = tmp_red->next;
		// assign_fd(tmp_red);
		tmp_red = tmp_red->next;
	}
	return ;
}

int	check_redirect(t_minishell *ms)
{
	t_execlist *tmp_exec;
	t_redlist *tmp_red;

	if (ms->exec->redtype == NO_REDIRECT)
		return 0;
	tmp_exec = ms->exec;
	tmp_red = ms->exec->red;
	while (tmp_exec)
	{
		validate_red(ms, tmp_red);
		tmp_exec = tmp_exec->next;
		(void) tmp_exec;//
	}
	return 0;
}

void	redirect(t_minishell *ms)
{
	(void) ms;//
}
