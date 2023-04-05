/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:16:50 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/04 22:08:26 by shimakaori       ###   ########.fr       */
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
	char	*result;
	char	*start;

	result = ft_strdup(str);
	start = result;
	while (*result != '\0')
	{
		*result = ft_toupper(*result);
		result++;
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

void	ms_strtrim(t_cmdlist *cmd, char c, char **original)
{
	char	**split;
	char	*tmp;
	char	*old;
	size_t	i;

	i = 1;
	split = ft_split(cmd->str, c);
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
