/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:56:59 by mabdelsa          #+#    #+#             */
/*   Updated: 2023/09/10 12:52:18 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_put_hex_uint_lower(unsigned int i)
{
	char			*base;
	unsigned int	count;

	base = "0123456789abcdef";
	count = 0;
	if (i > 15)
	{
		count += ft_put_hex_uint_lower(i / 16);
		count += ft_put_hex_uint_lower(i % 16);
	}
	else
		count += ft_put_char(base[i]);
	return (count);
}

unsigned int	ft_put_hex_uint_upper(unsigned int i)
{
	char			*base;
	unsigned int	count;

	base = "0123456789ABCDEF";
	count = 0;
	if (i > 15)
	{
		count += ft_put_hex_uint_upper(i / 16);
		count += ft_put_hex_uint_upper(i % 16);
	}
	else
		count += ft_put_char(base[i]);
	return (count);
}

unsigned int	ft_put_hex_pointer_recursive(size_t ptr)
{
	char			*base;
	unsigned int	count;

	base = "0123456789abcdef";
	count = 0;
	if (ptr > 15)
	{
		count += ft_put_hex_pointer_recursive(ptr / 16);
		count += ft_put_hex_pointer_recursive(ptr % 16);
	}
	else
		count += ft_put_char(base[ptr]);
	return (count);
}

unsigned int	ft_put_hex_pointer(size_t ptr)
{
	unsigned int	count;

	count = 0;
	if (ptr == 0)
	{
		write(1, "0x0", 3);
		return (3);
	}
	write(1, "0x", 2);
	count += 2;
	count += ft_put_hex_pointer_recursive(ptr);
	return (count);
}
