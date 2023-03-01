/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mslist.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 15:01:38 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/01 17:18:12 by shimakaori       ###   ########.fr       */
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
	new->next = NULL;
	return (new);
}

t_mslist	*ms_lstlast(t_mslist *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	ms_lstadd_back(t_mslist **lst, t_mslist *new)
{
	t_mslist	*tmp;

	if (!lst || !new)
		return ;
	if (!(*lst))
		*lst = new;
	else
	{
		tmp = ms_lstlast(*lst);
		tmp->next = new;
	}
}

int	ms_lstsize(t_mslist *lst)
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
		tmp->pipe = NO_PIPE;
		free(tmp);
		i++;
	}
	*lst = (NULL);
}
