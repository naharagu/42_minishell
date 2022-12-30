/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 06:19:05 by naharagu          #+#    #+#             */
/*   Updated: 2022/07/10 18:44:09 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}

static size_t	ft_intlen(int n)
{
	size_t	len;

	if (n < 0)
		len = 1;
	else
		len = 0;
	while (1)
	{
		++len;
		if (!(n / 10))
			break ;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		neg;
	int		i;
	int		cnt;
	char	*buf;

	if (n < 0)
		neg = 1;
	else
		neg = 0;
	i = neg - 1;
	cnt = (int)ft_intlen(n);
	buf = (char *)ft_calloc(cnt + 1, sizeof(char));
	if (!buf)
		return (NULL);
	if (neg)
		buf[0] = '-';
	while (++i < cnt)
	{
		buf[cnt - (!neg) - i] = "0123456789"[ft_abs(n % 10)];
		n /= 10;
	}
	buf[cnt] = '\0';
	return (buf);
}
