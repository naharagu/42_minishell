/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mslist.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 15:01:38 by shimakaori        #+#    #+#             */
/*   Updated: 2023/01/14 15:11:26 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mslist	*ms_lstnew(long value)
{
	t_mslist	*new;

	new = (t_mslist *)malloc(sizeof(t_mslist));
	if (!new)
		return (NULL);
	new->str = NULL;
	new->pipe = NO_PIPE;
	new->quote = NO_QUOTE;
	new->redirect = NO_REDIRECT;
	new->cmd = NO_CMD;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_mslist	*ms_lstlast(t_mslist *lst)
{
	if (!lst)
		return (NULL);
	if (lst->prev)
		return (lst->prev);
	return (lst);
}

void	ms_lstadd_front(t_mslist **lst, t_mslist *new)
{
	t_mslist	*last;

	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		new->prev = NULL;
		new->next = NULL;
		*lst = new;
		return ;
	}
	last = ms_lstlast(*lst);
	new->prev = last;
	new->next = *lst;
	(*lst)->prev = new;
	last->next = new;
	*lst = new;
}

void	ms_lstadd_back(t_pslist **lst, t_pslist *new)
{
	t_mslist	*last;

	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		new->prev = NULL;
		new->next = NULL;
		*lst = new;
		return ;
	}
	last = ms_lstlast(*lst);
	last->next = new;
	new->prev = last;
	new->next = (*lst);
	(*lst)->prev = new;
}

int	ms_lstsize(t_mslist *lst)
{
	t_mslist	*first;
	int			size;

	if (!lst)
		return (0);
	size = 0;
	first = lst;
	while (lst)
	{
		if (size > 0 && first == lst)
			break ;
		size++;
		lst = lst->next;
	}
	return (size);
}
