/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_it_is2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhyhadl <ozhyhadl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 21:27:17 by ozhyhadl          #+#    #+#             */
/*   Updated: 2019/09/27 22:50:37 by ozhyhadl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

int	ft_is_param3(mxml_node_t *node, t_rt *rt, int i, const char *name)
{
	t_scene	*scene;

	scene = &rt->scene;
	if (ft_strequ(name, "move_dir"))
		return (ft_add_move_dir(mxmlGetOpaque(node), rt, i));
	else if (ft_strequ(name, "v0") || ft_strequ(name, "v1") || \
		ft_strequ(name, "v2") || ft_strequ(name, "v3"))
		return (ft_add_v(mxmlGetOpaque(node), scene, i, name));
	else if (ft_strequ(name, "distance"))
		return (ft_add_distance(mxmlGetOpaque(node), scene, i, &rt->filters));
	else if (ft_strequ(name, "cub_rotation"))
		return (ft_add_rotation(mxmlGetOpaque(node), scene, i, &rt->filters));
	return (0);
}

int	ft_is_param2(mxml_node_t *node, t_rt *rt, int i, const char *name)
{
	t_scene	*scene;

	scene = &rt->scene;
	if (ft_strequ(name, "mmin") || ft_strequ(name, "mmax"))
		return (ft_add_mmin_mmax(mxmlGetOpaque(node), scene, i, name));
	else if (ft_strequ(name, "transparency") || ft_strequ(name, "specular") || \
	ft_strequ(name, "cut_normal") || ft_strequ(name, "texture") || \
	ft_strequ(name, "bump") || ft_strequ(name, "cutting") || \
	ft_strequ(name, "cut_dot") || ft_strequ(name, "reflective") || \
	ft_strequ(name, "rotation") || ft_strequ(name, "ior") || \
	ft_strequ(name, "transp_map_no") || ft_strequ(name, "txt_offset") || \
	ft_strequ(name, "txt_scale") || ft_strequ(name, "noise"))
	{
		if (scene->obj[i].fig_type == RECTANGLE && \
		scene->obj[i].complex_fig != -1)
		{
			add_for_all_obj(mxmlGetOpaque(node), rt, i, name);
			ft_fill_rectangle(scene, scene->obj[i].complex_fig, \
			&scene->obj[i], &rt->filters);
		}
		return (add_for_all_obj(mxmlGetOpaque(node), rt, i, name));
	}
	else
		return (ft_is_param3(node, rt, i, name));
	return (0);
}

int	ft_is_param(mxml_node_t *node, t_rt *rt, int i, int what_is)
{
	const char	*name;
	t_scene		*scene;

	scene = &rt->scene;
	if (what_is != 1)
		return (1);
	name = mxmlGetElement(node);
	if (ft_strequ(name, "centre") || ft_strequ(name, "dot") || \
		ft_strequ(name, "vertex"))
		return (add_position(mxmlGetOpaque(node), scene, i, name));
	else if (ft_strequ(name, "RGB"))
		return (ft_add_rgb(mxmlGetOpaque(node), scene, i));
	else if (ft_strequ(name, "radius"))
		return (ft_add_radius(mxmlGetOpaque(node), scene, i));
	else if (ft_strequ(name, "normal") || ft_strequ(name, "dir"))
		return (ft_add_normal_dir(mxmlGetOpaque(node), scene, i, name));
	else if (ft_strequ(name, "angle"))
		return (ft_add_tanget(mxmlGetOpaque(node), scene, i));
	else if (ft_is_param2(node, rt, i, name))
		return (0);
	ft_putstr(RED"XML : invalid param "COLOR_OFF);
	ft_putendl(name);
	return (1);
}
