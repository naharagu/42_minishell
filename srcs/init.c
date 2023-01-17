/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:16:50 by shimakaori        #+#    #+#             */
/*   Updated: 2023/01/16 12:10:22 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	*init_struct_ms(t_minishell *ms)
{
	ms = malloc(sizeof(t_minishell));
	if (!ms)
		exit(EXIT_FAILURE);
	ms->exit_status = 0;
	ms->input = NULL;
	ms->quote = NO_QUOTE;
	return (ms);
}

t_mslist	*init_mslist(t_mslist *list)
{
	list = malloc(sizeof(t_mslist));
	if (!list)
		exit(EXIT_FAILURE);
	list->str = NULL;
	list->pipe = NO_PIPE;
	list->redirect = NO_REDIRECT;
	list->cmd = NO_CMD;
	list->next = NULL;
	list->prev = NULL;
	return (list);
}
