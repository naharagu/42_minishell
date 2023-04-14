/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:25:11 by naharagu          #+#    #+#             */
/*   Updated: 2023/04/14 14:32:24 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_pipe(t_execlist *exec)
{
	if (exec->next == NULL)
		return ;
	pipe(exec->pipe_out);
	exec->next->pipe_in[0] = exec->pipe_out[0];
	exec->next->pipe_in[1] = exec->pipe_out[1];
}

void	setup_child_pipe(t_execlist *exec)
{
	safe_close(exec->pipe_out[0]);
	dup2(exec->pipe_in[0], STDIN_FILENO);
	if (exec->pipe_in[0] != STDIN_FILENO)
		safe_close(exec->pipe_in[0]);
	dup2(exec->pipe_out[1], STDOUT_FILENO);
	if (exec->pipe_out[1] != STDOUT_FILENO)
		safe_close(exec->pipe_out[1]);
}

void	setup_parent_pipe(t_execlist *exec)
{
	if (exec->pipe_in[0] != STDIN_FILENO)
		safe_close(exec->pipe_in[0]);
	if (exec->next)
		safe_close(exec->pipe_out[1]);
}
