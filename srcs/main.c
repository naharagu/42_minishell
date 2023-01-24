/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:53:39 by shimakaori        #+#    #+#             */
/*   Updated: 2023/01/24 09:54:39 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell(t_minishell *ms);
void	lexer(t_minishell *ms);
char	*add_list(char *input, t_mslist	**list);

void	signal_handler(int signum)
{
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_redisplay();
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	*ms;

	ms = init_struct_ms(ms);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	minishell(ms);
	return (0);
}

void	minishell(t_minishell *ms)
{
	char	*line;

	rl_outstream = stderr;
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		ms->input = line;
		lexer(ms);
		//parser(ms);
		free(line);
	}
	exit(ms->exit_status);
}

// void	parser(t_minishell *ms)
// {
// 	size_t		i;

// 	i = 0;
// 	while (i < ms_lstsize(list))
// 	{
// 		printf("str= %s\n", list->str);
// 		list = list->next;
// 		i++;
// 	}
// }

void	lexer(t_minishell *ms)
{
	t_mslist	*tmp;
	char		*start;
	size_t		len;
	size_t		i;//

	while (*ms->input)
	{
		len = 0;
		start = ms->input;
		while (*ms->input && is_quoted(*ms->input, ms))
			ms->input++;
		while (*ms->input && !(is_space(*ms->input)) \
			&& !(is_delimiter(*ms->input)))
			ms->input++;
		len = ms->input - start;
		if (len > 0)
		{
			tmp = ms_lstnew(len, start);
			ms_lstadd_back(&ms->list, tmp);
		}
		if (is_delimiter(*ms->input))
			ms->input = add_list(ms->input, &ms->list);
		ms->input++;
	}
	i = 0;//
	while (i < ms_lstsize(ms->list))//
	{//
		printf("str= %s\n", ms->list->str);//
		ms->list = ms->list->next;//
		i++;//
	}//
}

char	*add_list(char *input, t_mslist	**list)
{
	t_mslist	*tmp;
	char		*start;
	size_t		len;

	len = 0;
	start = input;
	while (is_delimiter(*input))
		input++;
	len = input - start;
	tmp = ms_lstnew(len, start);
	ms_lstadd_back(list, tmp);
	input--;
	return (input);
}
