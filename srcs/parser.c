/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:01:50 by shimakaori        #+#    #+#             */
/*   Updated: 2023/02/07 15:29:31 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_cmd(t_minishell *ms, char *str);
char	*toupper_char(char *str);
void	check_metachara(t_minishell *ms, char *str);

void	parser(t_minishell *ms)
{
	t_mslist	*start;
	t_execlist	*tmp;
	size_t		num;

	start = ms->list;
	num = 0;
	//printf("size= %d\n", ms_lstsize(ms->list));//
	while (ms->list)
	{
		check_cmd(ms, ms->list->str);
		check_metachara(ms, ms->list->str);
		//printf("str= %s\n", ms->list->str);//
		if (ms->list->pipe != NO_PIPE)
		{
			//printf("start= %s\n", start->str);//
			//printf("num= %zu\n", num);//
			tmp = exec_lstnew(ms, start, num);
			exec_lstadd_back(&ms->exec, tmp);
			start = ms->list->next;
			num = 0;
		}
		else
			num++;
		ms->list = ms->list->next;
	}
	//printf("start= %s\n", start->str);//
	//printf("num= %zu\n", num);//
	tmp = exec_lstnew(ms, start, num);
	exec_lstadd_back(&ms->exec, tmp);
}

void	check_cmd(t_minishell *ms, char *str)
{
	char	*upstr;

	upstr = toupper_char(str);
	if (!(ft_strncmp("ECHO", upstr, ft_strlen(str))))
		ms->list->cmd = ECHO_CMD;
	else if (!(ft_strncmp("CD", upstr, ft_strlen(str))))
		ms->list->cmd = CD_CMD;
	else if (!(ft_strncmp("PWD", upstr, ft_strlen(str))))
		ms->list->cmd = PWD_CMD;
	else if (!(ft_strncmp("EXPORT", upstr, ft_strlen(str))))
		ms->list->cmd = EXPORT_CMD;
	else if (!(ft_strncmp("UNSET", upstr, ft_strlen(str))))
		ms->list->cmd = UNSET_CMD;
	else if (!(ft_strncmp("ENV", upstr, ft_strlen(str))))
		ms->list->cmd = ENV_CMD;
	else if (!(ft_strncmp("EXIT", upstr, ft_strlen(str))))
		ms->list->cmd = EXIT_CMD;
	free(upstr);
}

char	*toupper_char(char *str)
{
	char	*tmp;
	char	*start;

	tmp = ft_strdup(str);
	start = tmp;
	while (*tmp != '\0')
	{
		*tmp = ft_toupper(*tmp);
		tmp++;
	}
	return (start);
}

void	check_metachara(t_minishell *ms, char *str)
{
	if (!(ft_strncmp("<", str, ft_strlen(str))))
		ms->list->redirect = INPUT;
	else if (!(ft_strncmp(">", str, ft_strlen(str))))
		ms->list->redirect = OUTPUT;
	else if (!(ft_strncmp("<<", str, ft_strlen(str))))
		ms->list->redirect = HERE_DOC;
	else if (!(ft_strncmp(">>", str, ft_strlen(str))))
		ms->list->redirect = APPEND;
	else if (!(ft_strncmp("|", str, ft_strlen(str))))
		ms->list->pipe = PIPE;
	else if (!(ft_strncmp(";", str, ft_strlen(str))))
		ms->list->pipe = SEMICOLON;
}
