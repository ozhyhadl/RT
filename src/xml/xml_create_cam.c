/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_create_cam.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhyhadl <ozhyhadl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 12:22:48 by ozhyhadl          #+#    #+#             */
/*   Updated: 2019/09/11 17:10:37 by ozhyhadl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

void	ft_create_cam(t_pov *pov)
{
	pov->d = D;
	pov->vw = VW;
	pov->vh = VH;
	pov->coord = (cl_double3){{0, 0, 0}};
	pov->dir = (cl_double3){{0, 0, 0}};
}

int		ft_add_cam_dot(const char *str, t_pov *pov)
{
	cl_double3 dot;

	if (ft_get_3param(3, str, &dot, NULL))
		pov->coord = (cl_double3)dot;
	else
		return (1);
	return (0);
}
