/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_nums.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 09:49:25 by naharagu          #+#    #+#             */
/*   Updated: 2022/08/03 21:50:46 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

long long	put_int(int n)
{
	long long	i;
	long long	n_ll;

	i = 0;
	n_ll = (long long) n;
	if (n_ll < 0)
	{
		i += write(1, "-", 1);
		n_ll *= -1;
	}
	if (n_ll >= 10)
	{
		i += put_int(n_ll / 10);
		i += put_int(n_ll % 10);
	}
	else
	{
		ft_putchar_fd(n_ll + '0', 1);
		i++;
	}
	return (i);
}

long long	put_u(unsigned int u)
{
	long long	i;

	i = 0;
	if (u >= 10)
	{
		i += put_u(u / 10);
		i += put_u(u % 10);
	}
	else
	{
		ft_putchar_fd(u + '0', 1);
		i++;
	}
	return (i);
}

long long	get_hex_len(long long num)
{
	size_t	len;

	len = 0;
	while (num)
	{
		len++;
		num = num / 16;
	}
	return (len);
}

void	put_x_helper(unsigned int x, char fmt)
{
	if (x >= 16)
	{
		put_x_helper(x / 16, fmt);
		put_x_helper(x % 16, fmt);
	}
	else
	{
		if (x <= 9)
			ft_putchar_fd((x + '0'), 1);
		else
		{
			if (fmt == 'x')
				ft_putchar_fd((x - 10 + 'a'), 1);
			if (fmt == 'X')
				ft_putchar_fd((x - 10 + 'A'), 1);
		}
	}
}

long long	put_x(unsigned int x, char fmt)
{
	if (!x)
		return (write(1, "0", 1));
	put_x_helper(x, fmt);
	return (get_hex_len(x));
}
