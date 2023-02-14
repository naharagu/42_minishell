/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 11:16:37 by shimakaori        #+#    #+#             */
/*   Updated: 2023/02/14 14:36:50 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_cmd(char *str, t_cmdlist *cmd, t_execlist *exec);
void	expand_red(char *str, t_redlist *red, t_execlist *exec);

void	expansion(t_minishell *ms)
{
	t_execlist	*startexec;
	t_cmdlist	*startcmd;
	t_redlist	*startred;

	startexec = ms->exec;
	while (ms->exec)
	{
		ms->exec->env->key = ft_strdup("KEY");//
		ms->exec->env->value = ft_strdup("hoge fuga");//
		startcmd = ms->exec->cmd;
		startred = ms->exec->red;
		while (ms->exec->cmd->next)
		{
			expand_cmd(ms->exec->cmd->str, ms->exec->cmd, ms->exec);
			ms->exec->cmd = ms->exec->cmd->next;
		}
		while (ms->exec->red->next)
		{
			expand_red(ms->exec->red->str, ms->exec->red, ms->exec);
			ms->exec->red = ms->exec->red->next;
		}
		ms->exec->cmd = startcmd;
		ms->exec->red = startred;
		ms->exec = ms->exec->next;
	}
	ms->exec = startexec;
	free(ms->exec->env->key);//
	free(ms->exec->env->value);//
}

void	expand_cmd(char *str, t_cmdlist *cmd, t_execlist *exec)
{
	t_envlist	*startenv;
	char		**split;
	size_t		i;

	startenv = exec->env;
	i = 0;
	if (*str == '\'')
		cmd->quote = S_QUOTE;
	else if (*str == '\"')
		cmd->quote = D_QUOTE;
	if (cmd->quote == S_QUOTE || cmd->quote == D_QUOTE)
		str = ft_strtrim(str, "\'\"");
	if (*str == '$' && cmd->quote != S_QUOTE)
	{
		str++;
		while (exec->env)
		{
			if (!(ft_strncmp(exec->env->key, str, ft_strlen(exec->env->key))))
			{
				if (cmd->quote == D_QUOTE)
					cmd->str = exec->env->value;
				else
				{
					split = ft_split(exec->env->value, ' ');
					while (split[i])
					{
						cmd->str = split[i];
						cmd->next = cmd_lstnew(cmd->next);
						cmd = cmd->next;
						i++;
					}
				}
			}
			exec->env = exec->env->next;
		}
	}
	else
		cmd->str = str;
	exec->env = startenv;
}

void	expand_red(char *str, t_redlist *red, t_execlist *exec)
{
	t_envlist			*startenv;

	startenv = exec->env;
	if (*str == '\'')
		red->quote = S_QUOTE;
	else if (*str == '\"')
		red->quote = D_QUOTE;
	if (red->quote == S_QUOTE || red->quote == D_QUOTE)
		str = ft_strtrim(str, "\'\"");
	if (*str == '$' && red->quote != S_QUOTE)
	{
		str++;
		while (exec->env)
		{
			if (!(ft_strncmp(exec->env->key, str, ft_strlen(exec->env->key))))
				red->str = exec->env->value;
			exec->env = exec->env->next;
		}
	}
	else
		red->str = str;
	exec->env = startenv;
}
