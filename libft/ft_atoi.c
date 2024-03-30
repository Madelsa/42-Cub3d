/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 14:14:24 by mabdelsa          #+#    #+#             */
/*   Updated: 2023/07/14 14:14:24 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	process_digits(const char *str, int sign, int i)
{
	long	result;
	long	prev;

	result = 0;
	prev = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		prev = result;
		result = result * 10 + str[i++] - '0';
		if (prev > result)
		{
			if (sign < 0)
				return (0);
			else
				return (-1);
		}
	}
	return (result * sign);
}

int	ft_atoi(const char *str)
{
	int		sign;
	int		i;

	if (str == NULL)
		return (0);
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] == '0')
		i++;
	return (process_digits(str, sign, i));
}
