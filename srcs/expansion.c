/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 11:16:37 by shimakaori        #+#    #+#             */
/*   Updated: 2023/02/10 11:21:05 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	trim_quote_cmd(t_cmdlist *cmd);
void	expand_env_cmd(t_cmdlist *cmd, t_execlist *exec);
void	trim_quote_red(t_redlist *red);
void	expand_env_red(t_redlist *red, t_execlist *exec);

void	expansion(t_minishell *ms)
{
	ms->exec->env->key = ft_strdup("KEY");//
	ms->exec->env->value = ft_strdup("value");//
	while (ms->exec)
	{
		while (ms->exec->cmd)
		{
			trim_quote_cmd(ms->exec->cmd);
			expand_env_cmd(ms->exec->cmd, ms->exec);
			ms->exec->cmd = ms->exec->cmd->next;
		}
		while (ms->exec->red)
		{
			trim_quote_red(ms->exec->red);
			expand_env_red(ms->exec->red, ms->exec);
			ms->exec->red = ms->exec->red->next;
		}
		ms->exec = ms->exec->next;
	}
	free(ms->exec->env->key);
	free(ms->exec->env->value);
}

void	trim_quote_cmd(t_cmdlist *cmd)
{
	if (*cmd->str == '\'')
	{
		cmd->quote = S_QUOTE;
		cmd->str = ft_strtrim(cmd->str, "\'");
	}
	else if (*cmd->str == '\"')
	{
		cmd->quote = D_QUOTE;
		cmd->str = ft_strtrim(cmd->str, "\"");
	}
	printf("trimedcmdstr = %s", cmd->str);//
}

void	expand_env_cmd(t_cmdlist *cmd, t_execlist *exec)
{
	if (*cmd->str == '$' && cmd->quote != S_QUOTE)
	{
		while (exec->env)
		{
			if (!(ft_strncmp(exec->env->key, &cmd->str[1], \
				ft_strlen(exec->env->key))))
				cmd->str = exec->env->value;
			exec->env = exec->env->next;
		}
	}
	printf("expandedcmdstr = %s", cmd->str);//
}

void	trim_quote_red(t_redlist *red)
{
	if (*red->str == '\'')
	{
		red->quote = S_QUOTE;
		red->str = ft_strtrim(red->str, "\'");
	}
	else if (*red->str == '\"')
	{
		red->quote = D_QUOTE;
		red->str = ft_strtrim(red->str, "\"");
	}
	printf("trimedredstr = %s", red->str);//
}

void	expand_env_red(t_redlist *red, t_execlist *exec)
{
	if (*red->str == '$' && red->quote != S_QUOTE)
	{
		while (exec->env)
		{
			if (!(ft_strncmp(exec->env->key, &red->str[1], \
				ft_strlen(exec->env->key))))
				red->str = exec->env->value;
			exec->env = exec->env->next;
		}
	}
	printf("expandedredstr = %s", red->str);//
}
