/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:39:14 by mabdelsa          #+#    #+#             */
/*   Updated: 2023/09/05 15:23:05 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*node;
	t_list	*new_node;
	t_list	*current;
	void	*function_applied;

	if (!lst || !del)
		return (NULL);
	node = NULL;
	current = lst;
	while (current)
	{
		function_applied = f(current->content);
		new_node = ft_lstnew(function_applied);
		if (!new_node)
		{
			del(function_applied);
			ft_lstclear(&node, del);
			return (NULL);
		}
		ft_lstadd_back(&node, new_node);
		current = current->next;
	}
	return (node);
}
