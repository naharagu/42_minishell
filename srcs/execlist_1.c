/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execlist_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:12:02 by shimakaori        #+#    #+#             */
/*   Updated: 2023/02/08 15:59:30 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//static void	init_lists(t_execlist *new, t_minishell *ms);
t_cmdlist	*cmd_lstnew(t_cmdlist *cmd);
t_redlist	*red_lstnew(t_redlist *red);
t_envlist	*env_lstnew(t_envlist *env);

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
	new->cmdtype = NO_CMD;
	new->redtype = NO_REDIRECT;
	new->cmd = cmd_lstnew(new->cmd);
	new->red = red_lstnew(new->red);
	new->env = env_lstnew(new->env);
	//init_lists(new, ms);
	new->next = NULL;
	return (new);
}

t_cmdlist	*cmd_lstnew(t_cmdlist *cmd)
{
	cmd = (t_cmdlist *)malloc(sizeof(t_cmdlist));
	if (!cmd)
		exit (EXIT_FAILURE);
	cmd->str = NULL;
	//cmd->quote = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_redlist	*red_lstnew(t_redlist *red)
{
	red = (t_redlist *)malloc(sizeof(t_redlist));
	if (!red)
		exit (EXIT_FAILURE);
	red->str = NULL;
	red->fd = 0;
	red->next = NULL;
	return (red);
}

t_envlist	*env_lstnew(t_envlist *env)
{
	env = (t_envlist *)malloc(sizeof(t_envlist));
	if (!env)
		exit (EXIT_FAILURE);
	env->key = NULL;
	env->value = NULL;
	env->next = NULL;
	return (env);
}

// static void	init_lists(t_execlist *new, t_minishell *ms)
// {
// 	new->cmd = (t_cmdlist *)malloc(sizeof(t_cmdlist));
// 	if (!new->cmd)
// 		exit (EXIT_FAILURE);
// 	new->cmd->str = NULL;
// 	//new->cmd->quote = NULL;
// 	new->cmd->next = NULL;
// 	new->red = (t_redlist *)malloc(sizeof(t_redlist));
// 	if (!new->red)
// 		exit (EXIT_FAILURE);
// 	new->red->redtype = NO_REDIRECT;
// 	new->red->str = NULL;
// 	new->red->fd = 0;
// 	new->red->next = NULL;
// 	new->env = (t_envlist *)malloc(sizeof(t_envlist));
// 	if (!new->env)
// 		exit (EXIT_FAILURE);
// 	new->env->key = NULL;
// 	new->env->value = NULL;
// 	new->env->next = NULL;
// }
