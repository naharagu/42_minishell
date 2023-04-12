/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:24:24 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/12 10:23:22 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_cmdtype(t_minishell *ms, char *str)
{
	size_t	len;
	char	*upchar;

	len = ft_strlen(str);
	upchar = toupper_char(str);
	if (len == 4 && !(ft_strncmp("ECHO", upchar, len)))
		ms->exec->cmdtype = ECHO_CMD;
	else if (len == 2 && !(ft_strncmp("CD", upchar, len)))
		ms->exec->cmdtype = CD_CMD;
	else if (len == 3 && !(ft_strncmp("PWD", upchar, len)))
		ms->exec->cmdtype = PWD_CMD;
	else if (len == 6 && !(ft_strncmp("EXPORT", upchar, len)))
		ms->exec->cmdtype = EXPORT_CMD;
	else if (len == 5 && !(ft_strncmp("UNSET", upchar, len)))
		ms->exec->cmdtype = UNSET_CMD;
	else if (len == 3 && !(ft_strncmp("ENV", upchar, len)))
		ms->exec->cmdtype = ENV_CMD;
	else if (len == 4 && !(ft_strncmp("EXIT", upchar, len)))
		ms->exec->cmdtype = EXIT_CMD;
	free(upchar);
}

void	check_redtype(t_minishell *ms, char *str)
{
	if (*str != '\'' && *str != '\"')
	{
		if (ft_strnstr(str, ">>", ft_strlen(str)))
			ms->exec->redtype = APPEND;
		else if (ft_strnstr(str, ">", ft_strlen(str)) \
			&& ms->exec->redtype != APPEND)
			ms->exec->redtype = OUTPUT;
		else if (ft_strnstr(str, "<<", ft_strlen(str)))
			ms->exec->redtype = HERE_DOC;
		else if (ft_strnstr(str, "<", ft_strlen(str)) \
			&& ms->exec->redtype != HERE_DOC)
			ms->exec->redtype = INPUT;
	}
}
