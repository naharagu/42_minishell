/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 23:20:33 by naharagu          #+#    #+#             */
/*   Updated: 2022/07/17 08:32:43 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	dst_len;

	if (!dstsize)
		return (ft_strlen(src));
	src_len = ft_strlen(src);
	dst_len = ft_strlen(dest);
	if (dst_len > dstsize)
		src_len += dstsize;
	else
	{
		src_len += dst_len;
		ft_strlcpy(dest + dst_len, src, dstsize - dst_len);
	}
	return (src_len);
}
