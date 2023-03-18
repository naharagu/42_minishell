/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_redlist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 15:35:33 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/18 15:52:24 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	red_lstadd_back(t_redlist **lst, t_redlist *new);

void	add_redlist(t_minishell *ms, char *str)
{
	t_redlist	*tmp;

	tmp = red_lstnew(ms, str);
	red_lstadd_back(&ms->exec->red, tmp);
}

void	red_lstadd_back(t_redlist **lst, t_redlist *new)
{
	t_redlist	*tmp;

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

int	red_lstsize(t_redlist *lst)
{
	int			size;

	if (!lst)
		return (0);
	size = 0;
	while (lst->next)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}
