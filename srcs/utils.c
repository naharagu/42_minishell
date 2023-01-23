/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:16:50 by shimakaori        #+#    #+#             */
/*   Updated: 2023/01/19 14:08:37 by shimakaori       ###   ########.fr       */
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

void	get_pathname(void)
{
	char	*pathname;

	pathname = getcwd(NULL, 0);
	if (!pathname)
		return ;
	else
		printf("%s\n", pathname);
	free(pathname);
}
