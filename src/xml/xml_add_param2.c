/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_add_param2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhyhadl <ozhyhadl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 00:50:49 by ozhyhadl          #+#    #+#             */
/*   Updated: 2019/09/28 00:27:45 by ozhyhadl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

int	add_for_all_obj3(const char *str, t_rt *rt, int i, const char *tag)
{
	cl_double3	dot;
	t_scene		*scene;
	cl_double	one_dot;

	scene = &rt->scene;
	dot.s[1] = -10;
	if (ft_strequ(tag, "txt_offset") && ft_get_3param(2, str, &dot, NULL))
	{
		scene->obj[i].txt_offset.s[0] = dot.s[0];
		scene->obj[i].txt_offset.s[1] = dot.s[1];
	}
	else if (ft_strequ(tag, "txt_scale") && ft_get_3param(2, str, &dot, NULL))
	{
		scene->obj[i].txt_scale.s[0] = dot.s[0];
		scene->obj[i].txt_scale.s[1] = dot.s[1];
	}
	else if (ft_strequ(tag, "texture") && rt->envi.txt_count > ft_atoi(str))
		scene->obj[i].text_no = (cl_int)ft_atoi(str);
	else if (ft_strequ(tag, "bump") && rt->envi.txt_count > ft_atoi(str))
		scene->obj[i].normal_map_no = (cl_int)ft_atoi(str);
	else if (ft_strequ(tag, "noise") && ft_get_3param(1, str, NULL, &one_dot))
		scene->obj[i].noise = one_dot;
	else
		return (0);
	return (1);
}

int	add_for_all_obj2(const char *str, t_rt *rt, int i, const char *tag)
{
	cl_double	one_dot;
	cl_double3	dot;
	t_scene		*scene;

	scene = &rt->scene;
	if (ft_strequ(tag, "cutting") && ft_get_3param(1, str, NULL, &one_dot))
		scene->obj[i].cutting = (cl_int)one_dot;
	else if (ft_strequ(tag, "cut_dot") && ft_get_3param(3, str, &dot, NULL))
		scene->obj[i].cutting_plane.dot = (cl_double3)dot;
	else if (ft_strequ(tag, "cut_normal") && ft_get_3param(3, str, &dot, NULL))
		scene->obj[i].cutting_plane.normal = (cl_double3)dot;
	else if (ft_strequ(tag, "rotation") && ft_get_3param(3, str, &dot, NULL))
		scene->obj[i].rotation_martix = build_rotation_matrix_form_angles\
(scene->obj[i].rotation = (cl_double3)dot);
	else if (ft_strequ(tag, "ior") && ft_get_3param(1, str, NULL, &one_dot))
		if (one_dot < MIN_IOR || one_dot > MAX_IOR)
			return (!error_message(RED"XML: 1.0004 <= ior <= 2"COLOR_OFF));
		else
			scene->obj[i].ior = one_dot;
	else if (ft_strequ(tag, "transp_map_no") && \
	ft_get_3param(1, str, NULL, &one_dot) && rt->envi.txt_count > ft_atoi(str))
		scene->obj[i].transparancy_map_no = (cl_int)one_dot;
	else
		return (add_for_all_obj3(str, rt, i, tag));
	return (1);
}

int	add_for_all_obj(const char *str, t_rt *rt, int i, const char *tag)
{
	cl_double	one_dot;
	t_scene		*scene;

	scene = &rt->scene;
	if (add_for_all_obj2(str, rt, i, tag))
		return (1);
	if (!ft_get_3param(1, str, NULL, &one_dot))
		return (0);
	else if (ft_strequ(tag, "specular") && (one_dot < -1 || one_dot > 1000))
		return (!error_message(RED"XML: -1 <= specular <= 1000"COLOR_OFF));
	else if (ft_strequ(tag, "reflective") && (one_dot < 0 || one_dot > 1))
		return (!error_message(RED"XML: 0 <= reflective <= 1"COLOR_OFF));
	else if (ft_strequ(tag, "transparency") && (one_dot < 0 || one_dot > 1))
		return (!error_message(RED"XML: 0 <= transparency <= 1"COLOR_OFF));
	else if (ft_strequ(tag, "specular"))
		scene->obj[i].specular = (cl_int)ft_atoi(str);
	else if (ft_strequ(tag, "reflective"))
		scene->obj[i].reflective = (cl_double)one_dot;
	else if (ft_strequ(tag, "transparency"))
		scene->obj[i].trans = (cl_double)one_dot;
	else
		return (0);
	return (1);
}

int	ft_add_mmin_mmax(const char *str, t_scene *scene, int i, const char *tag)
{
	cl_double	one_dot;

	if (!ft_get_3param(1, str, NULL, &one_dot))
		return (0);
	if (ft_strequ(tag, "mmin"))
	{
		if (scene->obj[i].fig_type == CONE)
			scene->obj[i].shape.cone.mmin = one_dot;
		else if (scene->obj[i].fig_type == CYLIN)
			scene->obj[i].shape.cylin.mmin = one_dot;
	}
	else if (ft_strequ(tag, "mmax"))
	{
		if (scene->obj[i].fig_type == CONE)
			scene->obj[i].shape.cone.mmax = one_dot;
		else if (scene->obj[i].fig_type == CYLIN)
			scene->obj[i].shape.cylin.mmax = one_dot;
	}
	else
		return (0);
	return (1);
}

int	ft_add_move_dir(const char *str, t_rt *rt, int i)
{
	cl_double3	dot;

	if (!ft_get_3param(3, str, &dot, NULL))
		return (0);
	rt->filters.obj_movement[i].move = 1;
	rt->filters.obj_movement[i].dir = (cl_double3)dot;
	return (1);
}
