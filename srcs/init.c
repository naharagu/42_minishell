/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:16:50 by shimakaori        #+#    #+#             */
/*   Updated: 2023/01/13 12:25:29 by shimakaori       ###   ########.fr       */
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

t_mslist	*init_mslist(t_mslist *list)
{
	list = malloc(sizeof(t_mslist));
	if (!list)
		exit(EXIT_FAILURE);
	list->str = NULL;
	list->pipe = NO_PIPE;
	list->quote = NO_QUOTE;
	list->redirect = NO_REDIRECT;
	list->cmd = NO_CMD;
	list->next = NULL;
	list->prev = NULL;
	return (list);
}

t_token	*init_token(t_token *token)
{
	token = malloc(sizeof(t_token));
	if (!token)
		exit(EXIT_FAILURE);
	token->num = 1;
	token->split = NULL;
	// printf("%zu\n", token->num);
	// printf("%p\n", &token->num);
	//init_mslist(token->list);
	return (token);
}
