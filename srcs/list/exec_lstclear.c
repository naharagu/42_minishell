/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_lstclear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:03:37 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/26 09:42:12 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmdline(char **cmdline);
void	cmd_lstclear(t_cmdlist **lst);
void	red_lstclear(t_redlist **lst);
void	env_lstclear(t_envlist **lst);

void	exec_lstclear(t_execlist **lst)
{
	t_execlist	*tmp;

	if (!lst || !(*lst))
		return ;
	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free_cmdline(tmp->cmdline);
		tmp->cmdtype = NO_CMD;
		tmp->redtype = NO_REDIRECT;
		cmd_lstclear(&tmp->cmd);
		red_lstclear(&tmp->red);
		free(tmp->heredoc);
		free(tmp);
	}
	*lst = NULL;
}

void	free_cmdline(char **cmdline)
{
	char	**tmp;

	if (!cmdline || !(*cmdline))
		return ;
	tmp = cmdline;
	while (*tmp)
	{
		free(*tmp);
		tmp++;
	}
	free(cmdline);
}

void	cmd_lstclear(t_cmdlist **lst)
{
	t_cmdlist	*tmp;

	if (!lst || !(*lst))
		return ;
	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		if (tmp->str)
			free(tmp->str);
		free(tmp);
	}
	*lst = NULL;
}

void	red_lstclear(t_redlist **lst)
{
	t_redlist	*tmp;

	if (!lst || !(*lst))
		return ;
	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		if (tmp->str)
			free(tmp->str);
		free(tmp);
	}
	*lst = NULL;
}

void	env_lstclear(t_envlist **lst)
{
	t_envlist	*tmp;

	if (!lst || !(*lst))
		return ;
	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		if (tmp->key)
			free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
	*lst = NULL;
}
