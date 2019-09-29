/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhyhadl <ozhyhadl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 23:22:16 by ozhyhadl          #+#    #+#             */
/*   Updated: 2019/09/28 00:18:55 by ozhyhadl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

int	exit_parse(mxml_node_t *tree, FILE *fp, char *str)
{
	if (str != NULL)
		error_message(str);
	fclose(fp);
	mxmlDelete(tree);
	return (1);
}

int	ft_parse_xml(char *name_file, t_scene *scene, t_pov *pov, t_rt *rt)
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
	if (ft_read_xml(node, scene, rt))
		return (exit_parse(tree, fp, NULL));
	fclose(fp);
	mxmlDelete(tree);
	return (0);
}
