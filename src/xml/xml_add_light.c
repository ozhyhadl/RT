/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_add_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhyhadl <ozhyhadl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 18:56:10 by ozhyhadl          #+#    #+#             */
/*   Updated: 2019/09/27 18:51:29 by ozhyhadl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

static int	ft_is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

void		ft_creat_light(t_scene *scene, int l)
{
	scene->light[l].type_num = POINT;
	scene->light[l].intensity = (cl_double3){{0.1, 0.1, 0.1}};
	scene->light[l].v = (cl_double3){{0, 0, 0}};
}

int			ft_add_type_light(t_scene *scene, int l, char *str)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	if (str == NULL)
		return (error_message(RED"XML : empty tag <type> "COLOR_OFF));
	while (str[i] != '\0')
	{
		if (ft_is_space(str[i]))
			i++;
		else
			str[n++] = (char)str[i++];
	}
	str[n] = str[i];
	if (ft_strequ(str, "point"))
		scene->light[l].type_num = POINT;
	else if (ft_strequ(str, "ambient"))
		scene->light[l].type_num = AMBIENT;
	else if (ft_strequ(str, "direct"))
		scene->light[l].type_num = DIRECT;
	else
		return (error_message(RED"XML : invalid type light "COLOR_OFF));
	return (0);
}
