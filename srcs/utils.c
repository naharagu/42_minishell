/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:16:50 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/20 13:28:02 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	*init_ms(void)
{
	t_minishell	*ms;

	ms = malloc(sizeof(t_minishell));
	if (!ms)
		exit_error(ms, "malloc");
	ms->exit_status = 0;
	ms->line = NULL;
	ms->quote = NO_QUOTE;
	ms->list = NULL;
	ms->exec = NULL;
	ms->argv = init_argv(ms);
	return (ms);
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
