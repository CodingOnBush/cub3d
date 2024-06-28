/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:00:10 by momrane           #+#    #+#             */
/*   Updated: 2024/06/28 17:01:36 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_is_color(char **split)
{
	int	id;

	if (!split || !*split)
		return (NO);
	id = ft_get_id(split[0]);
	if (id == CEIL || id == FLOOR)
		return (YES);
	return (NO);
}

int	ft_get_infos(t_env *env, char **split)
{
	if (!split)
		return (ft_free_splitmore(split), GOON);
	if (!split[0])
		return (ft_free_splitmore(split), GOON);
	if (ft_get_id(split[0]) == -1)
		return (ft_free_splitmore(split), STOP);
	if (ft_splitlen(split) == 2 && ft_get_id(split[0]) != -1)
	{
		env->file.count++;
		if (env->img[ft_get_id(split[0])].path != NULL)
			return (ft_free_splitmore(split), GOON);
		env->img[ft_get_id(split[0])].path = ft_strdup(split[1]);
	}
	else if (ft_splitlen(split) == 4 && ft_is_color(split) == YES)
	{
		env->file.colors[ft_get_id(split[0])][R] = ft_atoi(split[1]);
		env->file.colors[ft_get_id(split[0])][G] = ft_atoi(split[2]);
		env->file.colors[ft_get_id(split[0])][B] = ft_atoi(split[3]);
		env->file.count++;
	}
	else
		return (ft_free_splitmore(split), STOP);
	return (ft_free_splitmore(split), GOON);
}
