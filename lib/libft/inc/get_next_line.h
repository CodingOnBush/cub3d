/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 13:30:23 by vvaudain          #+#    #+#             */
/*   Updated: 2024/06/18 13:27:48 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

char	*ft_read(int fd, char *stockage, char *ptrstr, int size);
int		ft_is_next_line(char *buf);
char	*ft_check_and_stock(char *stockage, char *ptrstr);
char	*get_next_line(int fd);

#endif