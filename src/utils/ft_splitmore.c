/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitmore.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 07:35:15 by momrane           #+#    #+#             */
/*   Updated: 2024/06/28 16:58:35 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// void	*ft_free_array(char **out, int i)
// {
// 	while (i > 0)
// 	{
// 		i--;
// 		free(out[i]);
// 	}
// 	free(out);
// 	return (NULL);
// }

static int	ft_count_words(const char *str, char *set)
{
	int	out;

	out = 0;
	if (!str)
		return (0);
	while (*str)
	{
		while (*str != '\0' && ft_strchr(set, *str) != NULL)
			str++;
		if (ft_strchr(set, *str) == NULL && *str != '\0')
			out++;
		while (*str != '\0' && ft_strchr(set, *str) == NULL)
			str++;
	}
	return (out);
}

static int	ft_get_wlen(const char *str, char *set)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (ft_strchr(set, str[i]) != NULL)
			break ;
		i++;
	}
	return (i);
}

static int	ft_apply_split(char **out, int len, char const *s, char *set)
{
	int const	slen = ft_strlen(s);
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (s[j] != '\0' && i < len)
	{
		while (ft_strchr(set, s[j]) != NULL)
			s++;
		if (!s[j])
			break ;
		out[i] = ft_substr(&s[j], 0, ft_get_wlen(&s[j], set));
		if (!out[i])
			return (ft_free_array(out, i), FAILURE);
		i++;
		j += ft_get_wlen(&s[j], set);
		if (j >= slen)
			break ;
	}
	return (SUCCESS);
}

char	**ft_splitmore(char const *s, char *set)
{
	char		**out;
	int const	len = ft_count_words(s, set);

	if (!s)
		return (NULL);
	out = malloc(sizeof(char *) * (len + 1));
	if (!out)
		return (NULL);
	out[len] = NULL;
	if (ft_apply_split(out, len, s, set) == FAILURE)
		return (NULL);
	return (out);
}

// #include <stdio.h>

// int	main(void)
// {
//  	char	**result;
// 	char	*str;
//  	int		i;

// 	str = "1, 2, 3, 4, 5";
// 	result = ft_splitmore(str, "\0");
// 	i = 0;
//  	while (result[i] != NULL) {
//  		printf("%s\n", result[i]);
//  		i++;
//  	}
// 	ft_free_array(result, i);
// 	return (0);
// }
