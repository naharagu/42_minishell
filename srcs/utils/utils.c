/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:16:50 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/12 21:46:43 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (!result)
		exit_error("malloc");
	start = result;
	while (*result != '\0')
	{
		*result = ft_toupper(*result);
		result++;
	}
	return (start);
}

void	clear_ms(t_minishell *ms)
{
	ms->line = NULL;
	ms->quote = NO_QUOTE;
	ms_lstclear(&ms->list);
	exec_lstclear(&ms->exec);
}

char	*get_errchar(size_t count_in, size_t count_out)
{
	if (count_in > 3 && count_out > 0)
		return ("<>");
	else if (count_in > 3)
		return ("<");
	else if (count_out > 3 || (count_in > 1 && count_out > 1))
		return (">>");
	else if (count_out > 2 || (count_in > 1 && count_out > 0))
		return (">");
	return (NULL);
}
