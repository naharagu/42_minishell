/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cmdlist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 15:27:34 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/24 16:12:54 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		cmd_lstadd_back(t_cmdlist **lst, t_cmdlist *new);
t_cmdlist	*cmd_lstlast(t_cmdlist *lst);

void	add_cmdlist(t_minishell *ms, char *str)
{
	t_cmdlist	*tmp;

	tmp = cmd_lstnew(ms, str);
	cmd_lstadd_back(&ms->exec->cmd, tmp);
}

t_cmdlist	*cmd_lstnew(t_minishell *ms, char *str)
{
	t_cmdlist	*cmd;

	cmd = (t_cmdlist *)malloc(sizeof(t_cmdlist) * 1);
	if (!cmd)
		exit_error (ms, "malloc");
	if (str)
		cmd->str = ft_strdup(str);
	cmd->quote = NO_QUOTE;
	cmd->next = NULL;
	return (cmd);
}

void	cmd_lstadd_back(t_cmdlist **lst, t_cmdlist *new)
{
	t_cmdlist	*last;

	if (!lst || !new)
		return ;
	if (*lst)
	{
		last = cmd_lstlast(*lst);
		last->next = new;
	}
	else
		*lst = new;
}

t_cmdlist	*cmd_lstlast(t_cmdlist *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	cmd_lstsize(t_cmdlist *lst)
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
