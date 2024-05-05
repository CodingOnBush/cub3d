/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 07:52:08 by momrane           #+#    #+#             */
/*   Updated: 2024/01/18 20:35:59 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	ft_update_lst(t_node **lst)
{
	t_node	*current;
	char	*new;

	if (*lst == NULL)
		return ;
	current = *lst;
	while (current->next != NULL)
		current = current->next;
	new = ft_get_after_nl(current->str);
	if (new == NULL)
	{
		ft_freelst(lst);
		return ;
	}
	ft_freelst(lst);
	ft_lstappend(lst, new);
}

int	ft_createlst(int fd, t_node **lst)
{
	char	*buff;
	int		s;

	buff = NULL;
	s = 0;
	while (ft_lstchr(*lst) == 0)
	{
		buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buff)
			return (-1);
		s = read(fd, buff, BUFFER_SIZE);
		if (s <= 0)
		{
			free(buff);
			return (s);
		}
		buff[s] = '\0';
		ft_lstappend(lst, buff);
	}
	return (s);
}

void	*ft_freelst(t_node **lst)
{
	t_node	*current;
	t_node	*next;

	if (*lst == NULL)
		return (NULL);
	current = *lst;
	while (current != NULL)
	{
		next = current->next;
		free(current->str);
		free(current);
		current = next;
	}
	*lst = NULL;
	return (NULL);
}

char	*ft_create_str(t_node *lst)
{
	t_node	*current;
	char	*new;
	char	*str;
	int		len;

	len = ft_get_len(lst);
	if (len == 0)
		return (NULL);
	new = (char *)malloc((len + 1) * sizeof(char));
	if (!new)
		return (NULL);
	current = lst;
	str = NULL;
	while (current)
	{
		str = current->str;
		while (*str != '\n' && *str)
			*new++ = *str++;
		current = current->next;
	}
	if (str != NULL && *str == '\n')
		*new++ = *str++;
	*new = '\0';
	return (new - len);
}

char	*ft_gnl(int fd)
{
	static t_node	*lst = NULL;
	char			*line;
	int				s;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	s = ft_createlst(fd, &lst);
	if (s < 0 || !lst)
		return (ft_freelst(&lst));
	line = ft_create_str(lst);
	if (line == NULL)
		return (ft_freelst(&lst));
	ft_update_lst(&lst);
	return (line);
}
