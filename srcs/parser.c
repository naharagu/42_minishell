/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:01:50 by shimakaori        #+#    #+#             */
/*   Updated: 2023/02/13 17:41:44 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_execlist(t_minishell *ms);
void	check_cmd_red(t_minishell *ms, char *str);
void	copy_cmd_red_list(t_minishell *ms, char *str);

void	add_execlist(t_minishell *ms, t_mslist	*first, size_t num)
{
	t_execlist	*tmp;

	tmp = exec_lstnew(ms, first, num);
	exec_lstadd_back(&ms->exec, tmp);
}

void	parser(t_minishell *ms)
{
	t_mslist	*start;
	t_mslist	*first;
	size_t		num;

	start = ms->list;
	first = ms->list;
	num = 0;
	while (ms->list)
	{
		check_pipe(ms, ms->list->str);
		if (ms->list->pipe != NO_PIPE)
		{
			add_execlist(ms, first, num);
			first = ms->list->next;
			num = 0;
		}
		else
			num++;
		ms->list = ms->list->next;
	}
	ms->list = start;
	add_execlist(ms, first, num);
	check_execlist(ms);
	error_parser(ms);
}

void	check_execlist(t_minishell *ms)
{
	t_execlist	*startexec;
	t_cmdlist	*startcmd;
	t_redlist	*startred;
	size_t		i;

	startexec = ms->exec;
	while (ms->exec)
	{
		startcmd = ms->exec->cmd;
		startred = ms->exec->red;
		i = 0;
		while (ms->exec->cmdline[i])
		{
			check_cmd_red(ms, toupper_char(ms->exec->cmdline[i]));
			free(toupper_char(ms->exec->cmdline[i]));
			copy_cmd_red_list(ms, ms->exec->cmdline[i]);
			i++;
		}
		ms->exec->cmd = startcmd;
		ms->exec->red = startred;
		// if (red_lstsize(ms->exec->red) < 2)
		// 	error_exit("newline", SYNTAX);
		ms->exec = ms->exec->next;
	}
	ms->exec = startexec;
}

void	check_cmd_red(t_minishell *ms, char *str)
{
	if (!(ft_strncmp("ECHO", str, ft_strlen("ECHO"))))
		ms->exec->cmdtype = ECHO_CMD;
	else if (!(ft_strncmp("CD", str, ft_strlen("CD"))))
		ms->exec->cmdtype = CD_CMD;
	else if (!(ft_strncmp("PWD", str, ft_strlen("PWD"))))
		ms->exec->cmdtype = PWD_CMD;
	else if (!(ft_strncmp("EXPORT", str, ft_strlen("EXPORT"))))
		ms->exec->cmdtype = EXPORT_CMD;
	else if (!(ft_strncmp("UNSET", str, ft_strlen("UNSET"))))
		ms->exec->cmdtype = UNSET_CMD;
	else if (!(ft_strncmp("ENV", str, ft_strlen("ENV"))))
		ms->exec->cmdtype = ENV_CMD;
	else if (!(ft_strncmp("EXIT", str, ft_strlen("EXIT"))))
		ms->exec->cmdtype = EXIT_CMD;
	else if (!(ft_strncmp("<", str, ft_strlen("<"))))
		ms->exec->redtype = INPUT;
	else if (!(ft_strncmp(">", str, ft_strlen(">"))))
		ms->exec->redtype = OUTPUT;
	else if (!(ft_strncmp("<<", str, ft_strlen("<<"))))
		ms->exec->redtype = HERE_DOC;
	else if (!(ft_strncmp(">>", str, ft_strlen(">>"))))
		ms->exec->redtype = APPEND;
}

void	copy_cmd_red_list(t_minishell *ms, char *str)
{
	if (ms->exec->redtype == NO_REDIRECT)
	{
		ms->exec->cmd->str = str;
		ms->exec->cmd->next = cmd_lstnew(ms->exec->cmd->next);
		ms->exec->cmd = ms->exec->cmd->next;
	}
	else if (ms->exec->redtype != NO_REDIRECT)
	{
		ms->exec->red->str = str;
		ms->exec->red->next = red_lstnew(ms->exec->red->next);
		ms->exec->red = ms->exec->red->next;
	}
}
