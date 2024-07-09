/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:30:12 by momrane           #+#    #+#             */
/*   Updated: 2024/07/09 17:06:57 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "defines.h"
# include "includes.h"
# include "structs.h"

/* ======================== MLX ======================== */
/*	event	*/
int		ft_win_cross(t_env *env);
int		ft_key_pressed(int keycode, t_env *env);
int		ft_key_released(int keycode, t_env *env);

/*	load_images	*/
int		load_images(t_env *env);

/* ====================== PARSING ====================== */
/*	create_map	*/
int		ft_create_map(t_env *env, char *filepath);

/*	ft_check_each_zero	*/
int		ft_check_each_zero(t_env *env);

/*	ft_find_player	*/
int		ft_find_player(t_env *env);

/*	ft_map_is_closed	*/
int		ft_flood_fill(t_env *env, int px, int py);
int		ft_map_is_closed(t_env *env);

/*	ft_set_map_size	*/
int		ft_set_map_size(t_env *env, int fd);

/*	parse_infos	*/
int		ft_parse_infos(t_env *env, char *cubfile);

/*	parsing	*/
int		ft_parsing(t_env *env, char *cubfile);

/*	utils	*/
int		ft_color_is_empty(int color[3]);
int		ft_is_texture_line(char *line);
int		ft_is_color_line(char *line);
int		ft_atoicolor(const char *str);
int		ft_all_data_collected(t_env *env);

/* ==================== RAYCASTING ==================== */
/*	img	*/
void	ft_pixel_put(t_env *env, int c, int r, int color);
int		ft_get_texpixel(t_env *env, int texx, int texy);
int		ft_get_texx(t_env *env);

/*	move	*/
void	ft_move(t_env *env);

/*	render	*/
int		ft_render(t_env *env);

/*	wallheight	*/
int		ft_get_line_height(t_env *env, int col);

/* ======================== TOOLS ====================== */
/*	free	*/
void	ft_free_env(t_env *env);
void	ft_free_split(char **split);
void	ft_free_array(char **array, int row);

/*	ft_splitmore	*/
char	**ft_splitmore(char const *s, char *set);

/*	init	*/
void	ft_init_env(t_env *env);

/*	utils	*/
int		ft_err(char *str, int ret);
int		ft_splitlen(char **split);
int		ft_get_id(char *str);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_iswhitespace(char c);

/*	utils2	*/
void	ft_update_dir(t_env *env);
int		ft_gettype(char *line);
int		ft_rgb_isvalid(t_env *env);

/*	utils3	*/
int		ft_rgb_to_int(int color[3]);
void	ft_reset_map(char **map, int mapw, int maph);
void	ft_err_title(void);
void	ft_remove_spaces_at_end(char *line);

#endif