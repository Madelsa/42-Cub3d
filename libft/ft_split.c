/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 05:34:40 by mahmoud           #+#    #+#             */
/*   Updated: 2023/09/09 15:32:13 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_num_words(char const *s, char c)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			count++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	return (count);
}

static void	free_string(char **str, size_t str_index)
{
	while (str_index > 0)
		free(str[--str_index]);
	free(str);
}

static char	*split_string(const char *s, char c, size_t *start)
{
	size_t	i;
	size_t	j;
	char	*word;
	size_t	k;

	i = *start;
	j = 0;
	while (s[i] == c)
		i++;
	while (s[i + j] && s[i + j] != c)
		j++;
	word = (char *)malloc(sizeof(char) * (j + 1));
	if (word == NULL)
		return (NULL);
	k = 0;
	while (k < j)
	{
		word[k] = s[i + k];
		k++;
	}
	word[j] = '\0';
	*start = i + j;
	return (word);
}

char	**ft_split(const char *s, char c)
{
	size_t	count;
	char	**str;
	size_t	start;
	size_t	i;

	start = 0;
	if (s == NULL)
		return (NULL);
	count = get_num_words(s, c);
	str = (char **)malloc(sizeof(char *) * (count + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < count)
	{
		str[i] = split_string(s, c, &start);
		if (str[i] == NULL)
		{
			free_string(str, i);
			return (NULL);
		}
		i++;
	}
	str[count] = NULL;
	return (str);
}
