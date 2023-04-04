/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:16:50 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/04 15:25:33 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_status;

void	init_ms(t_minishell *ms)
{
	g_status = 0;
	ms->cmd_size = 0;
	ms->line = NULL;
	ms->quote = NO_QUOTE;
	ms->list = NULL;
	ms->exec = NULL;
	ms->env = NULL;
	ms->argv = init_argv(ms);
	return ;
}

char	*toupper_char(char *str)
{
	char	*tmp;
	char	*start;

	tmp = ft_strdup(str);
	start = tmp;
	while (*tmp != '\0')
	{
		*tmp = ft_toupper(*tmp);
		tmp++;
	}
	return (start);
}

void	check_pipe(t_minishell *ms, char *str)
{
	if (!(ft_strncmp("|", str, ft_strlen(str))))
		ms->list->pipe = PIPE;
	else if (!(ft_strncmp(";", str, ft_strlen(str))))
		ms->list->pipe = SEMICOLON;
}

void	clear_ms(t_minishell *ms)
{
	ms->line = NULL;
	ms->quote = NO_QUOTE;
	ms_lstclear(&ms->list);
	exec_lstclear(&ms->exec);
	free_argv(&ms->argv);
}

char	*ms_strtrim(char const *s1, char c)
{
	char	**split;
	char	*result;
	char	*tmp;
	size_t	i;

	if (!s1 || !c)
		return (NULL);
	i = 0;
	tmp = NULL;
	split = ft_split(s1, c);
	while (split[i] && split[i][0] != '\0')
	{
		if (!tmp)
			tmp = ft_strdup(split[i]);
		else
			tmp = ft_strjoin(tmp, split[i]);
		free(split[i]);
		i++;
	}
	free(split);
	result = ft_strdup(tmp);
	free (tmp);
	return (result);
}
