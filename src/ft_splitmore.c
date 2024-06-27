/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitmore.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 07:35:15 by momrane           #+#    #+#             */
/*   Updated: 2024/06/27 07:43:52 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	*ft_free_array(char **out, int i)
{
	while (i > 0)
	{
		i--;
		free(out[i]);
	}
	free(out);
	return (NULL);
}

static int	ft_count_words(const char *str, char *set)
{
	int	out;

	out = 0;
	while (*str)
	{
		while (ft_strchr(set, *str) != NULL)
			str++;
		if (ft_strchr(set, *str) == NULL && *str != '\0')
			out++;
		while (ft_strchr(set, *str) == NULL && *str != '\0')
			str++;
	}
	return (out);
}

static int	ft_get_wlen(const char *str, char *set)/*char sep*/
{
	// if (!ft_strchr(str, sep))
	// 	return (ft_strlen(str));
	// else
	// 	return (ft_strchr(str, sep) - str);
	int	i;

	i = 0;
	while(str[i])
	{
		if (ft_strchr(set, str[i]) != NULL)
			break;
		i++;
	}
	return (i);
}

char	**ft_splitmore(char const *s, char *set)
{
	char	**out;
	int		i;

	if (!s)
		return (NULL);
	out = malloc((ft_count_words(s, set) + 1) * sizeof(char *));
	if (!out)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (ft_strchr(set, *s) != NULL)
			s++;
		if (*s)
		{
			out[i] = ft_substr(s, 0, ft_get_wlen(s, set));
			if (!out[i])
				return (ft_free_array(out, i));
			i++;
			s += ft_get_wlen(s, set);
		}
	}
	out[i] = NULL;
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
