/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:01:50 by shimakaori        #+#    #+#             */
/*   Updated: 2023/01/25 15:52:37 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	check_cmd(t_minishell *ms, char *str)
{
	char	*upstr;

	upstr = toupper_char(str);
	//printf("upstr= %s\n", upstr);//
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

void	check_redirect(t_minishell *ms, char *str)
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
}

void	parser(t_minishell *ms)
{
	size_t		i;

	i = 0;
	while (i < ms_lstsize(ms->list))
	{
		check_cmd(ms, ms->list->str);
		check_redirect(ms, ms->list->str);
		printf("str= %s\n", ms->list->str);//
		printf("cmd= %d\n", ms->list->cmd);//
		printf("redirect= %d\n", ms->list->redirect);//
		printf("pipe= %d\n", ms->list->pipe);//
		ms->list = ms->list->next;
		i++;
	}
}
