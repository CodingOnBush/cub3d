/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_map_size.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:32:59 by momrane           #+#    #+#             */
/*   Updated: 2024/07/08 16:00:05 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static char	*ft_skip_empty_lines(t_env *env, int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (ft_err("Missing map", FAILURE), NULL);
	while (line != NULL)
	{
		if (ft_strchr(line, '\n') != NULL)
			*(ft_strchr(line, '\n')) = '\0';
		if (line[0] != '\0')
			return (line);
		free(line);
		env->mapstart++;
		line = get_next_line(fd);
	}
	return (NULL);
}

int	ft_set_map_size(t_env *env, int fd)
{
	char	*line;
	int		empty;

	line = ft_skip_empty_lines(env, fd);
	if (!line)
		return (FAILURE);
	empty = 0;
	while (line != NULL)
	{
		env->maph++;
		if (ft_strchr(line, '\n') != NULL)
			*(ft_strchr(line, '\n')) = '\0';
		if (line[0] == '\0')
			empty++;
		else
			empty = 0;
		if (ft_strlen(line) > env->mapw)
			env->mapw = ft_strlen(line);
		free(line);
		line = get_next_line(fd);
	}
	env->maph = env->maph - empty;
	return (SUCCESS);
}
