/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_envlist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 15:56:49 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/18 18:29:05 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_lstadd_back(t_envlist **lst, t_envlist *new);

void	add_envlist(t_minishell *ms, char *key, char *value)
{
	t_envlist	*tmp;

	tmp = env_lstnew(ms, key, value);
	env_lstadd_back(&ms->exec->env, tmp);
}

void	env_lstadd_back(t_envlist **lst, t_envlist *new)
{
	t_envlist	*tmp;

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

int	env_lstsize(t_envlist *lst)
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
