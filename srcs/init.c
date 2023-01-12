/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:16:50 by shimakaori        #+#    #+#             */
/*   Updated: 2023/01/12 13:39:11 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_struct_ms(t_minishell *ms)
{
	ms = malloc(sizeof(t_minishell));
	if (!ms)
		exit(EXIT_FAILURE);
	ms->exit_status = 0;
	return ;
}

void	init_mslist(t_mslist *list)
{
	list = malloc(sizeof(t_mslist));
	if (!list)
		exit(EXIT_FAILURE);
	list->str = NULL;
	list->quote = NO_QUOTE;
	list->redirect = NO_REDIRECT;
	list->cmd = NO_CMD;
	init_mslist(list->next);
	init_mslist(list->prev);
}

void	init_token(t_token *token)
{
	token = malloc(sizeof(t_token));
	if (!token)
		exit(EXIT_FAILURE);
	token->pipe = NO_PIPE;
	token->num = 0;
	init_mslist(token->list);
}
