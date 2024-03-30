/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:36:09 by mabdelsa          #+#    #+#             */
/*   Updated: 2023/09/10 12:51:49 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check(char c, va_list args)
{
	if (c == 'c')
		return (ft_put_char(va_arg(args, int)));
	else if (c == 's')
		return (ft_put_string(va_arg(args, char *)));
	else if (c == 'p')
		return (ft_put_hex_pointer(va_arg(args, size_t)));
	else if (c == 'd' || c == 'i')
		return (ft_putnbr(va_arg(args, int)));
	else if (c == 'u')
		return (ft_putnbr_unsigned(va_arg(args, int)));
	else if (c == 'x')
		return (ft_put_hex_uint_lower(va_arg(args, unsigned int)));
	else if (c == 'X')
		return (ft_put_hex_uint_upper(va_arg(args, unsigned int)));
	else if (c == '%')
		return (ft_put_char('%'));
	else
		return (ft_put_char(c));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list			args;
	unsigned int	i;
	unsigned int	count;

	va_start(args, str);
	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%')
			count += check(str[++i], args);
		else
		{
			write(1, &str[i], 1);
			count++;
		}
		i++;
	}
	va_end(args);
	return (count);
}
