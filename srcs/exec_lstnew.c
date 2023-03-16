/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_lstnew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:12:02 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/16 14:27:14 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmdlist	*cmd_lstnew(t_minishell *ms, t_cmdlist *cmd);
t_redlist	*red_lstnew(t_minishell *ms, t_redlist *red);
t_envlist	*env_lstnew(t_minishell *ms, t_envlist *env);
t_heredoc	*heredoc_lstnew(t_minishell *ms, t_heredoc *heredoc);

t_execlist	*exec_lstnew(t_minishell *ms, t_mslist *list, size_t num)
{
	t_execlist	*new;
	size_t		j;

	new = (t_execlist *)malloc(sizeof(t_execlist));
	new->cmdline = (char **)ft_calloc(sizeof (char *), num + 1);
	if (!new || !new->cmdline)
		return (NULL);
	j = 0;
	while (j < num && list->str)
	{
		new->cmdline[j] = ft_strdup(list->str);
		list = list->next;
		j++;
	}
	new->cmdtype = NO_CMD;
	new->redtype = NO_REDIRECT;
	new->std_fd = STD_OUT;
	new->err_fd = STD_ERR;
	new->cmd = cmd_lstnew(ms, new->cmd);
	new->red = red_lstnew(ms, new->red);
	new->env = env_lstnew(ms, new->env);
	new->heredoc = heredoc_lstnew(ms, new->heredoc);
	new->next = NULL;
	return (new);
}

t_cmdlist	*cmd_lstnew(t_minishell *ms, t_cmdlist *cmd)
{
	cmd = (t_cmdlist *)malloc(sizeof(t_cmdlist));
	if (!cmd)
		exit_error (ms, "malloc");
	cmd->str = NULL;
	cmd->quote = NO_QUOTE;
	cmd->next = NULL;
	return (cmd);
}

t_redlist	*red_lstnew(t_minishell *ms, t_redlist *red)
{
	red = (t_redlist *)malloc(sizeof(t_redlist));
	if (!red)
		exit_error (ms, "malloc");
	red->str = NULL;
	red->quote = NO_QUOTE;
	red->next = NULL;
	return (red);
}

t_envlist	*env_lstnew(t_minishell *ms, t_envlist *env)
{
	env = (t_envlist *)malloc(sizeof(t_envlist));
	if (!env)
		exit_error (ms, "malloc");
	env->key = NULL;
	env->value = NULL;
	env->next = NULL;
	return (env);
}

t_heredoc	*heredoc_lstnew(t_minishell *ms, t_heredoc *heredoc)
{
	heredoc = malloc(sizeof(t_heredoc));
	if (!heredoc)
		exit_error(ms, "malloc");
	heredoc->docline = NULL;
	heredoc->expand = NULL;
	heredoc->delimiter = NULL;
	heredoc->quote = NO_QUOTE;
	return (heredoc);
}
