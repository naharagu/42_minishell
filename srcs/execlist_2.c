/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execlist_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:45:49 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/14 15:21:00 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_lstadd_back(t_execlist **lst, t_execlist *new)
{
	t_execlist	*tmp;

	if (!lst || !new)
		return ;
	if (!(*lst))
		*lst = new;
	else
	{
		//tmp = exec_lstlast(*lst);
		while ((*lst)->next)
			(*lst) = (*lst)->next;
		tmp = (*lst);
		tmp->next = new;
	}
}

void	exec_lstclear(t_execlist **lst)
{
	t_execlist	*tmp;
	size_t		i;

	if (!lst)
		return ;
	i = 0;
	while (i < exec_lstsize(*lst))
	{
		tmp = *lst;
		*lst = (*lst)->next;
		tmp->cmdtype = NO_CMD;
		tmp->redtype = NO_REDIRECT;
		tmp->std_fd = STD_OUT;
		tmp->err_fd = STD_ERR;
		free(tmp->cmdline);
		free(tmp->cmd);
		free(tmp->red);
		free(tmp->env);
		free(tmp->heredoc);
		free(tmp);
		i++;
	}
	*lst = (NULL);
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
