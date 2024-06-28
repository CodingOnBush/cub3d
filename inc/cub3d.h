/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:30:12 by momrane           #+#    #+#             */
/*   Updated: 2024/06/28 12:13:52 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "defines.h"
# include "includes.h"
# include "structs.h"

/*	UTILS	*/
int		ft_err(char *str, int ret);
int		ft_splitlen(char **split);
int		ft_get_id(char *str);
void	ft_update_dir(t_env *env);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_iswhitespace(char c);

/*	PARSING	*/
int		ft_parsing(t_env *env, char *cubfile);

/*	PARSING2	*/
int		ft_map_is_closed(t_env *env);

/*	INIT	*/
void	ft_init_env(t_env *env);

/*	DRAW	*/
int		ft_render(t_env *env);

/*	HOOKS	*/
int		ft_win_cross(t_env *env);
int		ft_key_hook(int keycode, t_env *env);
int		ft_key_released(int keycode, t_env *env);
int		ft_key_pressed(int keycode, t_env *env);

/*	FREE	*/
void	ft_free_env(t_env *env);
void	ft_free_splitmore(char **split);

/*	MLX	*/
int		ft_load_images(t_env *env);

/*	SPLITMORE	*/
char	**ft_splitmore(char const *s, char *set);

#endif