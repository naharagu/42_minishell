/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:55:41 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/14 15:37:23 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_exec(t_minishell *ms)
{
	t_execlist	*startexec;
	t_cmdlist	*startcmd;
	int			argc;
	char		**argv;
	size_t		i;

	argc = 0;
	startexec = ms->exec;
	while (ms->exec)
	{
		i = 0;
		startcmd = ms->exec->cmd;
		if (ms->exec->cmdtype == ECHO_CMD && ms->exec->cmd->next->str)
			printf("%s\n", ms->exec->cmd->next->str);
		if (ms->exec->cmdtype == SPC_CMD)
			other_error(ms, ft_itoa(ms->exit_status), "command not found", 1);
		if (ms->exec->cmdtype == EXIT_CMD)
		{
			argc = cmd_lstsize(ms->exec->cmd);
			argv = ft_calloc(sizeof(char *), argc);
			while (ms->exec->cmd)
			{
				argv[i] = ms->exec->cmd->str;
				ms->exec->cmd = ms->exec->cmd->next;
				i++;
			}
			ft_exit (ms, argc, argv);
			free (argv);
		}
		ms->exec->cmd = startcmd;
		ms->exec = ms->exec->next;
	}
	ms->exec = startexec;
}

void	exec_command(t_execlist	*exec)
{
	char	*str1;
	char	*str2;

	str1 = ft_strdup("test1");
	str2 = ft_strdup("test2");
	ft_putnbr_fd(exec->std_fd, 1);
	ft_putchar_fd(':', 1);
	ft_putendl_fd(str1, 1);
	ft_putnbr_fd(exec->err_fd, 2);
	ft_putchar_fd(':', 2);
	ft_putendl_fd(str2, 2);
	free(str1);
	free(str2);
}

void	read_fd(t_minishell *ms, int fd)
{
	ssize_t		filesize;
	char		*buf;
	int			len;

	filesize = 1;
	len = 100;
	buf = ft_calloc(sizeof(char), (len + 1));
	if (!buf)
		exit_error(ms, "calloc");
	while (filesize != 0)
	{
		filesize = read(fd, buf, len);
		if (filesize == -1)
			free(buf);
	}
	ft_putendl_fd("", 2);
	ft_putendl_fd(buf, 2);
	free(buf);
}
