/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 22:04:43 by naharagu          #+#    #+#             */
/*   Updated: 2023/03/27 23:56:46 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(t_minishell *ms, t_execlist *exec)
{
	// printf("\x1b[32mbuiltin"); //
	// printf("\x1b[39m\n"); //
	// printf("cmdtype: %d\n", exec->cmdtype);//
	size_t argc;
	char **argv;

	argc = get_args_size(ms->exec);
	argv = create_args_array(ms->exec);
	if (exec->cmdtype == ECHO_CMD)
		return (ft_echo(argc, argv));
	if (exec->cmdtype == CD_CMD)
		return (ft_cd(ms, argc, argv));
	if (exec->cmdtype == PWD_CMD)
		return (ft_pwd());
	if (exec->cmdtype == EXPORT_CMD)
		return (ft_export(ms, argc, argv));
	if (exec->cmdtype == UNSET_CMD)
		return (ft_unset(ms, argc, argv));
	if (exec->cmdtype == ENV_CMD)
		return (ft_env(ms));
	if (exec->cmdtype == EXIT_CMD)
		ft_exit(ms, argc, argv);
	return (EXIT_FAILURE);
}

int	execute_parent_process(t_minishell *ms)
{
	int		status;

	// printf("before redirect\n");
	if (ms->exec->redtype != NO_REDIRECT)
		set_redirect(ms->exec->red);
	// printf("after redirect\n");
	status = execute_builtin(ms, ms->exec);
	if (ms->exec->redtype != NO_REDIRECT)
		reset_redirect(ms->exec->red);
	return (status);
}
