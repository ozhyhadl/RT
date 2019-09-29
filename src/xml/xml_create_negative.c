/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_create_negative.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhyhadl <ozhyhadl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 17:15:16 by ozhyhadl          #+#    #+#             */
/*   Updated: 2019/09/27 19:37:35 by ozhyhadl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

int		ft_is_negative(mxml_node_t *node, t_scene *scene, int i, int what_is)
{
	const char	*name;
	cl_double3	dot;
	cl_double	one_dot;

	if (what_is != 4)
		return (1);
	name = mxmlGetElement(node);
	if (ft_strequ(name, "centre") && ft_get_3param(3, \
		mxmlGetOpaque(node), &dot, NULL))
	{
		scene->neg_obj[i].shape.sphere.cent = (cl_double3)dot;
		return (0);
	}
	else if (ft_strequ(name, "radius") && ft_get_3param(1, \
			mxmlGetOpaque(node), NULL, &one_dot) && one_dot >= 0)
	{
		scene->neg_obj[i].shape.sphere.radius = (cl_double)one_dot;
		return (0);
	}
	ft_putstr(RED"XML : invalid param "COLOR_OFF);
	ft_putendl(name);
	return (1);
}

int		ft_create_negative_spher(t_scene *scene, int *il)
{
	il[2]++;
	scene->neg_obj[il[2]].fig_type = SPHERE;
	scene->neg_obj[il[2]].shape.sphere.cent = (cl_double3){{0, 0, 0 }};
	scene->neg_obj[il[2]].shape.sphere.radius = (cl_double)1;
	return (4);
}
