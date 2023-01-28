/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execlist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:12:02 by shimakaori        #+#    #+#             */
/*   Updated: 2023/01/28 21:48:11 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_lists(t_execlist *new, t_minishell *ms);

t_execlist	*exec_lstnew(t_minishell *ms, t_mslist *list, size_t num)
{
	t_execlist	*new;
	size_t		j;

	new = (t_execlist *)malloc(sizeof(t_execlist));
	if (!new)
		return (NULL);
	new->cmdline = (char **)ft_calloc(sizeof (char *), num);
	if (!new->cmdline)
		return (NULL);
	j = 0;
	while (j < num)
	{
		new->cmdline[j] = list->str;
		printf("cmdline= %s\n", new->cmdline[j]);//
		list = list->next;
		j++;
	}
	init_lists(new, ms);
	new->next = NULL;
	return (new);
}

void	init_lists(t_execlist *new, t_minishell *ms)
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

// t_execlist	*exec_lstlast(t_execlist *lst)
// {
// 	if (!lst)
// 		return (NULL);
// 	if (lst->prev)
// 		return (lst->prev);
// 	return (lst);
// }

// void	exec_lstadd_back(t_execlist **lst, t_execlist *new)
// {
// 	t_execlist	*last;

// 	if (!lst || !new)
// 		return ;
// 	if (!(*lst))
// 	{
// 		new->prev = NULL;
// 		new->next = NULL;
// 		*lst = new;
// 		return ;
// 	}
// 	last = exec_lstlast(*lst);
// 	last->next = new;
// 	new->prev = last;
// 	new->next = (*lst);
// 	(*lst)->prev = new;
// }

// int	exec_lstsize(t_execlist *lst)
// {
// 	t_execlist	*first;
// 	int			size;

// 	if (!lst)
// 		return (0);
// 	size = 0;
// 	first = lst;
// 	while (lst)
// 	{
// 		if (size > 0 && first == lst)
// 			break ;
// 		size++;
// 		lst = lst->next;
// 	}
// 	return (size);
// }

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
