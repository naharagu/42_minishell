/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:55:41 by shimakaori        #+#    #+#             */
/*   Updated: 2023/02/28 11:08:14 by shimakaori       ###   ########.fr       */
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
		exit_error(ms, "closedir");
}

void	free_path_error(t_minishell *ms, char **path, char *str)
{
	free(path);
	exit_error(ms, str);
}
