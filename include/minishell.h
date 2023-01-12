/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:54:12 by shimakaori        #+#    #+#             */
/*   Updated: 2023/01/12 12:37:01 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <limits.h>
# include <stdbool.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <signal.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <termcap.h> 
# include <readline/readline.h>
# include <readline/history.h>

// # define 

typedef struct s_minishell
{
	int	exit_status;
}	t_minishell;

typedef enum e_quote
{
	S_QUOTE,
	D_QUOTE,
	END_S_QUOTE,
	END_D_QUOTE,
}	t_quote;

typedef enum e_redirection
{
	INPUT,
	OUTPUT,
	HERE_DOC,
	APPEND
}	t_redirection;

typedef enum e_cmd
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
}	t_cmd;

// main.c

#endif
