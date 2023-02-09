/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 11:16:37 by shimakaori        #+#    #+#             */
/*   Updated: 2023/02/09 13:14:23 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_cmd(t_cmdlist *cmd, t_execlist *exec);
char	*check_env(char *str, t_execlist *exec);

void	expansion(t_minishell *ms)
{
	while (ms->exec)
	{
		while (ms->exec->cmd)
		{
			check_cmd(ms->exec->cmd, ms->exec);
			ms->exec->cmd = ms->exec->cmd->next;
		}
		ms->exec = ms->exec->next;
	}
}

void	check_cmd(t_cmdlist *cmd, t_execlist *exec)
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
	printf("cmd->str = %s", cmd->str);//
	if (*cmd->str == '$' && cmd->quote != S_QUOTE)
		cmd->str = expand_env(cmd->str, exec);
	printf("cmd->str = %s", cmd->str);//
}

char	*expand_env(char *str, t_execlist *exec)
{
	char	*newstr;
	size_t	len;
	size_t	i;

	len = 0;
	i = 1;
	while (str[i] != '\0')
	{
		while (exec->env)
		{
			if (!(ft_strncmp(exec->env->key, \
				cmd->str[i], ft_strlen(exec->env->key))))
			exec->env = exec->env->next;
		}
		i++;
	}
	return (newstr);
}
