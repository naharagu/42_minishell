/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:36:16 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/17 16:08:22 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*assign_value_cmd(t_minishell *ms, t_cmdlist *cmd, char *tmp);
static char	*expand_env_cmd(t_minishell *ms, t_cmdlist *cmd, char *str);
static char	*get_newstr_cmd(t_minishell *ms, t_cmdlist *cmd, char *str);

void	expand_cmd( t_minishell *ms, t_cmdlist *cmd, char *str)
{
	char	*start;
	char	*tmp;
	char	*old;
	char	*new;

	old = NULL;
	while (*str)
	{
		start = str;
		if (*str && *str == '$')
			str++;
		while (*str && is_quoted_cmd(cmd, *str))
			str++;
		if (*str && *str == '$')
			str++;
		while (*str && *str != '$' && *str != '\'' && *str != '\"')
			str++;
		tmp = ft_substr(start, 0, str - start);
		// printf("1tmp= %s\n", tmp);//")
		new = assign_value_cmd (ms, cmd, tmp);
		free (tmp);
		old = get_old(&new, &old);
	}
	free(cmd->str);
	cmd->str = old;
}

static char	*assign_value_cmd(t_minishell *ms, t_cmdlist *cmd, char *tmp)
{
	char	*new;
	char	*trim;
	char	*str;

	new = NULL;
	trim = NULL;
	str = tmp;
	if (!(ft_strncmp("\"\"", str, ft_strlen(str))) \
		|| !(ft_strncmp("\'\'", str, ft_strlen(str))))
		return (ft_strdup(""));
	if (ft_strnstr(str, "$", ft_strlen(str)) && (*str == '\'' || *str == '\"'))
	{
		trim = trim_quote(str, *str);
		if (cmd->quote == END_S_QUOTE)
			return (trim);
		new = expand_env_cmd(ms, cmd, trim);
		free (trim);
	}
	else if (ft_strnstr(str, "$", ft_strlen(str)))
		new = expand_env_cmd(ms, cmd, str);
	else if (*str == '\'' || *str == '\"')
		new = trim_quote(str, *str);
	else
		new = ft_strdup(str);
	return (new);
}

static char	*expand_env_cmd(t_minishell *ms, t_cmdlist *cmd, char *str)
{
	char		*start;
	char		*tmp;
	char		*old;
	char		*new;

	old = NULL;
	while (*str)
	{
		start = str;
		str += split_str(str);
		tmp = ft_substr(start, 0, str - start);
		// printf("2tmp= %s\n", tmp);//")
		new = get_newstr_cmd(ms, cmd, tmp);
		// printf("new= %s\n", new);//")
		free(tmp);
		old = get_old(&new, &old);
	}
	return (old);
}

static char	*get_newstr_cmd(t_minishell *ms, t_cmdlist *cmd, char *str)
{

	if (*str == '$' && ft_strlen(str) > 1)
	{
		str++;
		if (*str == '\'' || *str == '\"')
			return (trim_quote(str, *str));
		else if (cmd->quote != END_S_QUOTE)
			return (get_env(ms, str));
	}
	return (ft_strdup(str));
}
