/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:06:22 by momrane           #+#    #+#             */
/*   Updated: 2024/01/22 09:47:05 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

t_pt	**ft_new_matrix(int r, int c)
{
	t_pt	**new;
	int		i;

	i = 0;
	new = (t_pt **)malloc(sizeof(t_pt *) * r);
	if (!new)
		return (NULL);
	while (i < r)
	{
		new[i] = (t_pt *)malloc(sizeof(t_pt) * c);
		if (!new[i])
			return (ft_free_matrix(new, i));
		i++;
	}
	return (new);
}

void	ft_parse_matrix(t_env *env, void (*f)(t_env *env, int r, int c))
{
	int	r;
	int	c;

	r = 0;
	while (r < env->rows)
	{
		c = 0;
		while (c < env->cols)
		{
			f(env, r, c);
			c++;
		}
		r++;
	}
}
