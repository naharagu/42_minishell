/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_argv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 21:17:59 by shimakaori        #+#    #+#             */
/*   Updated: 2023/04/01 07:28:12 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_argv	*init_argv(t_minishell *ms)
{
	t_argv		*argv;

	argv = (t_argv *)malloc (sizeof(t_argv) * 1);
	if (!argv)
		exit_error(ms, "malloc");
	argv->argc = 0;
	argv->argv = NULL;
	return (argv);
}

void	free_argv(t_argv **argv)
{
	int	i;

	if (!argv || !((*argv)->argv))
		return ;
	i = 0;
	while (i < (*argv)->argc)
	{
		if ((*argv)->argv[i])
			free((*argv)->argv[i]);
		i++;
	}
	free((*argv)->argv);
	free(*argv);
}
