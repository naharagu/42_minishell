/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_redlist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 15:35:33 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/07 14:26:49 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		red_lstadd_back(t_redlist **lst, t_redlist *new);
t_redlist	*red_lstlast(t_redlist *lst);

void	add_redlist(t_minishell *ms, char *str)
{
	t_redlist	*tmp;

	tmp = red_lstnew(str);
	red_lstadd_back(&ms->exec->red, tmp);
}

t_redlist	*red_lstnew(char *str)
{
	t_redlist	*red;

	red = (t_redlist *)malloc(sizeof(t_redlist) * 1);
	if (!red)
		exit_error ("malloc");
	if (str)
		red->str = ft_strdup(str);
	red->quote = NO_QUOTE;
	red->next = NULL;
	return (red);
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
