/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cmdlist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 15:27:34 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/18 16:37:53 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_lstadd_back(t_cmdlist **lst, t_cmdlist *new);

void	add_cmdlist(t_minishell *ms, char *str)
{
	t_cmdlist	*tmp;

	tmp = cmd_lstnew(ms, str);
	cmd_lstadd_back(&ms->exec->cmd, tmp);
}

void	cmd_lstadd_back(t_cmdlist **lst, t_cmdlist *new)
{
	t_cmdlist	*tmp;

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

int	cmd_lstsize(t_cmdlist *lst)
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
