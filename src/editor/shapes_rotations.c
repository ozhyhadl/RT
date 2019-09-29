/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_rotations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yruda <yruda@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 17:10:00 by yruda             #+#    #+#             */
/*   Updated: 2019/09/28 12:16:02 by yruda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

cl_double3	vector_rotation(const Uint8 *k_s, cl_double3 n, double angle)
{
	if (k_s[SDL_SCANCODE_KP_8])
		n = (rotate_x(n, angle));
	else if (k_s[SDL_SCANCODE_KP_2])
		n = (rotate_x(n, -angle));
	else if (k_s[SDL_SCANCODE_KP_4])
		n = (rotate_y(n, -angle));
	else if (k_s[SDL_SCANCODE_KP_6])
		n = (rotate_y(n, angle));
	else if (k_s[SDL_SCANCODE_KP_7] || k_s[SDL_SCANCODE_KP_1])
		n = (rotate_z(n, angle));
	else if (k_s[SDL_SCANCODE_KP_9] || k_s[SDL_SCANCODE_KP_3])
		n = (rotate_z(n, -angle));
	return (n);
}

cl_double3	normal_direction_rotation(const Uint8 *k_s, cl_double3 n,
	double angle, t_fig *fig)
{
	n = vector_rotation(k_s, n, angle);
	fig->rotation_martix = build_rotation_matrix_for_dir(n);
	if (fig->cutting)
	{
		fig->cutting_plane.dot =
			vector_rotation(k_s, fig->cutting_plane.dot, angle);
		fig->cutting_plane.normal =
			vector_rotation(k_s, fig->cutting_plane.normal, angle);
	}
	return (n);
}

static int	add_angle_rotation(const Uint8 *k_s, cl_double3 *angle)
{
	if (k_s[SDL_SCANCODE_KP_8])
		angle->s[0] += 0.2;
	else if (k_s[SDL_SCANCODE_KP_2])
		angle->s[0] -= 0.2;
	else if (k_s[SDL_SCANCODE_KP_4])
		angle->s[1] -= 0.2;
	else if (k_s[SDL_SCANCODE_KP_6])
		angle->s[1] += 0.2;
	else if (k_s[SDL_SCANCODE_KP_7] || k_s[SDL_SCANCODE_KP_1])
		angle->s[2] += 0.2;
	else if (k_s[SDL_SCANCODE_KP_9] || k_s[SDL_SCANCODE_KP_3])
		angle->s[2] -= 0.2;
	return (1);
}

void		rotate_by_type(const Uint8 *k_s, t_fig *fig, t_scene *scene)
{
	if (fig->fig_type == CONE)
		fig->shape.cone.dir =
			normal_direction_rotation(k_s, fig->shape.cone.dir, 0.2, fig);
	else if (fig->fig_type == PLANE)
		fig->shape.plane.normal =
			normal_direction_rotation(k_s, fig->shape.plane.normal, 0.2, fig);
	else if (fig->fig_type == DISK)
		fig->shape.disk.normal =
			normal_direction_rotation(k_s, fig->shape.disk.normal, 0.2, fig);
	else if (fig->fig_type == CYLIN)
		fig->shape.cylin.dir =
			normal_direction_rotation(k_s, fig->shape.cylin.dir, 0.2, fig);
	else if (fig->fig_type == RECTANGLE && fig->complex_fig > -1)
	{
		add_angle_rotation(k_s, &scene->cubs[fig->complex_fig].rotation);
		scene->cubs[fig->complex_fig].rotation_matrix =
			build_rotation_matrix_form_angles(scene->cubs[fig->complex_fig].\
			rotation);
	}
}
