/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 22:04:43 by naharagu          #+#    #+#             */
/*   Updated: 2023/04/16 10:03:05 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_builtin_helper(t_minishell *ms, \
			size_t argc, char **argv)
{
	int		status;

	status = EXIT_SUCCESS;
	if (argv == NULL)
		return (EXIT_FAILURE);
	if (ft_strcmp(argv[0], "exit") == 0)
		status = ft_exit(argc, argv);
	else if (ft_strcmp(argv[0], "echo") == 0)
		status = ft_echo(argc, argv);
	else if (ft_strcmp(argv[0], "cd") == 0)
		status = ft_cd(ms, argc, argv);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		status = ft_pwd();
	else if (ft_strcmp(argv[0], "export") == 0)
		status = ft_export(ms, argc, argv);
	else if (ft_strcmp(argv[0], "unset") == 0)
		status = ft_unset(ms, argc, argv);
	else if (ft_strcmp(argv[0], "env") == 0)
		status = ft_env(ms, argc);
	else
	{
		other_error(argv[0], "command not found", NOT_FOUND);
		status = NOT_FOUND;
	}
	return (status);
}

int	execute_builtin(t_minishell *ms, t_execlist *exec)
{
	size_t	argc;
	char	**argv;
	int		status;

	if (exec->redtype != NO_REDIRECT)
		set_redirect(exec->red);
	argc = get_args_size(exec);
	argv = create_args_array(exec);
	status = execute_builtin_helper(ms, argc, argv);
	free_arg_array(argc, argv);
	return (status);
}
