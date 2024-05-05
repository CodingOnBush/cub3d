/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 07:56:42 by momrane           #+#    #+#             */
/*   Updated: 2024/01/22 09:39:58 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

char	*ft_get_after_nl(char *str)
{
	char	*pos;
	char	*out;
	int		len;
	int		i;

	if (!str)
		return (NULL);
	pos = ft_strchr(str, '\n');
	if (!pos || *(pos + 1) == '\0')
		return (NULL);
	len = 0;
	while (*(pos + 1 + len) != '\0')
		len++;
	out = (char *)malloc((len + 1) * sizeof(char));
	if (!out)
		return (NULL);
	i = 0;
	while (i < len)
	{
		out[i] = *(pos + 1 + i);
		i++;
	}
	out[i] = '\0';
	return (out);
}

int	ft_get_len(t_node *lst)
{
	t_node	*curr;
	char	*str;
	int		len;

	curr = lst;
	len = 0;
	while (curr)
	{
		str = curr->str;
		while (*str != '\n' && *str)
		{
			len++;
			str++;
		}
		if (*str == '\n')
			return (len + 1);
		curr = curr->next;
	}
	return (len);
}

void	ft_lstappend(t_node **lst, char *buff)
{
	t_node	*new;
	t_node	*curr;

	new = (t_node *)malloc(sizeof(t_node));
	if (!new)
		return ;
	new->str = buff;
	new->next = NULL;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	curr = *lst;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = new;
}

int	ft_lstchr(t_node *lst)
{
	t_node	*curr;
	char	*str;

	curr = lst;
	while (curr)
	{
		str = curr->str;
		if (ft_strchr(str, '\n') != NULL)
			return (1);
		curr = curr->next;
	}
	return (0);
}
