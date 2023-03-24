/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 22:04:43 by naharagu          #+#    #+#             */
/*   Updated: 2023/03/24 22:04:46 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(t_execlist *exec, size_t argc, char **argv)
{
	extern char	**environ;

	// printf("builtin\n");//
	// printf("cmdtype: %d\n", exec->cmdtype);//
	if (exec->cmdtype == ECHO_CMD)
		return (ft_echo(argc, argv));
	// if (exec->cmdtype == CD_CMD)
	// 	return (ft_cd(argc, argv));
	if (exec->cmdtype == PWD_CMD)
		return (ft_pwd(argc, argv));
	// if (exec->cmdtype == EXPORT_CMD)
	// 	return (ft_export(argc, argv));
	// if (exec->cmdtype == UNSET_CMD)
	// 	return (ft_unset(argc, argv));
	if (exec->cmdtype == ENV_CMD)
		return (ft_env(argc, argv, environ));
	// if (exec->cmdtype == EXIT_CMD)
	// 	ft_exit(ms, argc, argv);
	return (EXIT_FAILURE);
}

int	execute_parent_process(t_minishell *ms)
{
	int		status;
	size_t	argc;
	char	**argv;

	argc = get_args_size(ms->exec);
	argv = create_args_array(ms->exec);
	// printf("before redirect\n");
	if (ms->exec->redtype != NO_REDIRECT)
		set_redirect(ms->exec->red);
	// printf("after redirect\n");
	status = execute_builtin(ms->exec, argc, argv);
	if (ms->exec->redtype != NO_REDIRECT)
		reset_redirect(ms->exec->red);
	return (status);
}
