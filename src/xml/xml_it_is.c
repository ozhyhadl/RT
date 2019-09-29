/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_it_is.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhyhadl <ozhyhadl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 16:48:30 by ozhyhadl          #+#    #+#             */
/*   Updated: 2019/09/28 14:33:47 by ozhyhadl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

int	ft_check_child(mxml_node_t *node)
{
	if ((node = mxmlGetFirstChild(node)) != NULL)
		if (mxmlGetOpaque(mxmlGetParent(node)) != NULL)
			node = mxmlGetNextSibling(node);
	if (node != NULL)
	{
		ft_putstr(RED"XML: Mistake palace tag "COLOR_OFF);
		ft_putstr(mxmlGetElement(node));
		ft_putstr(RED" after "COLOR_OFF);
		ft_putendl(mxmlGetElement(mxmlGetParent(node)));
		return (1);
	}
	return (0);
}

int	ft_is_cam(mxml_node_t *node, t_pov *pov, int what_is)
{
	if (what_is != 3)
		return (1);
	if (ft_strequ(mxmlGetElement(node), "position"))
		return (ft_add_cam_dot(mxmlGetOpaque(node), pov));
	if (ft_strequ(mxmlGetElement(node), "dir"))
		return (ft_add_cam_dir(mxmlGetOpaque(node), pov));
	else
		return (error_message(RED"XML: invalid tag for cam"COLOR_OFF));
}

int	ft_is_light(mxml_node_t *node, t_scene *scene, int l, int what_is)
{
	const char	*name;
	cl_double3	dot;

	if (what_is != 2)
		return (1);
	name = mxmlGetElement(node);
	if (ft_strequ(name, "type"))
		return (ft_add_type_light(scene, l, (char *)mxmlGetOpaque(node)));
	else if (ft_strequ(name, "intensity") && \
			ft_get_3param(3, mxmlGetOpaque(node), &dot, NULL))
		if (dot.s[0] >= 0 && dot.s[1] >= 0 && dot.s[2] >= 0)
			scene->light[l].intensity = (cl_double3)dot;
		else
			return (error_message(RED"XML : intensity >= 0 "COLOR_OFF));
	else if (ft_strequ(name, "position") && \
		ft_get_3param(3, mxmlGetOpaque(node), &dot, NULL))
		if (scene->light[l].type_num == DIRECT)
			scene->light[l].v = ft_normalize((cl_double3)dot);
		else
			scene->light[l].v = (cl_double3)dot;
	else
		return (error_message(RED"XML: invalid tag for light"COLOR_OFF));
	return (0);
}

int	ft_is_obj2(const char *str, t_scene *scene, int *il, t_rt *rt)
{
	if (ft_strequ(str, "spher"))
		ft_create_spher(scene, il[0], &rt->filters);
	else if (ft_strequ(str, "plane"))
		ft_create_pale(scene, il[0], &rt->filters);
	else if (ft_strequ(str, "cone"))
		ft_create_cone(scene, il[0], &rt->filters);
	else if (ft_strequ(str, "cylin"))
		ft_create_cylin(scene, il[0], &rt->filters);
	else if (ft_strequ(str, "disk"))
		ft_create_disk(scene, il[0], &rt->filters);
	else if (ft_strequ(str, "triangle"))
		ft_create_triangle(scene, il[0], &rt->filters);
	else if (ft_strequ(str, "rectangle"))
		ft_create_rectangle(scene, il[0], &rt->filters);
	else if (ft_strequ(str, "ellipse"))
		ft_create_ellipse(scene, il[0], &rt->filters);
	else if (ft_strequ(str, "cube"))
		ft_create_cube(scene, &rt->filters, il);
	else
		return (0);
	return (1);
}

int	ft_is_obj(const char *str, t_scene *scene, int *il, t_rt *rt)
{
	il[0] += 1;
	if (ft_is_obj2(str, scene, il, rt))
		return (1);
	else if (ft_strequ(str, "light"))
	{
		il[0] -= 1;
		il[1] += 1;
		ft_creat_light(scene, il[1]);
		return (2);
	}
	else if (ft_strequ(str, "cam"))
	{
		il[0] -= 1;
		ft_create_cam(&rt->pov);
		return (3);
	}
	else if (ft_strequ(str, "negative_spher"))
	{
		il[0] -= 1;
		return (ft_create_negative_spher(scene, il));
	}
	else
		return (0);
	return (1);
}
