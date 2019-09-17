/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhyhadl <ozhyhadl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 17:34:14 by ozhyhadl          #+#    #+#             */
/*   Updated: 2019/09/17 14:31:09 by ozhyhadl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int	exit_parse(mxml_node_t *tree, FILE *fp, char *str)
{
	if (str != NULL)
		error_message(str);
	fclose(fp);
	mxmlDelete(tree);
	return (1);
}

int	ft_read_xml(mxml_node_t *node, t_scene *scene, t_pov *pov)
{
	int			index[2];
	mxml_node_t	*son;
	int			what_is;

	index[0] = -1;
	index[1] = -1;
	while (node != NULL)
	{
		son = mxmlGetFirstChild(node);
		if (mxmlGetElement(node) != NULL && !(what_is = \
			ft_is_obj(mxmlGetElement(node), scene, index, pov)))
			return (error_message(RED"XML: Not valid tag"COLOR_OFF));
		while (son != NULL)
		{
			if (mxmlGetElement(son) != NULL && ((ft_is_param(son, scene, \
			index[0], what_is) && (ft_is_light(son, scene, index[1], what_is) \
			&& ft_is_cam(son, pov, what_is))) || ft_check_child(son)))
				return (1);
			son = mxmlGetNextSibling(son);
		}
		node = mxmlGetNextSibling(node);
	}
	scene->count_obj = index[0] + 1;
	scene->count_light = index[1] + 1;
	return (0);
}

int	ft_parse_xml(char *name_file, t_scene *scene, t_pov *pov)
{
	FILE		*fp;
	mxml_node_t	*tree;
	mxml_node_t	*node;

	if ((fp = fopen(name_file, "r")) == NULL)
		return (error_message(RED"Сould not open file"COLOR_OFF));
	tree = mxmlLoadFile(NULL, fp, MXML_OPAQUE_CALLBACK);
	if (tree == NULL)
		return (error_message(RED"Cant load XML"COLOR_OFF));
	if (!ft_strequ(mxmlGetElement(tree), \
		"?xml version=\"1.0\" encoding=\"utf-8\"?"))
		return (exit_parse(tree, fp, RED\
		"XML: invalid version & encoding"COLOR_OFF));
	node = mxmlGetFirstChild(tree);
	node = mxmlGetNextSibling(node);
	if (!ft_strequ(mxmlGetElement(node), "RT"))
		return (exit_parse(tree, fp, RED"Use first tag <RT> </RT>"COLOR_OFF));
	ft_add_w_h(pov, node);
	node = mxmlGetFirstChild(node);
	if (ft_read_xml(node, scene, pov))
		return (exit_parse(tree, fp, NULL));
	fclose(fp);
	mxmlDelete(tree);
	return (0);
}
