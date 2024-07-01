/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 07:24:35 by momrane           #+#    #+#             */
/*   Updated: 2024/07/01 18:05:48 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_err(char *str, int ret)
{
	ft_err_title();
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
	return (ret);
}

int	ft_splitlen(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return (0);
	while (split[i])
		i++;
	return (i);
}

int	ft_get_id(char *str)
{
	if (!str)
		return (-1);
	if (ft_strcmp(str, "WE") == 0)
		return (WEST);
	if (ft_strcmp(str, "EA") == 0)
		return (EAST);
	if (ft_strcmp(str, "NO") == 0)
		return (NORTH);
	if (ft_strcmp(str, "SO") == 0)
		return (SOUTH);
	if (ft_strcmp(str, "C") == 0)
		return (CEIL);
	if (ft_strcmp(str, "F") == 0)
		return (FLOOR);
	return (-1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

int	ft_iswhitespace(char c)
{
	if (c == '\0')
		return (NO);
	if (ft_strchr(" \t\n\v\f\r", c) != NULL)
		return (YES);
	return (NO);
}
