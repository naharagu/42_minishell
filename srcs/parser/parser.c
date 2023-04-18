/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:01:50 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/18 21:59:17 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_execlist(t_minishell *ms);
static int	copy_cmd_red_list(t_minishell *ms, t_execlist *exec);

int	parser(t_minishell *ms)
{
	t_mslist	*tmplist;
	t_mslist	*first;

	tmplist = ms->list;
	while (tmplist)
	{
		ms->cmd_size = 0;
		first = tmplist;
		while (tmplist->str && (ft_strncmp("|", tmplist->str,
					ft_strlen(tmplist->str))))
		{
			if (!tmplist->next)
			{
				ms->cmd_size++;
				break ;
			}
			tmplist = tmplist->next;
			ms->cmd_size++;
		}
		add_execlist(ms, first, ms->cmd_size);
		tmplist = tmplist->next;
	}
	if (errror_parser_mslist(ms) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (check_execlist(ms));
}

static int	check_execlist(t_minishell *ms)
{
	t_execlist	*tmp_exec;
	size_t		i;

	tmp_exec = ms->exec;
	while (tmp_exec)
	{
		i = 0;
		while (tmp_exec->cmdline[i])
		{
			check_redtype(ms, tmp_exec->cmdline[i]);
			check_cmdtype(ms, tmp_exec->cmdline[i]);
			if (error_redirect(tmp_exec, tmp_exec->cmdline[i]) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			i++;
		}
		if (copy_cmd_red_list(ms, tmp_exec) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		tmp_exec = tmp_exec->next;
	}
	return (EXIT_SUCCESS);
}

static int	copy_cmd_red_list(t_minishell *ms, t_execlist *exec)
{
	size_t	i;

	i = 0;
	while (exec->cmdline[i])
	{
		if (ft_strnstr(exec->cmdline[i], ">", ft_strlen(exec->cmdline[i])) \
			|| ft_strnstr(exec->cmdline[i], "<", ft_strlen(exec->cmdline[i])))
		{
			add_redlist(ms, exec->cmdline[i]);
			i++;
			if (exec->cmdline[i])
			{
				add_redlist(ms, exec->cmdline[i]);
				if (is_metachara(exec->cmdline[i][0]))
					return (syntax_error(exec->cmdline[i], 258));
			}
			else
				return (syntax_error("newline", 258));
		}
		else
			add_cmdlist(ms, exec->cmdline[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
