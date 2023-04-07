/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_envlist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 15:56:49 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/07 14:26:02 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		env_lstadd_back(t_envlist **lst, t_envlist *new);
t_envlist	*env_lstlast(t_envlist *lst);

void	add_envlist(t_minishell *ms, char *key, char *value)
{
	t_envlist	*tmp;

	tmp = env_lstnew(key, value);
	env_lstadd_back(&ms->env, tmp);
}

t_envlist	*env_lstnew(char *key, char *value)
{
	t_envlist	*env;

	env = (t_envlist *)malloc(sizeof(t_envlist) * 1);
	if (!env)
		exit_error ("malloc");
	env->key = key;
	env->value = value;
	env->next = NULL;
	return (env);
}

void	env_lstadd_back(t_envlist **lst, t_envlist *new)
{
	t_envlist	*last;

	if (!lst || !new)
		return ;
	if (*lst)
	{
		last = env_lstlast(*lst);
		last->next = new;
	}
	else
		*lst = new;
}

t_envlist	*env_lstlast(t_envlist *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
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
