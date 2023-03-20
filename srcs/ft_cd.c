/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:54:26 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/20 16:07:14 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_minishell *ms, char *newdir)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		exit_error(ms, "getcwd");
	printf("oldcwd= %s\n", cwd);//
	if (chdir(newdir) < 0)
		exit_error(ms, "chdir");
	cwd = getcwd(NULL, 0);
	printf("newcwd= %s\n", cwd);//
}
