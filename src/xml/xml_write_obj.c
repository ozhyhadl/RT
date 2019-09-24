/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_write_obj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhyhadl <ozhyhadl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 22:09:58 by ozhyhadl          #+#    #+#             */
/*   Updated: 2019/09/24 01:04:52 by ozhyhadl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

void	ft_write_spher(t_sphere_data spher, mxml_node_t *data, t_fig fig)
{
	mxml_node_t *node;

	node = mxmlNewElement(data, "spher");
	ft_write_3param(spher.cent, node, (const char *)"centre");
	ft_write_param((cl_double)spher.radius, node, (const char *)"radius");
	ft_write_all(fig, node);
}

void	ft_write_plane(t_plane_data plane, mxml_node_t *data, t_fig fig)
{
	mxml_node_t *node;

	node = mxmlNewElement(data, "plane");
	ft_write_3param(plane.dot, node, (const char *)"dot");
	ft_write_3param(plane.normal, node, (const char *)"normal");
	ft_write_all(fig, node);
}

void	ft_write_cylin(t_cylin_data cylin, mxml_node_t *data, t_fig fig)
{
	mxml_node_t *node;

	node = mxmlNewElement(data, "cylin");
	ft_write_3param(cylin.dot, node, (const char *)"dot");
	ft_write_3param(cylin.dir, node, (const char *)"dir");
	ft_write_param(cylin.mmax, node, (const char *)"mmax");
	ft_write_param(cylin.mmin, node, (const char *)"mmin");
	ft_write_all(fig, node);
}

void	ft_write_cone(t_cone_data cone, mxml_node_t *data, t_fig fig)
{
	mxml_node_t *node;

	node = mxmlNewElement(data, "cone");
	ft_write_3param(cone.vertex, node, (const char *)"vertex");
	ft_write_3param(cone.dir, node, (const char *)"dir");
	ft_write_param(cone.mmax, node, (const char *)"mmax");
	ft_write_param(cone.mmin, node, (const char *)"mmin");
	ft_write_param(cone.tangent * 180 / 3.14, node, (const char *)"angle");
	ft_write_all(fig, node);
}

void	ft_write_to_xml(t_fig fig, mxml_node_t *data)
{
	if (fig.fig_type == SPHERE)
		ft_write_spher(fig.shape.sphere, data, fig);
	if (fig.fig_type == PLANE)
		ft_write_plane(fig.shape.plane, data, fig);
	if (fig.fig_type == CYLIN)
		ft_write_cylin(fig.shape.cylin, data, fig);
	if (fig.fig_type == CONE)
		ft_write_cone(fig.shape.cone, data, fig);
}
