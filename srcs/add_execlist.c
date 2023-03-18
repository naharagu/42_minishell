/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_execlist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:45:49 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/18 15:35:54 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_lstadd_back(t_execlist **lst, t_execlist *new);

void	add_execlist(t_minishell *ms, t_mslist	*first, size_t num)
{
	t_execlist	*tmp;

	tmp = exec_lstnew(ms, first, num);
	exec_lstadd_back(&ms->exec, tmp);
}

void	exec_lstadd_back(t_execlist **lst, t_execlist *new)
{
	t_execlist	*tmp;

	if (!lst || !new)
		return ;
	if (!(*lst))
		*lst = new;
	else
	{
		while ((*lst)->next)
			(*lst) = (*lst)->next;
		tmp = (*lst);
		tmp->next = new;
	}
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
