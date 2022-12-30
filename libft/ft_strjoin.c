/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 06:19:05 by naharagu          #+#    #+#             */
/*   Updated: 2022/07/23 09:45:30 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	i;
	size_t	j;

	if (!s1 | !s2)
		return (NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	res = malloc((i + j + 1) * sizeof(char));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1, i + 1);
	ft_strlcpy(res + i, s2, j + 1);
	return (res);
}
