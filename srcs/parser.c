/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:01:50 by shimakaori        #+#    #+#             */
/*   Updated: 2023/02/10 12:56:33 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_pipe(t_minishell *ms, char *str);
void	check_execlist(t_minishell *ms);
void	check_cmd(t_minishell *ms, char *str);
void	check_red(t_minishell *ms, char *str);

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
			printf ("tmp=%s", tmp->cmdline[0]);//
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

void	check_pipe(t_minishell *ms, char *str)
{
	if (!(ft_strncmp("|", str, ft_strlen(str))))
		ms->list->pipe = PIPE;
	else if (!(ft_strncmp(";", str, ft_strlen(str))))
		ms->list->pipe = SEMICOLON;
}

void	check_execlist(t_minishell *ms)
{
	size_t		i;
	size_t		j;

	j = 0;
	printf("execsize= %d\n", exec_lstsize(ms->exec));//
	while (ms->exec)
	{
		i = 0;
		while (ms->exec->cmdline[i] != 0)
		{
			printf("[exec:%ld]cmdline[%ld]= %s\n", j, i, ms->exec->cmdline[j]);//
			check_cmd(ms, ms->exec->cmdline[i]);
			check_red(ms, ms->exec->cmdline[i]);
			if (ms->exec->redtype == NO_REDIRECT)
			{
				ms->exec->cmd->str = ms->exec->cmdline[i];
				ms->exec->cmd->next = cmd_lstnew(ms->exec->cmd->next);
				ms->exec->cmd = ms->exec->cmd->next;
			}
			else if (ms->exec->redtype != NO_REDIRECT)
			{
				ms->exec->red->str = ms->exec->cmdline[i];
				ms->exec->red->next = red_lstnew(ms->exec->red->next);
				ms->exec->red = ms->exec->red->next;
			}
			i++;
		}
		ms->exec = ms->exec->next;
		j++;
	}
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
