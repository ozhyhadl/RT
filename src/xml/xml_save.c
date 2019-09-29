/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_save.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhyhadl <ozhyhadl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 13:32:14 by ozhyhadl          #+#    #+#             */
/*   Updated: 2019/09/28 13:55:29 by ozhyhadl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

int			is_frst_ltag(const char *str)
{
	if (ft_strequ(str, "spher") || ft_strequ(str, "plane") || \
		ft_strequ(str, "cone") || ft_strequ(str, "cylin") || \
		ft_strequ(str, "light") || ft_strequ(str, "cam") || \
		ft_strequ(str, "rectangle") || ft_strequ(str, "triangle") || \
		ft_strequ(str, "disk") || ft_strequ(str, "ellipse") || \
		ft_strequ(str, "cube") || ft_strequ(str, "negative_spher"))
		return (1);
	return (0);
}

int			is_param_ltag(const char *str)
{
	if (ft_strequ(str, "centre") || ft_strequ(str, "radius") || \
		ft_strequ(str, "RGB") || ft_strequ(str, "transparency") || \
		ft_strequ(str, "specular") || ft_strequ(str, "texture") || \
		ft_strequ(str, "vertex") || ft_strequ(str, "angle") || \
		ft_strequ(str, "type") || ft_strequ(str, "position") || \
		ft_strequ(str, "dot") || ft_strequ(str, "normal") || \
		ft_strequ(str, "intensity") || ft_strequ(str, "reflective") || \
		ft_strequ(str, "dir") || ft_strequ(str, "specular") || \
		ft_strequ(str, "bump") || ft_strequ(str, "mmin") || \
		ft_strequ(str, "mmax") || ft_strequ(str, "cutting") || \
		ft_strequ(str, "cut_dot") || ft_strequ(str, "cut_normal") ||
		ft_strequ(str, "rotation") || ft_strequ(str, "ior") || \
		ft_strequ(str, "transp_map_no") || ft_strequ(str, "txt_offset") || \
		ft_strequ(str, "txt_scale") || ft_strequ(str, "move_dir") || \
		ft_strequ(str, "v0") || ft_strequ(str, "v1") || ft_strequ(str, "v2") \
		|| ft_strequ(str, "v3") || ft_strequ(str, "distance") || \
		ft_strequ(str, "cub_rotation") || ft_strequ(str, "noise"))
		return (1);
	return (0);
}

const char	*whitespace_cb(mxml_node_t *node, int where)
{
	const char *element;

	element = mxmlGetElement(node);
	if (!strcmp(element, "RT"))
		return ("\n");
	if (is_frst_ltag(element))
	{
		if (where == MXML_WS_BEFORE_OPEN)
			return ("\t");
		if (where == MXML_WS_AFTER_CLOSE)
			return ("\n");
		if (where == MXML_WS_BEFORE_CLOSE)
			return ("\n\t");
	}
	if (is_param_ltag(element))
		if (where == MXML_WS_BEFORE_OPEN)
			return ("\n\t\t");
	return (NULL);
}

int			ft_xml_save(char *name_file, t_scene *scene, t_pov pov, t_rt *rt)
{
	mxml_node_t *xml;
	mxml_node_t *data;
	FILE		*fp;
	int			i;

	i = -1;
	xml = mxmlNewXML("1.0");
	data = mxmlNewElement(xml, "RT");
	while (++i < scene->count_obj)
		ft_write_to_xml(scene, data, &rt->filters.obj_movement[i], &i);
	i = -1;
	while (++i < scene->count_light)
		ft_write_light(scene->light[i], data);
	i = -1;
	while (++i < scene->count_neg_obj)
		ft_write_neg(scene->neg_obj[i], data);
	ft_write_cam(pov, data);
	if ((fp = fopen(name_file, "w")) == NULL)
		return (error_message(RED"XML: file to save can't open"COLOR_OFF));
	mxmlSaveFile(xml, fp, whitespace_cb);
	mxmlDelete(xml);
	fclose(fp);
	return (0);
}
