/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:16:50 by shimakaori        #+#    #+#             */
/*   Updated: 2023/01/12 13:17:04 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	init_struct_ms(t_minishell *ms)
{
	ms = malloc(sizeof(t_minishell));
	if (!ms)
		exit(EXIT_FAILURE);
	ms->exit_status = 0;
	return ;
}
