/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_write_param.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhyhadl <ozhyhadl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 22:13:18 by ozhyhadl          #+#    #+#             */
/*   Updated: 2019/09/28 13:55:01 by ozhyhadl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

void	ft_write_param(cl_double param, mxml_node_t *node, const char *name)
{
	char	*tmp;

	node = mxmlNewElement(node, name);
	mxmlNewText(node, 0, (tmp = double_to_char(param)));
	ft_strdel(&tmp);
}

void	ft_write_3param(cl_double3 param, mxml_node_t *node, const char *name)
{
	char	*tmp;

	node = mxmlNewElement(node, name);
	mxmlNewText(node, 0, (tmp = double_to_char(param.s[0])));
	ft_strdel(&tmp);
	mxmlNewText(node, 1, (tmp = double_to_char(param.s[1])));
	ft_strdel(&tmp);
	mxmlNewText(node, 1, (tmp = double_to_char(param.s[2])));
	ft_strdel(&tmp);
}

void	ft_write_2param(cl_double2 param, mxml_node_t *node, const char *name)
{
	char	*tmp;

	node = mxmlNewElement(node, name);
	mxmlNewText(node, 0, (tmp = double_to_char(param.s[0])));
	ft_strdel(&tmp);
	mxmlNewText(node, 1, (tmp = double_to_char(param.s[1])));
	ft_strdel(&tmp);
}

void	ft_write_big_double(cl_double param, mxml_node_t *node, \
		const char *name)
{
	node = mxmlNewElement(node, name);
	mxmlNewReal(node, param);
}

void	ft_write_all(t_fig fig, mxml_node_t *node, t_obj_movement *filter)
{
	ft_write_3param(fig.color, node, (const char *)"RGB");
	ft_write_param(fig.trans, node, (const char *)"transparency");
	ft_write_param(fig.reflective, node, (const char *)"reflective");
	ft_write_param((cl_double)fig.specular, node, (const char *)"specular");
	ft_write_param((cl_double)fig.text_no, node, (const char *)"texture");
	ft_write_param((cl_double)fig.normal_map_no, node, "bump");
	ft_write_param((cl_double)fig.noise, node, "noise");
	ft_write_param((cl_double)fig.cutting, node, "cutting");
	ft_write_3param(fig.cutting_plane.dot, node, "cut_dot");
	ft_write_3param(fig.cutting_plane.normal, node, "cut_normal");
	if (fig.fig_type == SPHERE)
		ft_write_3param(fig.rotation, node, "rotation");
	ft_write_big_double(fig.ior, node, (const char *)"ior");
	ft_write_param((cl_double)fig.transparancy_map_no, node,\
	(const char *)"transp_map_no");
	ft_write_2param(fig.txt_offset, node, "txt_offset");
	ft_write_2param(fig.txt_scale, node, "txt_scale");
	if (filter->move != 0)
		ft_write_3param(filter->dir, node, "move_dir");
}
