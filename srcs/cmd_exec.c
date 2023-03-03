/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:55:41 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/03 15:57:52 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//void	my_ls(t_minishell *ms);
//void	free_path_error(t_minishell *ms, char **path, char *str);

void	cmd_exec(t_minishell *ms)
{
	t_execlist	*startexec;
	t_cmdlist	*startcmd;

	startexec = ms->exec;
	while (ms->exec)
	{
		if (ms->exec->cmdtype == ECHO_CMD && ms->exec->cmd->next->str)
			printf("%s\n",ms->exec->cmd->next->str);
		// if (ms->exec->cmdtype == LS_CMD)
		// 	my_ls (ms);//
		if (ms->exec->cmdtype == SPC_CMD)
			other_error(ms, ft_itoa(127), "command not found", 127);
		// startcmd = ms->exec->cmd;
		// while (ms->exec->cmd->str)
		// {
		// 	ms->exec->cmd = ms->exec->cmd->next;
		// }
		// ms->exec->cmd = startcmd;
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
	ft_putendl_fd(buf, 2);
	free(buf);
}

// void	my_ls(t_minishell *ms)
// {
// 	DIR				*dir;
// 	struct dirent	*dp;
// 	char			*path;

// 	errno = 0;
// 	path = ft_strdup(".");
// 	dir = opendir(path);
// 	if (!dir)
// 		free_path_error(ms, &path, "opendir");
// 	while (dp)
// 	{
// 		dp = readdir(dir);
// 		if (!dp && !errno)
// 			break ;
// 		if (!dp && errno)
// 		{
// 			free_path_error(ms, &path, "readdir");
// 			closedir(dir);
// 		}
// 		if (*dp->d_name != '.')
// 			printf("%s\n", dp->d_name);
// 	}
// 	free(path);
// 	if (closedir(dir) < 0)
// 		exit_error(ms, "closedir");
// }

// void	free_path_error(t_minishell *ms, char **path, char *str)
// {
// 	free(path);
// 	exit_error(ms, str);
// }
