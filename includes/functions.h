/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 23:16:07 by anri              #+#    #+#             */
/*   Updated: 2019/09/28 12:56:01 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "rt.h"

cl_double3			*get_obj_dot(t_fig *fig);
cl_double3			get_obj_dir(t_fig fig);
void				ft_fill_rectangle(t_scene *scene, int cub, t_fig *fig,
					t_filters *filter);
cl_double3			canvas_to_viewport(int x, int y, t_pov pov);
t_rectangle_data	set_rectangles(cl_double3 *v, int r);
int					translate(t_rt *rt);
int					rotation(t_rt *rt);
int					changes_norm(t_rt *rt, int *rotations, int *move);
int					motion(t_rt *rt, cl_uint *pixels);
int					static_render(t_rt *rt, cl_uint *pixels);
void				move_obj_a_little(t_rt *rt);
void				set_obj_back(t_rt *rt);
void				add_to_buff_to_array(cl_double3 *arr, \
							Uint32 *buff, t_rt *rt);
void				array_to_screen_pixels(Uint32 *pix, \
						cl_double3 *arr, int div, t_rt *rt);

#endif
