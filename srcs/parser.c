/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:01:50 by shimakaori        #+#    #+#             */
/*   Updated: 2023/02/10 16:54:55 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_execlist(t_minishell *ms);
void	check_cmd(t_minishell *ms, char *str);
void	check_red(t_minishell *ms, char *str);
void	copy_cmd_red_list(t_minishell *ms, char *str, size_t i);

void	parser(t_minishell *ms)
{
	t_mslist	*start;
	t_execlist	*tmp;
	size_t		num;

	start = ms->list;
	num = 0;
	while (ms->list)
	{
		check_pipe(ms, ms->list->str);
		if (ms->list->pipe != NO_PIPE)
		{
			tmp = exec_lstnew(ms, start, num);
			exec_lstadd_back(&ms->exec, tmp);
			start = ms->list->next;
			num = 0;
		}
		else
			num++;
		ms->list = ms->list->next;
	}
	tmp = exec_lstnew(ms, start, num);
	exec_lstadd_back(&ms->exec, tmp);
	check_execlist(ms);
}

void	check_execlist(t_minishell *ms)
{
	t_execlist	*start;
	size_t		i;

	start = ms->exec;
	while (ms->exec)
	{
		i = 0;
		while (ms->exec->cmdline[i] != 0)
		{
			check_cmd(ms, ms->exec->cmdline[i]);
			check_red(ms, ms->exec->cmdline[i]);
			copy_cmd_red_list(ms, ms->exec->cmdline[i], i);
			i++;
		}
		ms->exec = ms->exec->next;
	}
	ms->exec = start;
}

void	check_cmd(t_minishell *ms, char *str)
{
	char	*upstr;

	upstr = toupper_char(str);
	if (!(ft_strncmp("ECHO", upstr, ft_strlen("ECHO"))))
		ms->exec->cmdtype = ECHO_CMD;
	else if (!(ft_strncmp("CD", upstr, ft_strlen("CD"))))
		ms->exec->cmdtype = CD_CMD;
	else if (!(ft_strncmp("PWD", upstr, ft_strlen("PWD"))))
		ms->exec->cmdtype = PWD_CMD;
	else if (!(ft_strncmp("EXPORT", upstr, ft_strlen("EXPORT"))))
		ms->exec->cmdtype = EXPORT_CMD;
	else if (!(ft_strncmp("UNSET", upstr, ft_strlen("UNSET"))))
		ms->exec->cmdtype = UNSET_CMD;
	else if (!(ft_strncmp("ENV", upstr, ft_strlen("ENV"))))
		ms->exec->cmdtype = ENV_CMD;
	else if (!(ft_strncmp("EXIT", upstr, ft_strlen("EXIT"))))
		ms->exec->cmdtype = EXIT_CMD;
	free(upstr);
}

void	check_red(t_minishell *ms, char *str)
{
	if (!(ft_strncmp("<", str, ft_strlen("<"))))
		ms->exec->redtype = INPUT;
	else if (!(ft_strncmp(">", str, ft_strlen(">"))))
		ms->exec->redtype = OUTPUT;
	else if (!(ft_strncmp("<<", str, ft_strlen("<<"))))
		ms->exec->redtype = HERE_DOC;
	else if (!(ft_strncmp(">>", str, ft_strlen(">>"))))
		ms->exec->redtype = APPEND;
}

void	copy_cmd_red_list(t_minishell *ms, char *str, size_t i)
{
	t_cmdlist	*startcmd;
	t_redlist	*startred;

	printf("cmdtype= %d\n", ms->exec->cmdtype);//
	printf("redtype= %d\n", ms->exec->redtype);//
	startcmd = ms->exec->cmd;
	startred = ms->exec->red;
	if (ms->exec->redtype == NO_REDIRECT)
	{
		ms->exec->cmd->str = str;
		printf("cmd[%ld]= %s\n", i,  ms->exec->cmd->str);//
		ms->exec->cmd->next = cmd_lstnew(ms->exec->cmd->next);
		ms->exec->cmd = ms->exec->cmd->next;
	}
	else if (ms->exec->redtype != NO_REDIRECT)
	{
		ms->exec->red->str = str;
		printf("red[%ld]= %s\n", i, ms->exec->red->str);//
		ms->exec->red->next = red_lstnew(ms->exec->red->next);
		ms->exec->red = ms->exec->red->next;
	}
	ms->exec->cmd = startcmd;
	ms->exec->red = startred;
	printf("startcmd= %s\n", ms->exec->cmd->str);//
	printf("startred= %s\n", ms->exec->red->str);//
	//startがズレてる
}
