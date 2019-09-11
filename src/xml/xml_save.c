/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_save.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhyhadl <ozhyhadl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 13:32:14 by ozhyhadl          #+#    #+#             */
/*   Updated: 2019/09/11 21:49:21 by ozhyhadl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int		is_frst_ltag(const char *str)
{
	if (ft_strequ(str, "spher") || ft_strequ(str, "plane") || \
		ft_strequ(str, "cone") || ft_strequ(str, "cylin") || \
			ft_strequ(str, "light") || ft_strequ(str, "cam"))
		return (1);
	return (0);
}
int		is_param_ltag(const char *str)
{
	if (ft_strequ(str, "centre") || ft_strequ(str, "radius") || \
		ft_strequ(str, "RGB") || ft_strequ(str, "transparency") || \
		ft_strequ(str, "specular") || ft_strequ(str, "texture") || \
		ft_strequ(str, "vertex") || ft_strequ(str, "angle") || \
		ft_strequ(str, "type") || ft_strequ(str, "position") || \
		ft_strequ(str, "dot") || ft_strequ(str, "normal") || \
		ft_strequ(str, "intensity") || ft_strequ(str, "reflective") || \
		ft_strequ(str, "dir") || ft_strequ(str, "specular"))
		return (1);
	return (0);
}

const char *whitespace_cb(mxml_node_t *node, int where)
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

char	*double_to_char(double nbr)
{
	int		i;
	char	*first;
	char	*second;
	char	*tmp;
	char c;

	first = ft_itoa((int)nbr);
	i = (int)nbr;
	nbr = nbr - i;
	tmp = first;
	if (nbr != 0)
	{
		first = ft_strjoin(first, ".");
		ft_strdel(&tmp);
	}
	while (nbr != 0.0)
	{
		nbr = round(nbr * 10.0);
		second = ft_itoa((int) nbr);
		tmp = first;
		first = ft_strjoin(first, second);
		ft_strdel(&tmp);
		ft_strdel(&second);
		nbr -= (long long)nbr;
	}
	return (first);
}

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

void	ft_write_all(t_fig fig, mxml_node_t *node)
{
	ft_write_3param(fig.color, node, (const char *)"RGB");
	ft_write_param(fig.trans, node, (const char *)"transparency");
	ft_write_param(fig.reflective, node, (const char *)"reflective");
	ft_write_param((cl_double)fig.specular, node, (const char *)"specular");
	ft_write_param((cl_double)fig.text_no, node, (const char *)"texture");

}

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
	ft_write_all(fig, node);
}

void	ft_write_cone(t_cone_data cone, mxml_node_t *data, t_fig fig)
{
	mxml_node_t *node;

	node = mxmlNewElement(data, "cone");
	ft_write_3param(cone.vertex, node, (const char *)"vertex");
	ft_write_3param(cone.dir, node, (const char *)"dir");
	// add tang and tnas to angle 
}
void	ft_write_to_xml(t_fig fig, mxml_node_t *data)
{

	if (fig.fig_type == SPHERE)
		ft_write_spher(fig.shape.sphere, data, fig);
	if (fig.fig_type == PLANE)
		ft_write_plane(fig.shape.plane, data, fig);
	if (fig.fig_type == CYLIN)
		ft_write_cylin(fig.shape.cylin, data, fig);
}

int		ft_xml_save(char *name_file, t_scene *scene, t_pov *pov)
{
	mxml_node_t *xml;    /* <?xml ... ?> */
	mxml_node_t *data;   /* <data> */
	FILE 		*fp;
	t_fig		fig;
	int			i;

	i = 0;
	xml = mxmlNewXML("1.0");
	data = mxmlNewElement(xml, "RT");
	while (i < scene->count_obj)
	{
		fig = scene->obj[i];
		ft_write_to_xml(fig, data);
		i++;
	}
	if ((fp = fopen(name_file, "w")) == NULL)
		return (error_message(RED"XML: file to save can't open"COLOR_OFF));
	mxmlSaveFile(xml, fp, whitespace_cb);
	fclose(fp);
	return (0);
}