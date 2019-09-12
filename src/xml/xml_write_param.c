/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_write_param.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhyhadl <ozhyhadl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 22:13:18 by ozhyhadl          #+#    #+#             */
/*   Updated: 2019/09/12 22:37:08 by ozhyhadl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

char	*double_to_char(double nbr)
{
	char	*first;
	char	*second;
	char	*tmp;

	first = ft_itoa((int)nbr);
	nbr -= (long long)nbr;
	tmp = first;
	if (nbr != 0)
	{
		first = ft_strjoin(first, ".");
		ft_strdel(&tmp);
	}
	while (nbr != 0.0)
	{
		nbr = round(nbr * 10.0);
		second = ft_itoa((int)nbr);
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
	ft_write_param((cl_double)fig.normal_map_no, node, "bump");
}
