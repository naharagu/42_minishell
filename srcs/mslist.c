/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mslist.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 15:01:38 by shimakaori        #+#    #+#             */
/*   Updated: 2023/01/27 15:17:59 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mslist	*ms_lstnew(size_t len, char *str)
{
	t_mslist	*new;
	size_t		j;

	new = (t_mslist *)malloc(sizeof(t_mslist));
	if (!new)
		return (NULL);
	new->str = ft_calloc(sizeof(char), (len + 1));
	if (!(new->str))
		return (NULL);
	j = 0;
	while (j < len)
	{
		new->str[j] = str[j];
		j++;
	}
	new->pipe = NO_PIPE;
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

void	ms_lstadd_back(t_mslist **lst, t_mslist *new)
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

void	ms_lstclear(t_mslist **lst)
{
	t_mslist	*tmp;
	size_t		i;

	if (!lst)
		return ;
	i = 0;
	while (i < ms_lstsize(*lst))
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp->str);
		free(tmp);
		i++;
	}
	*lst = (NULL);
}
