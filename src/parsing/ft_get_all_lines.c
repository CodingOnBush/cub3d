/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_all_lines.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:04:11 by momrane           #+#    #+#             */
/*   Updated: 2024/06/28 17:12:04 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_count_lines(char *file)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (perror(file), -1);
	count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		count++;
		free(line);
	}
	close(fd);
	return (count);
}

static void	ft_remove_spaces_at_end(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (line[len - 1] == '\n')
		line[len - 1] = ' ';
	while (len > 0 && line[len - 1] == ' ')
	{
		line[len - 1] = '\0';
		len--;
	}
}

int	ft_get_all_lines(t_env *env, char *cubfile)
{
	int	fd;
	int	row;
	int	len;

	fd = open(cubfile, O_RDONLY);
	if (fd == -1)
		return (perror(cubfile), FAILURE);
	env->file.rows = ft_count_lines(cubfile);
	if (env->file.rows == -1)
		return (close(fd), FAILURE);
	if (env->file.rows == 0)
		return (close(fd), ft_err("Empty file", FAILURE));
	env->file.content = (char **)malloc(sizeof(char *) * (env->file.rows + 1));
	if (!env->file.content)
		return (close(fd), FAILURE);
	env->file.content[env->file.rows] = NULL;
	row = 0;
	while (row < env->file.rows)
	{
		env->file.content[row] = get_next_line(fd);
		len = ft_strlen(env->file.content[row]);
		ft_remove_spaces_at_end(env->file.content[row]);
		row++;
	}
	return (close(fd), SUCCESS);
}
