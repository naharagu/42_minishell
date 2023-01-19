/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:53:39 by shimakaori        #+#    #+#             */
/*   Updated: 2023/01/19 13:45:52 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell(t_minishell *ms);
void	split_token(t_minishell *ms);
char	*add_list(char *input, t_mslist	**list);

int	main(int argc, char **argv, char **env)
{
	t_minishell	*ms;

	ms = init_struct_ms(ms);
	minishell(ms);
	return (0);
}

void	minishell(t_minishell *ms)
{
	while (1)
	{
		ms->input = readline("minishell$>");
		printf("input= %s\n", ms->input);//
		add_history(ms->input);
		split_token(ms);
		//free(ms->input);
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
