/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 11:09:51 by naharagu          #+#    #+#             */
/*   Updated: 2022/08/03 21:51:14 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <limits.h>

int			ft_printf(const char *fmt, ...);
long long	convert_put(va_list *ap, const char fmt, long long res);
long long	put_c(int c);
long long	put_s(char *s);
long long	put_p(uintptr_t p);
long long	put_int(int n);
long long	put_u(unsigned int u);
long long	put_x(unsigned int x, char fmt);

#endif