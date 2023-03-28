/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 22:04:43 by naharagu          #+#    #+#             */
/*   Updated: 2023/03/28 08:59:30 by naharagu         ###   ########.fr       */
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
	int	status;

	// if (exec->redtype != NO_REDIRECT)
	// t_redirect(exec->red);
	argc = get_args_size(ms->exec);
	argv = create_args_array(ms->exec);
	status = EXIT_SUCCESS;
	if (exec->cmdtype == EXIT_CMD)
		ft_exit(ms, argc, argv);
	else if (exec->cmdtype == ECHO_CMD)
		status = ft_echo(argc, argv);
	else if (exec->cmdtype == CD_CMD)
		status = ft_cd(ms, argc, argv);
	else if (exec->cmdtype == PWD_CMD)
		status = ft_pwd();
	else if (exec->cmdtype == EXPORT_CMD)
		status = ft_export(ms, argc, argv);
	else if (exec->cmdtype == UNSET_CMD)
		status = ft_unset(ms, argc, argv);
	else if (exec->cmdtype == ENV_CMD)
		status = ft_env(ms);
	return (status);
}

int	execute_parent_process(t_minishell *ms)
{
	int		status;

	status = execute_builtin(ms, ms->exec);
	if (ms->exec->redtype != NO_REDIRECT)
		reset_redirect(ms->exec->red);
	return (status);
}