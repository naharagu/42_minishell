/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_lstclear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:03:37 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/20 12:12:51 by shimakaori       ###   ########.fr       */
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
		free_cmdline(tmp->cmdline);
		cmd_lstclear(&tmp->cmd);
		red_lstclear(&tmp->red);
		env_lstclear(&tmp->env);
		if (tmp->heredoc)
		{
			free(tmp->heredoc);
			tmp->heredoc = NULL;
		}
		free(tmp);
		tmp = NULL;
		*lst = (*lst)->next;
	}
	*lst = NULL;
}

void	free_cmdline(char **cmdline)
{
	char	**tmp;

	if (!cmdline)
		return ;
	tmp = cmdline;
	while (*tmp)
	{
		free(*tmp);
		*tmp = NULL;
		tmp++;
	}
	free(cmdline);
	cmdline = NULL;
}

void	cmd_lstclear(t_cmdlist **lst)
{
	t_cmdlist	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = *lst;
		free(tmp->str);
		tmp->str = NULL;
		free(tmp);
		tmp = NULL;
		*lst = (*lst)->next;
	}
	*lst = NULL;
}

void	red_lstclear(t_redlist **lst)
{
	t_redlist	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = *lst;
		free(tmp->str);
		tmp->str = NULL;
		free(tmp);
		tmp = NULL;
		*lst = (*lst)->next;
	}
	*lst = NULL;
}

void	env_lstclear(t_envlist **lst)
{
	t_envlist	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = *lst;
		free(tmp->key);
		tmp->key = NULL;
		free(tmp->value);
		tmp->value = NULL;
		free(tmp);
		tmp = NULL;
		*lst = (*lst)->next;
	}
	*lst = NULL;
}
