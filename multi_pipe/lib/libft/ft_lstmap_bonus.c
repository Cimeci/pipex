/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:02:46 by inowak--          #+#    #+#             */
/*   Updated: 2024/10/23 16:53:59 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*temp;
	void	*verif;

	new_list = NULL;
	temp = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst)
	{
		verif = f(lst->content);
		if (verif)
			temp = ft_lstnew(verif);
		if (!temp || !verif)
		{
			if (verif)
				del(verif);
			ft_lstclear(&new_list, del);
			return (0);
		}
		ft_lstadd_back(&new_list, temp);
		lst = lst->next;
	}
	return (new_list);
}
