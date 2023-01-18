/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:53:39 by shimakaori        #+#    #+#             */
/*   Updated: 2023/01/18 13:47:29 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell(t_minishell *ms);
void	split_token(t_minishell *ms);

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
		add_history(ms->input);
		//printf("%s\n", ms->input);//
		split_token(ms);
		//free(ms->input);
	}
	exit(ms->exit_status);
}

void	split_token(t_minishell *ms)
{
	t_mslist	*list;
	t_mslist	*tmp;
	size_t		len;
	char		*str;
	size_t		i;

	list = NULL;
	while (*ms->input)
	{
		len = 0;
		str = ft_strdup(ms->input);
		while (*ms->input && is_quoted(*ms->input, ms))
		{
			ms->input++;
			len++;
		}
		while (*ms->input && !(is_space(*ms->input)) \
			&& !(is_delimiter(*ms->input)))
		{
			ms->input++;
			len++;
		}
		//printf("c= %c\n", *ms->input);//
		//printf("len= %zu\n", len);//
		if (len > 0)
		{
			tmp = ms_lstnew(len, str);
			ms_lstadd_back(&list, tmp);
		}
		if (is_delimiter(*ms->input))
		{
			tmp = ms_lstnew(1, ms->input);
			ms_lstadd_back(&list, tmp);
		}
		ms->input++;
		free(str);
	}
	i = 0;//
	while (i < ms_lstsize(list))//
	{//
		printf("str= %s\n", list->str);//
		list = list->next;//
		i++;//
	}//
}
