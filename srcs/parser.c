/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:01:50 by shimakaori        #+#    #+#             */
/*   Updated: 2023/02/08 13:07:33 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		check_pipe(t_minishell *ms, char *str);
void		check_execlist(t_minishell *ms);
t_cmdlist	*check_cmd(t_cmdlist *cmd, char *str);
void		check_red(t_minishell *ms, char *str);

void	parser(t_minishell *ms)
{
	t_mslist	*start;
	t_execlist	*tmp;
	size_t		num;

	start = ms->list;
	num = 0;
	//printf("listsize= %d\n", ms_lstsize(ms->list));//
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

	i = 0;
	//printf("execsize= %d\n", exec_lstsize(ms->exec));//
	while (ms->exec)
	{
		j = 0;
		while (ms->exec->cmdline[j] != 0)
		{
			printf("[exec:%ld]cmdline[%ld]= %s\n", i, j, ms->exec->cmdline[j]);//
			ms->exec->cmd = check_cmd(ms->exec->cmd, ms->exec->cmdline[j]);
			//check_red(ms, ms->exec->cmdline[j]);
			printf("cmdtype= %d\n", ms->exec->cmd->cmdtype);//
			//printf("redtype= %d\n", ms->exec->red->redtype);//
			j++;
		}
		ms->exec = ms->exec->next;
		i++;
	}
}

t_cmdlist	*check_cmd(t_cmdlist *cmd, char *str)
{
	char	*upstr;

	upstr = toupper_char(str);
	if (!(ft_strncmp("ECHO", upstr, ft_strlen("ECHO"))))
		cmd->cmdtype = ECHO_CMD;
	else if (!(ft_strncmp("CD", upstr, ft_strlen("CD"))))
		cmd->cmdtype = CD_CMD;
	else if (!(ft_strncmp("PWD", upstr, ft_strlen("PWD"))))
		cmd->cmdtype = PWD_CMD;
	else if (!(ft_strncmp("EXPORT", upstr, ft_strlen("EXPORT"))))
		cmd->cmdtype = EXPORT_CMD;
	else if (!(ft_strncmp("UNSET", upstr, ft_strlen("UNSET"))))
		cmd->cmdtype = UNSET_CMD;
	else if (!(ft_strncmp("ENV", upstr, ft_strlen("ENV"))))
		cmd->cmdtype = ENV_CMD;
	else if (!(ft_strncmp("EXIT", upstr, ft_strlen("EXIT"))))
		cmd->cmdtype = EXIT_CMD;
	free(upstr);
	if (cmd->cmdtype != NO_CMD)
	{
		cmd->str = str;
		printf("cmdstr= %s\n", cmd->str);//
		//cmd = cmd->next;
	}
	return (cmd);
}

void	check_red(t_minishell *ms, char *str)
{
	if (!(ft_strncmp("<", str, ft_strlen("<"))))
		ms->exec->red->redtype = INPUT;
	else if (!(ft_strncmp(">", str, ft_strlen(">"))))
		ms->exec->red->redtype = OUTPUT;
	else if (!(ft_strncmp("<<", str, ft_strlen("<<"))))
		ms->exec->red->redtype = HERE_DOC;
	else if (!(ft_strncmp(">>", str, ft_strlen(">>"))))
		ms->exec->red->redtype = APPEND;
	// if (ms->exec->red->redtype != NO_REDIRECT)
	// {
	// 	ms->exec->red->str = str;
	// 	printf("redstr= %s\n", ms->exec->red->str);//
	// 	ms->exec->red = ms->exec->red->next;
	// }	
}
