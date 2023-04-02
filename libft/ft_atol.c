/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 06:19:05 by naharagu          #+#    #+#             */
/*   Updated: 2023/04/02 20:59:39 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <errno.h>
#include <limits.h>

long	ft_atol(const char *str)
{
	long	res;
	int		sign;

	res = 0;
	sign = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	while (ft_isdigit(*str))
	{
		if (sign == 1 && (res > ((LONG_MAX - (*str - '0')) * sign) / 10))
		{
			errno = ERANGE;
			return (LONG_MAX);
		}
		else if (sign == -1 && (res < ((LONG_MIN - (*str - '0')) * sign) / 10))
		{
			errno = ERANGE;
			return (LONG_MIN);
		}
		res = res * 10 + ((*str++ - '0') * sign);
	}
	return (res);
}

// #include <stdio.h>
// #include <string.h>

// int	main(int argc, char **argv)
// {
// 	if (argc >= 1)
// 	{
// 		printf("ft_atol: %ld\n", ft_atol(argv[1]));
// 		printf("atol:    %ld\n", atol(argv[1]));
// 		printf("Errorno: %d\n", errno);
// 	}
// 	return (0);
// }
// //9223372036854775808