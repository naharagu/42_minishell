/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 06:19:05 by naharagu          #+#    #+#             */
/*   Updated: 2023/04/01 09:52:22by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
#include <stdbool.h>

long ft_strtol(const char *str, char **endptr, int base)
{
	long res;
	int	sign;

	if (base < 2 || base > 36)
	{
		if (endptr)
			*endptr = (char *)str;
		return 0;
	}
	res = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	while (ft_isdigit(*str))
	{
		if (sign == 1 && (res > ((LONG_MAX - (*str - '0')) * sign) / 10))
			return ((int)LONG_MAX);
		else if (sign == -1 && (res < ((LONG_MIN - (*str - '0')) * sign) / 10))
			return ((int)LONG_MIN);
		res = res * 10 + ((*str++ - '0') * sign);
	}
	return (res);
}
