/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimakaori <shimakaori@student.42tokyo.jp> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 16:13:20 by naharagu          #+#    #+#             */
/*   Updated: 2023/04/04 15:22:49 by shimakaori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char		*addr;
	size_t		len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	addr = (char *)ft_calloc((len + 1), sizeof(char));
	if (!addr)
		return (NULL);
	ft_memcpy(addr, s, len);
	return (addr);
}
