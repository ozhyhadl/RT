/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yruda <yruda@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 17:34:14 by ozhyhadl          #+#    #+#             */
/*   Updated: 2019/09/28 12:27:34 by yruda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

int	ft_check_count(int o, int i, int n, int c)
{
	if (o >= MAX_OBJ_COUNT)
	{
		ft_putstr(RED"XML: max obj is "COLOR_OFF);
		ft_putnbr(MAX_OBJ_COUNT);
		return (error_message(RED" SORRY !"COLOR_OFF));
	}
	if (i >= MAX_LIGHTING_COUNT)
	{
		ft_putstr(RED"XML: max light is "COLOR_OFF);
		ft_putnbr(MAX_LIGHTING_COUNT);
		return (error_message(RED" SORRY !"COLOR_OFF));
	}
	if (n >= MAX_NEGATIVE_OBJ_COUNT)
	{
		ft_putstr(RED"XML: max neg_obj is "COLOR_OFF);
		ft_putnbr(MAX_NEGATIVE_OBJ_COUNT);
		return (error_message(RED" SORRY !"COLOR_OFF));
	}
	if (c >= MAX_CUB_COUNT)
	{
		ft_putstr(RED"XML: max cub is "COLOR_OFF);
		ft_putnbr(MAX_CUB_COUNT);
		return (error_message(RED" SORRY !"COLOR_OFF));
	}
	return (0);
}

int	ft_read_xml3(mxml_node_t *son, t_rt *rt, int what_is, int *index)
{
	while (son != NULL)
	{
		if (mxmlGetElement(son) != NULL && ((ft_is_param(son, rt, \
		index[0], what_is) && ft_is_negative(son, &rt->scene, index[2], \
		what_is) && (ft_is_light(son, &rt->scene, index[1], what_is) && \
		ft_is_cam(son, &rt->pov, what_is))) || ft_check_child(son)))
			return (1);
		son = mxmlGetNextSibling(son);
	}
	return (0);
}

int	ft_read_xml2(mxml_node_t *node, t_rt *rt, int what_is, int *index)
{
	mxml_node_t	*son;

	while (node != NULL)
	{
		if (ft_check_count(index[0], index[1], index[2], index[3]))
			return (1);
		son = mxmlGetFirstChild(node);
		if (mxmlGetElement(node) != NULL && !(what_is = \
			ft_is_obj(mxmlGetElement(node), &rt->scene, index, rt)))
			return (error_message(RED"XML: Not valid tag"COLOR_OFF));
		if (ft_read_xml3(son, rt, what_is, index))
			return (1);
		if (mxmlGetElement(node) != NULL && ft_strequ(mxmlGetElement(node), \
		"rectangle") && !check_rectangle_in_plane(\
		rt->scene.obj[index[0]].shape.rectangle))
			return (error_message(RED"XML: bad rectangle"COLOR_OFF));
		node = mxmlGetNextSibling(node);
	}
	return (0);
}

int	ft_read_xml(mxml_node_t *node, t_scene *scene, t_rt *rt)
{
	int			index[4];
	int			what_is;

	index[0] = -1;
	index[1] = -1;
	index[2] = -1;
	index[3] = -1;
	what_is = 0;
	if (ft_read_xml2(node, rt, what_is, index))
		return (1);
	scene->count_obj = index[0] + 1;
	scene->count_light = index[1] + 1;
	scene->count_neg_obj = index[2] + 1;
	scene->count_cubs = index[3] + 1;
	return (0);
}
