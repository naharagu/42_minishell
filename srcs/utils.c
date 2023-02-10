/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:16:50 by shimakaori        #+#    #+#             */
/*   Updated: 2023/02/10 16:00:53 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	*init_struct_ms(t_minishell *ms)
{
	ms = malloc(sizeof(t_minishell));
	if (!ms)
		exit(EXIT_FAILURE);
	ms->exit_status = 0;
	ms->input = NULL;
	ms->quote = NO_QUOTE;
	ms->list = NULL;
	ms->exec = NULL;
	return (ms);
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

void	get_pathname(void)
{
	char	*pathname;

	pathname = getcwd(NULL, 0);
	if (!pathname)
		return ;
	else
		printf("%s\n", pathname);
	free(pathname);
}

//a > b | cd >> e だとリストのサイズが８になる
void	print_mslist(t_minishell *ms)
{
	size_t		i;

	i = 0;
	printf("lstsize= %d\n", ms_lstsize(ms->list));
	while (ms->list)
	{
		printf("list[%ld]: %s\n", i, ms->list->str);
		ms->list = ms->list->next;
		i++;
	}
}

//print_mslistの後だと動かない
void	print_execlist(t_minishell *ms)
{
	size_t		i;
	size_t		j;

	printf("execsize= %d\n", exec_lstsize(ms->exec));
	j = 0;
	while (ms->exec)
	{
		i = 0;
		while (ms->exec->cmdline[i] != 0)
		{
			printf("[exec:%ld]cmdline[%ld]= %s\n", j, i, ms->exec->cmdline[i]);
			i++;
		}
		ms->exec = ms->exec->next;
		j++;
	}
}

void	print_cmdredlist(t_minishell *ms)
{
	size_t		i;

	while (ms->exec)
	{
		printf("cmdtype= %d\n", ms->exec->cmdtype);
		printf("redtype= %d\n", ms->exec->redtype);
		i = 0;
		while (ms->exec->cmd)
		{
			printf("cmd[%ld]= %s\n", i, ms->exec->cmd->str);
			ms->exec->cmd = ms->exec->cmd->next;
			i++;
		}
		i = 0;
		while (ms->exec->red)
		{
			printf("red[%ld]= %s\n", i, ms->exec->red->str);
			ms->exec->red = ms->exec->red->next;
			i++;
		}
		ms->exec = ms->exec->next;
	}
}
