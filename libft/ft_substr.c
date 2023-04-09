/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 06:19:05 by naharagu          #+#    #+#             */
/*   Updated: 2023/04/09 11:52:52 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*res;

	res = ft_calloc((len + 1), sizeof(char));
	if (!s || !res)
		return (NULL);
	if ((size_t)start >= ft_strlen(s) || !(ft_strlcpy(res, s + start, len + 1)))
		res[0] = '\0';
	return (res);
}
