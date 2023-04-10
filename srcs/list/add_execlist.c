/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_execlist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:45:49 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/10 16:59:56 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		exec_lstadd_back(t_execlist **lst, t_execlist *new);
t_execlist	*exec_lstlast(t_execlist *lst);

void	add_execlist(t_minishell *ms, t_mslist	*first, size_t num)
{
	t_execlist	*tmp;

	if (num < 1)
		return ;
	tmp = exec_lstnew(first, num);
	exec_lstadd_back(&ms->exec, tmp);
}

void	exec_lstadd_back(t_execlist **lst, t_execlist *new)
{
	t_execlist	*last;

	if (!lst || !new)
		return ;
	if (*lst)
	{
		last = exec_lstlast(*lst);
		last->next = new;
	}
	else
		*lst = new;
}

t_execlist	*exec_lstlast(t_execlist *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	exec_lstsize(t_execlist *lst)
{
	int			size;

	if (!lst)
		return (0);
	size = 0;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}
