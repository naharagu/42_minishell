/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:16:50 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/04 15:12:41 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	*init_struct_ms(t_minishell *ms)
{
	ms = malloc(sizeof(t_minishell));
	if (!ms)
		exit_error(ms, "malloc");
	ms->exit_status = 0;
	ms->startline = NULL;
	ms->line = NULL;
	ms->quote = NO_QUOTE;
	ms->list = NULL;
	ms->exec = NULL;
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

void	all_free(t_minishell *ms)
{
	ms->quote = NO_QUOTE;
	if (ms->startline)
		free(ms->startline);
	if (ms->list)
		ms_lstclear(&ms->list);
	if (ms->exec)
		exec_lstclear(&ms->exec);
}

// void	get_pathname(void)
// {
// 	char	*pathname;

// 	pathname = getcwd(NULL, 0);
// 	if (!pathname)
// 		return ;
// 	else
// 		printf("%s\n", pathname);
// 	free(pathname);
// }
