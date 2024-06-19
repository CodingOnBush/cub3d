/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:38:12 by vvaudain          #+#    #+#             */
/*   Updated: 2024/06/19 11:28:14 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	ft_count_lines(char *file)
{
	int		fd;
	int		nb_lines;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (perror(file), FAILURE);
	nb_lines = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		nb_lines++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (nb_lines);
}

char	*ft_get_texture(char *line)
{
	char **infos;
	char *path;
	
	infos = ft_split(line, ' ');
	if (!infos)
		return (NULL);
	if (infos[2] != NULL)
		return (free(infos), NULL);
	if (infos[1] == NULL)
		return (free(infos), NULL);
	path = ft_strdup(infos[1]);
	return (free(infos), path);
}

void	ft_set_color(char *line, t_color *color)
{
	char **infos;
	
	infos = ft_split(line, ' ');
	if (!infos)
		return ;
	if (infos[3] != NULL || infos[2] == NULL)
	{
		free(infos);
		return ;
	}
	color->r = ft_atoi(infos[1]);
	color->g = ft_atoi(infos[2]);
	color->b = ft_atoi(infos[3]);
	free(infos);
}

int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}