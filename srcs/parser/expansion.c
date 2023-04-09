/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 11:16:37 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/09 15:03:23 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_cmd( t_minishell *ms, t_cmdlist *cmd, char *str);
//static int	expand_red(t_minishell *ms, t_redlist *red);
static bool	is_quoted_cmd(t_cmdlist *cmd, char c);

int	expansion(t_minishell *ms)
{
	t_execlist	*tmp_exec;
	t_cmdlist	*tmp_cmd;
	//t_redlist	*tmp_red;

	tmp_exec = ms->exec;
	while (tmp_exec)
	{
		tmp_cmd = tmp_exec->cmd;
		while (tmp_cmd)
		{
			expand_cmd(ms, tmp_cmd, tmp_cmd->str);
			tmp_cmd = tmp_cmd->next;
		}
		// tmp_red = tmp_exec->red;
		// while (tmp_red)
		// {
		// 	if (expand_red(ms, tmp_red) == EXIT_FAILURE)
		// 		return (EXIT_FAILURE);
		// 	tmp_red = tmp_red->next;
		// }
		tmp_exec = tmp_exec->next;
	}
	return (EXIT_SUCCESS);
}

static void	expand_cmd( t_minishell *ms, t_cmdlist *cmd, char *str)
{
	char	*start;
	char	*tmp;
	char	*old;
	char	*new;

	old = NULL;
	while (*str)
	{
		start = str;
		while (*str && is_quoted_cmd(cmd, *str))
			str++;
		if (*str == '$')
			str++;
		while (*str && *str != '$')
			str++;
		tmp = ft_substr(start, 0, str - start);
		start = str;
		printf("1tmp= %s\n", tmp);//
		new = assign_value_cmd (ms, cmd, tmp);
		new = ft_strjoin(old, new);
		old = ft_strdup(new);
		free(tmp);
		free(new);
	}
	free(cmd->str);
	cmd->str = old;
}

// static int	expand_red(t_minishell *ms, t_redlist *red)
// {
// 	char	*original;
// 	char	*copy;
// 	char	*tmp;

// 	original = red->str;
// 	tmp = ft_strdup(red->str);
// 	copy = tmp;
// 	while (*tmp)
// 	{
// 		trim_quote_red(red, *tmp, &original);
// 		tmp++;
// 	}
// 	free(copy);
// 	original = red->str;
// 	assign_value_red (ms, red, &original);
// 	return (error_expandedred(red, original));
// }

// char	*joinstr(t_minishell *ms, char **split, char **tmp)
// {
// 	char	*old;
// 	char	*new;

// 	old = ft_strdup(*tmp);
// 	free(*tmp);
// 	new = expand_env_cmd(ms, ms->exec->cmd,*tmp);
// 	*tmp = ft_strjoin(old, new);
// 	free(old);
// 	free(new);
// 	free(*split);
// 	return (*tmp);
// }

static bool	is_quoted_cmd(t_cmdlist *cmd, char c)
{
	if (c == '\'' && cmd->quote == S_QUOTE)
		cmd->quote = END_S_QUOTE;
	else if (c == '\"' && cmd->quote == D_QUOTE)
		cmd->quote = END_D_QUOTE;
	else if (c == '\'' && (cmd->quote == NO_QUOTE || \
		cmd->quote == END_S_QUOTE || cmd->quote == END_D_QUOTE))
		cmd->quote = S_QUOTE;
	else if (c == '\"' && (cmd->quote == NO_QUOTE || \
		cmd->quote == END_S_QUOTE || cmd->quote == END_D_QUOTE))
		cmd->quote = D_QUOTE;
	else if (c != '\'' && c != '\"' && \
		(cmd->quote == END_S_QUOTE || cmd->quote == END_D_QUOTE))
		cmd->quote = NO_QUOTE;
	if (cmd->quote == S_QUOTE || cmd->quote == D_QUOTE || \
		cmd->quote == END_S_QUOTE || cmd->quote == END_D_QUOTE)
		return (true);
	else
		return (false);
}
