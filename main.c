/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 22:47:25 by naharagu          #+#    #+#             */
/*   Updated: 2022/12/31 15:39:14 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_struct_ms(t_minishell *ms)
{
	ms = malloc(sizeof(t_minishell));
	ms->exit_status = 0;
	return ;
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	*ms;

	init_struct_ms(ms);
	return (0);
}
