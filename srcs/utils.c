/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:16:50 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/16 12:33:00 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	*init_struct_ms(void)
{
	t_minishell	*ms;

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

void	free_execlist(t_execlist *tmp)
{
	tmp->cmdtype = NO_CMD;
	tmp->redtype = NO_REDIRECT;
	tmp->std_fd = STD_OUT;
	tmp->err_fd = STD_ERR;
	if (tmp->cmdline)
		free(tmp->cmdline);
	if (tmp->cmd)
		free(tmp->cmd);
	if (tmp->red)
		free(tmp->red);
	if (tmp->env)
		free(tmp->env);
	if (tmp->heredoc)
		free(tmp->heredoc);
	if (tmp)
		free(tmp);
}
