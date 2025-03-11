/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarieux <mlarieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:41:08 by mlarieux          #+#    #+#             */
/*   Updated: 2025/03/11 12:41:10 by mlarieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

void	ft_lstdelone(t_list **lst, t_list *node)
{
	t_list	*node_ptr;
	t_list	*prev;

	node_ptr = *lst;
	prev = *lst;
	while (node_ptr && node_ptr != node)
	{
		prev = node_ptr;
		node_ptr = node_ptr->next;
	}
	if (node_ptr == *lst)
		*lst = node->next;
	if (node_ptr == node)
		prev->next = node_ptr->next;
	free (node);
}
