/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 03:41:25 by mahmoud           #+#    #+#             */
/*   Updated: 2023/09/03 08:21:26 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	n_cast;

	n_cast = (long)n;
	if (n_cast < 0)
	{
		ft_putchar_fd('-', fd);
		n_cast = -n_cast;
	}
	if (n_cast > 9)
		ft_putnbr_fd(n_cast / 10, fd);
	ft_putchar_fd((n_cast % 10) + '0', fd);
}
