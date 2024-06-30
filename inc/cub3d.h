/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:30:12 by momrane           #+#    #+#             */
/*   Updated: 2024/06/30 19:19:26 by allblue          ###   ########.fr       */
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
int		ft_strcmp(const char *s1, const char *s2);
int		ft_iswhitespace(char c);

/*	PARSING	*/
int		ft_parsing(t_env *env, char *cubfile);

/*	PARSING2	*/
int		ft_map_is_closed(t_env *env);

/*	ANALYZE	*/
int		ft_analyze_file(t_env *env);

/*	ANALYZE2	*/
int	ft_get_infos(t_env *env, char **split);

/*	INIT	*/
void	ft_init_env(t_env *env);

/*	LINEHEIGHT	*/
void	ft_set_line_height(t_env *env);

/*	IMG	*/
void	ft_pixel_put(t_env *env, int col, int row, int color);
t_img	ft_get_texture(t_env *env);
int		ft_get_tex_pixel(t_env *env, t_point tex);

/*	DRAW	*/
int		ft_render(t_env *env);

/*	HOOKS	*/
int		ft_win_cross(t_env *env);
int		ft_key_released(int keycode, t_env *env);
int		ft_key_pressed(int keycode, t_env *env);

/*	FREE	*/
void	ft_free_env(t_env *env);
void	ft_free_splitmore(char **split);
void	ft_free_array(char **array, int row);

/*	MLX	*/
int		ft_load_images(t_env *env);

/*	SPLITMORE	*/
char	**ft_splitmore(char const *s, char *set);

/*	UTILS2	*/
void	ft_update_dir(t_env *env);
int		ft_gettype(char *line);
int		ft_rgb_isvalid(t_env *env);

/*	UTILS3	*/
int		ft_rgb_to_int(int color[3]);

/*	CHECK_FILE	*/
int	ft_check_file_extension(char *file, char *ext);
int	ft_check_file(char *file);

/*	GET_ALL_LINES	*/
int	ft_get_all_lines(t_env *env, char *cubfile);

/*	FIND_PLAYER	*/
int	ft_find_player(t_env *env);

/*	MOVE	*/
void	ft_move(t_env *env);

#endif