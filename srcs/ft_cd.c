/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:54:26 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/20 16:35:33 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_minishell *ms, char *newdir)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		exit_error(ms, "getcwd");
	if (chdir(newdir) < 0)
		other_error(ms, "cd", ft_strjoin(newdir, \
		": No such file or directory"), 1);
	cwd = getcwd(NULL, 0);
}
