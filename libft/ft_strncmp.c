/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 16:13:20 by naharagu          #+#    #+#             */
/*   Updated: 2023/03/04 21:32:54 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	diff;

	while (n--)
	{
		diff = *(unsigned char *)s1++ - *(unsigned char *)s2++;
		if (diff)
			return (diff);
		if (!*s1)
			break ;
	}
	return (0);
}
