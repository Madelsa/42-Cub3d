/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:23:55 by mahmoud           #+#    #+#             */
/*   Updated: 2023/10/09 12:13:43 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*create_empty_string(void)
{
	char	*str;

	str = (char *)malloc(sizeof(char));
	if (str == NULL)
		return (NULL);
	str[0] = '\0';
	return (str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	begin;
	char	*str;

	i = 0;
	begin = i;
	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return ((char *)s1);
	j = ft_strlen(s1) - 1;
	while (s1[i] != '\0' && ft_strchr(set, s1[i]) != NULL)
		i++;
	if (s1[i] == '\0')
		return (create_empty_string());
	while (ft_strchr(set, s1[j]) != NULL)
		j--;
	str = (char *)malloc((j - i + 2) * sizeof(char));
	if (str == NULL)
		return (str);
	while (i <= j)
		str[begin++] = s1[i++];
	str[begin] = '\0';
	return (str);
}
