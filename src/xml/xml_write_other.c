/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_write_other.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhyhadl <ozhyhadl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 22:14:38 by ozhyhadl          #+#    #+#             */
/*   Updated: 2019/09/28 15:33:17 by ozhyhadl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

void	ft_write_light(t_light light, mxml_node_t *data)
{
	mxml_node_t *node;

	node = mxmlNewElement(data, "light");
	if (light.type_num == AMBIENT)
	{
		mxmlNewText(mxmlNewElement(node, "type"), 0, (const char *)"ambient");
		ft_write_3param(light.intensity, node, (const char *)"intensity");
		return ;
	}
	else if (light.type_num == POINT)
		mxmlNewText(mxmlNewElement(node, "type"), 0, (const char *)"point");
	else if (light.type_num == DIRECT)
		mxmlNewText(mxmlNewElement(node, "type"), 0, (const char *)"direct");
	ft_write_3param(light.v, node, (const char *)"position");
	ft_write_3param(light.intensity, node, (const char *)"intensity");
}

void	ft_write_cam(t_pov pov, mxml_node_t *data)
{
	mxml_node_t *node;

	node = mxmlNewElement(data, "cam");
	ft_write_3param(pov.coord, node, (const char *)"position");
	ft_write_3param(pov.dir, node, (const char *)"dir");
}

void	ft_write_neg(t_negative_fig neg, mxml_node_t *data)
{
	mxml_node_t *node;

	node = mxmlNewElement(data, "negative_spher");
	ft_write_3param(neg.shape.sphere.cent, node, (const char *)"centre");
	ft_write_param(neg.shape.sphere.radius, node, (const char *)"radius");
}
