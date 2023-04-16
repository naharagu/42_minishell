/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_red_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:38:12 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/16 09:50:16 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_status;
static void	set_redstr(t_redlist *red, char **old);
static char	*assign_value_red(t_minishell *ms, t_redlist *red, char *tmp);
static char	*expand_env_red(t_minishell *ms, t_redlist *red, char *str);
static char	*get_newstr_red(t_minishell *ms, t_redlist *red, char *str);

int	expand_red(t_minishell *ms, t_redlist *red, char *str)
{
	char	*original;
	char	*start;
	char	*tmp;
	char	*old;
	char	*new;

	original = str;
	old = NULL;
	while (*str)
	{
		start = str;
		while (*str && *str != '$' && *str != '\'' && *str != '\"')
			str++;
		while (*str == '$')
			str++;
		while (*str && is_quoted_red(red, *str))
			str++;
		tmp = ft_substr(start, 0, str - start);
		start = str;
		new = assign_value_red (ms, red, tmp);
		free (tmp);
		old = get_old(&new, &old);
	}
	set_redstr(red, &old);
	return (error_expandedred(red, original));
}

static void	set_redstr(t_redlist *red, char **old)
{
	free(red->str);
	red->str = *old;
}

static char	*assign_value_red(t_minishell *ms, t_redlist *red, char *tmp)
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
		if (red->quote == END_S_QUOTE)
			return (trim);
		new = expand_env_red(ms, red, trim);
		free (trim);
	}
	else if (ft_strnstr(str, "$", ft_strlen(str)))
		new = expand_env_red(ms, red, str);
	else if (*str == '\'' || *str == '\"')
		new = trim_quote(str, *str);
	else
		new = ft_strdup(str);
	return (new);
}

static char	*expand_env_red(t_minishell *ms, t_redlist *red, char *str)
{
	char		*start;
	char		*tmp;
	char		*old;
	char		*new;

	old = NULL;
	while (*str)
	{
		start = str;
		if (*str == '$' || is_space(*str))
			str++;
		if (*str && (*str == '\'' || *str == '\"'))
			str += quotedstr(str);
		while (*str && *str != '$' && !is_space(*str) \
			&& *str != '\'' && *str != '\"')
			str++;
		tmp = ft_substr(start, 0, str - start);
		start = str;
		new = get_newstr_red(ms, red, tmp);
		free(tmp);
		old = get_old(&new, &old);
	}
	return (old);
}

static char	*get_newstr_red(t_minishell *ms, t_redlist *red, char *str)
{
	char	*new;
	char	*trim;

	if (is_space(*str) || (*str == '$' && ft_strlen(str) == 1))
		return (ft_strdup(str));
	else if (*str == '$' && ft_strlen(str) > 1)
		str++;
	if ((*str == '\'' || *str == '\"') && ft_strnstr(str, "$", ft_strlen(str)))
	{
		trim = trim_quote(str, *str);
		if (red->quote == END_S_QUOTE)
			return (trim);
		new = get_env(ms, trim);
		free (trim);
		return (new);
	}
	else if (*str == '$' && ft_strlen(str) > 1)
	{
		str++;
		if (*str == '\'' || *str == '\"')
			return (trim_quote(str, *str));
		else if (red->quote != END_S_QUOTE)
			return (get_env(ms, str));
	}
	return (ft_strdup(str));
}
