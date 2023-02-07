/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execlist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:12:02 by shimakaori        #+#    #+#             */
/*   Updated: 2023/02/07 15:54:03 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_lists(t_execlist *new, t_minishell *ms);

t_execlist	*exec_lstnew(t_minishell *ms, t_mslist *list, size_t num)
{
	t_execlist	*new;
	size_t		j;

	if (!ms || !list || !num)
		return (NULL);
	new = (t_execlist *)malloc(sizeof(t_execlist));
	if (!new)
		return (NULL);
	new->cmdline = (char **)ft_calloc(sizeof (char *), num + 1);
	if (!new->cmdline)
		return (NULL);
	j = 0;
	while (j < num)
	{
		new->cmdline[j] = list->str;
		list = list->next;
		j++;
	}
	init_lists(new, ms);
	new->next = NULL;
	return (new);
}

static void	init_lists(t_execlist *new, t_minishell *ms)
{
	new->cmd = (t_cmdlist *)malloc(sizeof(t_cmdlist));
	if (!new->cmd)
		exit (EXIT_FAILURE);
	new->cmd->cmdtype = NO_CMD;
	new->cmd->str = NULL;
	new->cmd->next = NULL;
	new->red = (t_redlist *)malloc(sizeof(t_redlist));
	if (!new->red)
		exit (EXIT_FAILURE);
	new->red->redtype = NO_REDIRECT;
	new->red->str = NULL;
	new->red->fd = 0;
	new->red->next = NULL;
	new->env = (t_envlist *)malloc(sizeof(t_envlist));
	if (!new->env)
		exit (EXIT_FAILURE);
	new->env->key = NULL;
	new->env->value = NULL;
	new->env->next = NULL;
}

t_execlist	*exec_lstlast(t_execlist *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
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
		tmp = exec_lstlast(*lst);
		tmp->next = new;
	}
}

int	exec_lstsize(t_execlist *lst)
{
	t_execlist	*first;
	int			size;

	if (!lst)
		return (0);
	size = 0;
	first = lst;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

// void	exec_lstclear(t_execlist **lst)
// {
// 	t_execlist	*tmp;
// 	size_t		i;

// 	if (!lst)
// 		return ;
// 	i = 0;
// 	while (i < exec_lstsize(*lst))
// 	{
// 		tmp = *lst;
// 		*lst = (*lst)->next;
// 		free(tmp->str);
// 		free(tmp);
// 		i++;
// 	}
// 	*lst = (NULL);
// }
