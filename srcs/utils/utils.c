/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:16:50 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/10 17:01:44 by shimakaori       ###   ########.fr       */
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

// void	check_pipe(t_minishell *ms, char *str)
// {
// 	if (!(ft_strncmp("|", str, ft_strlen(str))))
// 		ms->list->pipe = PIPE;
// 	else if (!(ft_strncmp(";", str, ft_strlen(str))))
// 		ms->list->pipe = SEMICOLON;
// }

void	clear_ms(t_minishell *ms)
{
	ms->line = NULL;
	ms->quote = NO_QUOTE;
	ms_lstclear(&ms->list);
	exec_lstclear(&ms->exec);
}
