/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_write_obj2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhyhadl <ozhyhadl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 23:27:40 by ozhyhadl          #+#    #+#             */
/*   Updated: 2019/09/27 23:28:21 by ozhyhadl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

mxml_node_t	*ft_write_triangle(t_triangle_data triangle, mxml_node_t *data)
{
	mxml_node_t *node;

	node = mxmlNewElement(data, "triangle");
	ft_write_3param(triangle.v0, node, (const char *)"v0");
	ft_write_3param(triangle.v1, node, (const char *)"v1");
	ft_write_3param(triangle.v2, node, (const char *)"v2");
	return (node);
}

mxml_node_t	*ft_write_disk(t_disk_data disk, mxml_node_t *data)
{
	mxml_node_t *node;

	node = mxmlNewElement(data, "disk");
	ft_write_3param(disk.cent, node, (const char *)"centre");
	ft_write_3param(disk.normal, node, (const char *)"normal");
	ft_write_param(disk.radius, node, (const char *)"radius");
	return (node);
}

mxml_node_t	*ft_write_rectangle(t_rectangle_data rectangle, mxml_node_t *data)
{
	mxml_node_t *node;

	node = mxmlNewElement(data, "rectangle");
	ft_write_3param(rectangle.v0, node, (const char *)"v0");
	ft_write_3param(rectangle.v1, node, (const char *)"v1");
	ft_write_3param(rectangle.v2, node, (const char *)"v2");
	ft_write_3param(rectangle.v3, node, (const char *)"v3");
	return (node);
}

mxml_node_t	*ft_write_ellipse(t_ellipse_data elipse, mxml_node_t *data)
{
	mxml_node_t *node;

	node = mxmlNewElement(data, "ellipse");
	ft_write_3param(elipse.cent, node, (const char *)"centre");
	ft_write_3param(elipse.dir, node, (const char *)"dir");
	ft_write_param(elipse.dist_btwn_cent, node, (const char *)"distance");
	ft_write_param(elipse.radius_sum, node, (const char *)"radius");
	return (node);
}

mxml_node_t	*ft_write_cube(t_cube cube, mxml_node_t *data, int *i)
{
	mxml_node_t *node;

	node = mxmlNewElement(data, "cube");
	ft_write_3param(cube.cent, node, (const char *)"centre");
	ft_write_param(cube.dist, node, (const char *)"distance");
	ft_write_3param(cube.rotation, node, (const char *)"cub_rotation");
	*i = *i + 5;
	return (node);
}
