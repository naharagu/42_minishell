/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:54:26 by shimakaori        #+#    #+#             */
/*   Updated: 2023/03/26 17:51:00 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_minishell *ms, char *newdir)
{
	char	*cwd;

	if (!newdir)
		return (EXIT_FAILURE);
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		exit_error(ms, "getcwd");
		return (EXIT_FAILURE);
	}
	if (chdir(newdir) < 0)
	{
		other_error(ms, "cd", ft_strjoin(newdir, \
		": No such file or directory"), 1);
		return (EXIT_FAILURE);
	}
	cwd = getcwd(NULL, 0);
	return (EXIT_SUCCESS);
}
