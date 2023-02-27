/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:55:41 by shimakaori        #+#    #+#             */
/*   Updated: 2023/02/27 23:51:29 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_ls(t_minishell *ms);
void	free_path_error(t_minishell *ms, char **path, char *str);

void	cmd_exec(t_minishell *ms)
{
	t_execlist	*startexec;
	t_cmdlist	*startcmd;

	startexec = ms->exec;
	while (ms->exec)
	{
		// if (ms->exec->cmdtype == LS_CMD)
		// 	my_ls (ms);//
		if (ms->exec->cmdtype == SPC_CMD)
		{
			ms->err_msg = ft_substr("command not found");
			ms->err_location = ft_strdup(ft_itoa(ms->exit_status));
			print_error(ms, OTHER_ERR);
		}
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

//使わないかも
void	my_ls(t_minishell *ms)
{
	DIR				*dir;
	struct dirent	*dp;
	char			*path;

	errno = 0;
	path = ft_strdup(".");
	dir = opendir(path);
	if (!dir)
		free_path_error(ms, &path, "opendir");
	while (dp)
	{
		dp = readdir(dir);
		if (!dp && !errno)
			break ;
		if (!dp && errno)
		{
			free_path_error(ms, &path, "readdir");
			closedir(dir);
		}
		if (*dp->d_name != '.')
			printf("%s\n", dp->d_name);
	}
	free(path);
	if (closedir(dir) < 0)
		print_error(ms, "closedir", EXIT_ERR);
}

void	free_path_error(t_minishell *ms, char **path, char *str)
{
	free(path);
	print_error(ms, str, EXIT_ERR);
}
