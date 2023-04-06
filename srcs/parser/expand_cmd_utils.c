/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:36:16 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/06 19:56:02 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_status;
static void	ms_strtrim_cmd(t_cmdlist *cmd, char c, char **original);
static char	**make_split_cmd(t_cmdlist *cmd, char c, char **original);


void	trim_quote_cmd(t_cmdlist *cmd, char c, char **original)
{
	if (c == '\'' && cmd->quote == NO_QUOTE)
	{
		cmd->quote = S_QUOTE;
		ms_strtrim_cmd(cmd, '\'', original);
	}
	else if (c == '\"' && cmd->quote == NO_QUOTE)
	{
		cmd->quote = D_QUOTE;
		ms_strtrim_cmd(cmd, '\"', original);
	}
}

void	assign_value_cmd(t_minishell *ms, t_cmdlist *cmd, char **original)
{
	char	**split;
	char	*tmp;
	size_t	i;

	i = 1;
	split = NULL;
	tmp = NULL;
	if (ft_strnstr(cmd->str, "$", ft_strlen(cmd->str)) \
		&& cmd->quote != S_QUOTE)
		split = make_split_cmd(cmd, '$', original);
	if (!split || !split[0])
		return ;
	tmp = expand_env(ms, split[0]);
	free(split[0]);
	while (split[i] && split[i][0] != '\0')
	{
		tmp = joinstr(ms, &split[i], &tmp);
		i++;
	}
	free(*original);
	cmd->str = ft_strdup(tmp);
	free(tmp);
	free(split);
}

static void	ms_strtrim_cmd(t_cmdlist *cmd, char c, char **original)
{
	char	**split;
	char	*tmp;
	char	*old;
	size_t	i;

	i = 1;
	split = make_split_cmd(cmd, c, original);
	if (!split)
		return ;
	tmp = split[0];
	while (split[i] && split[i][0] != '\0')
	{
		old = ft_strdup(tmp);
		free(tmp);
		tmp = ft_strjoin(old, split[i]);
		free(old);
		free(split[i]);
		i++;
	}
	free(*original);
	cmd->str = ft_strdup(tmp);
	free(tmp);
	free(split);
}

static char	**make_split_cmd(t_cmdlist *cmd, char c, char **original)
{
	char	**split;

	split = ft_split(cmd->str, c);
	if (!split || !split[0])
	{
		free(*original);
		cmd->str = NULL;
		return (NULL);
	}
	return (split);
}
