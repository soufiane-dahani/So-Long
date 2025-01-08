/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:10:38 by sodahani          #+#    #+#             */
/*   Updated: 2025/01/08 12:32:27 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_lstadd_back(list **alst, list *new)
{
	list	*last;

	if (!*alst)
	{
		*alst = new;
		return ;
	}
	last = ft_lstlast(*alst);
	last->next = new;
}
list	*ft_lstnew(void *content, t_list **head)
{
	list	*elem;

	elem = ft_malloc(head, sizeof(list));
	if (!elem)
		return (NULL);
	elem->content = content;
	elem->next = NULL;
	return (elem);
}
int	ft_lstsize(list *lst)
{
	list	*tmp;
	int		i;

	tmp = lst;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}
char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (0);
}
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest && !src && n > 0)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}
char	*ft_strdupm(const char *s1, t_list **head)
{
	size_t	size;
	char	*dest;

	size = ft_strlen(s1);
	dest = (char *)ft_malloc( head ,sizeof(char) * (size + 1));
	if (dest == NULL)
		return (0);
	ft_memcpy(dest, s1, size);
	dest[size] = '\0';
	return (dest);
}
