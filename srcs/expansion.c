/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 11:16:37 by shimakaori        #+#    #+#             */
/*   Updated: 2023/02/13 14:23:36 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	trim_quote_cmd(char *str, t_cmdlist *cmd);
void	expand_env_cmd(char *str, t_cmdlist *cmd, t_execlist *exec);
void	trim_quote_red(char *str, t_redlist *red);
void	expand_env_red(char *str, t_redlist *red, t_execlist *exec);

// void	init_start(t_minishell *ms, t_start *start)
// {
// 	t_execlist	*exec;
// 	t_cmdlist	*cmd;
// 	t_redlist	*red;

// 	start->startexec = exec_lstnew(ms, NULL, 0);
// 	start->startcmd = cmd_lstnew(cmd);
// 	start->startred = red_lstnew(red);
// }

void	expansion(t_minishell *ms)
{
	t_execlist	*startexec;
	t_cmdlist	*startcmd;
	t_redlist	*startred;
	//t_start		*start;

	//init_start(ms, start);
	startexec = ms->exec;
	while (ms->exec)
	{
		ms->exec->env->key = ft_strdup("KEY");//
		ms->exec->env->value = ft_strdup("value");//
		startcmd = ms->exec->cmd;
		startred = ms->exec->red;
		while (ms->exec->cmd->next)
		{
			trim_quote_cmd(ms->exec->cmd->str, ms->exec->cmd);
			expand_env_cmd(ms->exec->cmd->str, ms->exec->cmd, ms->exec);
			ms->exec->cmd = ms->exec->cmd->next;
		}
		while (ms->exec->red->next)
		{
			trim_quote_red(ms->exec->red->str, ms->exec->red);
			expand_env_red(ms->exec->red->str, ms->exec->red, ms->exec);
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

void	trim_quote_cmd(char *str, t_cmdlist *cmd)
{
	if (*str == '\'')
	{
		cmd->quote = S_QUOTE;
		cmd->str = ft_strtrim(str, "\'");
	}
	else if (*str == '\"')
	{
		cmd->quote = D_QUOTE;
		cmd->str = ft_strtrim(str, "\"");
	}
}

void	expand_env_cmd(char *str, t_cmdlist *cmd, t_execlist *exec)
{
	t_envlist			*startenv;

	startenv = exec->env;
	if (*str == '$' && cmd->quote != S_QUOTE)
	{
		str++;
		while (exec->env->next)
		{
			if (!(ft_strncmp(exec->env->key, str, ft_strlen(exec->env->key))))
				cmd->str = exec->env->value;
			exec->env = exec->env->next;
		}
	}
	exec->env = startenv;
}

void	trim_quote_red(char *str, t_redlist *red)
{
	if (*str == '\'')
	{
		red->quote = S_QUOTE;
		red->str = ft_strtrim(str, "\'");
	}
	else if (*str == '\"')
	{
		red->quote = D_QUOTE;
		red->str = ft_strtrim(str, "\"");
	}
}

void	expand_env_red(char *str, t_redlist *red, t_execlist *exec)
{
	t_envlist			*startenv;

	startenv = exec->env;
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
	exec->env = startenv;
}
