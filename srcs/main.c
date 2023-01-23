/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:53:39 by shimakaori        #+#    #+#             */
/*   Updated: 2023/01/23 17:10:16 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell(t_minishell *ms);
void	split_token(t_minishell *ms);
char	*add_list(char *input, t_mslist	**list);

void	signal_handler(int signum)
{
	ft_putchar_fd('\n', STDOUT_FILENO);
	//rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

// void	set_signal_handler(void)
// {
// 	struct sigaction	act;

// 	if (sigemptyset(&act.sa_mask) == -1)
// 		exit (EXIT_FAILURE);
// 	act.sa_flags = 0;
// 	act.sa_handler = signal_handler;
// 	if (sigaction(SIGINT, &act, NULL) == -1)
// 		exit (EXIT_FAILURE);
// 	exit (EXIT_SUCCESS);
// }

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
		//printf("line= %s\n", line);//
		if (*line)
			add_history(line);
		ms->input = line;
		//ms->exit_status = interpret(line);
		split_token(ms);
		free(line);
	}
	exit(ms->exit_status);
}

void	split_token(t_minishell *ms)
{
	t_mslist	*list;
	t_mslist	*tmp;
	char		*start;
	size_t		len;
	size_t		i;//

	list = NULL;
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
			ms_lstadd_back(&list, tmp);
		}
		if (is_delimiter(*ms->input))
			ms->input = add_list(ms->input, &list);
		ms->input++;
	}
	i = 0;//
	while (i < ms_lstsize(list))//
	{//
		printf("str= %s\n", list->str);//
		list = list->next;//
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
