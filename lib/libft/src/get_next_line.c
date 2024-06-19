/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 13:30:58 by vvaudain          #+#    #+#             */
/*   Updated: 2024/06/18 13:26:49 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

// size_t	ft_strlcpy(char *dst, char *src, size_t size)
// {
// 	size_t	i;
// 	char	*source;

// 	i = 0;
// 	source = (char *) src;
// 	if (size == 0)
// 		return (ft_strlen(src));
// 	while ((source[i]) && (i < size - 1))
// 	{
// 		dst[i] = source[i];
// 		i++;
// 	}
// 	if (i < size)
// 		dst[i] = '\0';
// 	return (ft_strlen(src));
// }

char	*ft_check_and_stock(char *stockage, char *ptrstr)
{
	int		i;
	char	*line;

	i = 0;
	while (stockage[i] != '\n' && stockage[i])
		i++;
	line = ft_substr(stockage, 0, i + 1);
	if (stockage[i] == '\n' && stockage[i + 1])
	{
		if (ft_strlen(stockage) < BUFFER_SIZE)
			ft_strlcpy(ptrstr, stockage + i + 1, BUFFER_SIZE);
		else
			ft_strlcpy(ptrstr, stockage + i + 1,
				ft_strlen(stockage + i + 1) + 1);
	}
	if (stockage[i] == '\n' && !stockage[i + 1])
		ptrstr = ft_memset(ptrstr, 0, (size_t)ft_strlen(ptrstr));
	free(stockage);
	return (line);
}

int	ft_is_next_line(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

char	*ft_read(int fd, char *stockage, char *ptrstr, int size)
{
	char	*temp;
	int		new_size;
	int		j;

	j = 1;
	new_size = size;
	while (ft_is_next_line(stockage) != 0 && j > 0)
	{
		j = read(fd, ptrstr, BUFFER_SIZE);
		if (j < 0)
			return (NULL);
		if (j == 0 && *stockage == '\0')
			return (free (stockage), NULL);
		ptrstr[j] = '\0';
		new_size += BUFFER_SIZE;
		temp = malloc((new_size + 1) * sizeof(char));
		if (!temp)
			return (NULL);
		ft_strlcpy(temp, stockage, ft_strlen(stockage) + 1);
		free(stockage);
		stockage = temp;
		ft_strlcat(stockage, ptrstr, new_size + 1);
	}
	return (stockage);
}

char	*get_next_line(int fd)
{
	static char	ptrstr[BUFFER_SIZE + 1];
	int			size;
	char		*stockage;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1 || !BUFFER_SIZE || read(fd, 0, 0) < 0)
		return (NULL);
	size = 0;
	stockage = ft_strdup("");
	if (ptrstr[0] != '\0')
	{
		size = ft_strlen(ptrstr) + 1;
		free(stockage);
		stockage = malloc (size * sizeof(char));
		ft_strlcpy(stockage, ptrstr, size);
	}
	stockage = ft_read(fd, stockage, ptrstr, size);
	if (!stockage)
		return (NULL);
	line = ft_check_and_stock(stockage, ptrstr);
	return (line);
}
