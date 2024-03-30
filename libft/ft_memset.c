/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:41:21 by mabdelsa          #+#    #+#             */
/*   Updated: 2023/07/04 12:41:21 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int value, size_t len)
{
	size_t	i;

	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		((unsigned char *)str)[i] = (unsigned char)value;
		i++;
	}
	return (str);
}
