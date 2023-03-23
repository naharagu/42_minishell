/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_redlist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 15:35:33 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/18 19:08:02 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		red_lstadd_back(t_redlist **lst, t_redlist *new);
t_redlist	*red_lstlast(t_redlist *lst);

void	add_redlist(t_minishell *ms, char *str)
{
	t_redlist	*tmp;

	tmp = red_lstnew(ms, str);
	red_lstadd_back(&ms->exec->red, tmp);
}

void	red_lstadd_back(t_redlist **lst, t_redlist *new)
{
	t_redlist	*last;

	if (!lst || !new)
		return ;
	if (*lst)
	{
		last = red_lstlast(*lst);
		last->next = new;
	}
	else
		*lst = new;
}

t_redlist	*red_lstlast(t_redlist *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	red_lstsize(t_redlist *lst)
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