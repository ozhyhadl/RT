/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 13:49:51 by apavlov           #+#    #+#             */
/*   Updated: 2019/09/26 18:56:10 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

t_rotation_matrix	build_rotation_matrix_for_dir(cl_double3 dir)
{
	t_rotation_matrix	rm;

	rm.e3 = dir;
	if (rm.e3.s[2] == 0 && rm.e3.s[1] != 0)
		rm.e1 = ft_normalize((cl_double3){{1, 0, 0}});
	else if (rm.e3.s[2] == 0 && rm.e3.s[1] == 0)
		rm.e1 = ft_normalize((cl_double3){{0, 0, 1}});
	else
	{
		rm.e1 = ft_normalize((cl_double3){{1, 1, 0}});
		rm.e1.s[2] = -(rm.e3.s[0] * rm.e1.s[0] + \
						rm.e3.s[1] * rm.e1.s[1]) / rm.e3.s[2];
	}
	rm.e2 = cross(rm.e3, rm.e1);
	rm.e1 = ft_normalize(rm.e1);
	rm.e2 = ft_normalize(rm.e2);
	rm.e3 = ft_normalize(rm.e3);
	return (rm);
}

cl_double3			new_basis(cl_double3 point, t_rotation_matrix m)
{
	cl_double3		res;

	res.s[0] = m.e1.s[0] * point.s[0] + m.e1.s[1] * \
								point.s[1] + m.e1.s[2] * point.s[2];
	res.s[1] = m.e2.s[0] * point.s[0] + m.e2.s[1] * \
								point.s[1] + m.e2.s[2] * point.s[2];
	res.s[2] = m.e3.s[0] * point.s[0] + m.e3.s[1] * \
								point.s[1] + m.e3.s[2] * point.s[2];
	return (res);
}

cl_double3			transpone_basis(cl_double3 point, t_rotation_matrix m)
{
	cl_double3		res;

	res.s[0] = m.e1.s[0] * point.s[0] + m.e2.s[0] * \
								point.s[1] + m.e3.s[0] * point.s[2];
	res.s[1] = m.e1.s[1] * point.s[0] + m.e2.s[1] * \
								point.s[1] + m.e3.s[1] * point.s[2];
	res.s[2] = m.e1.s[2] * point.s[0] + m.e2.s[2] * \
								point.s[1] + m.e3.s[2] * point.s[2];
	return (res);
}

cl_double3			find_angles_from_rotation_matrix(t_rotation_matrix rm)
{
	cl_double3		res;

	res.s[1] = asin(-rm.e3.s[0]);
	res.s[0] = atan2(rm.e3.s[1], rm.e3.s[2]);
	res.s[2] = atan2(rm.e2.s[0], rm.e2.s[0]);
	return (res);
}

t_rotation_matrix	rotate_matrix_of_rotation(t_rotation_matrix m, \
										cl_double3 angles)
{
	m.e1 = rotate_xyz(m.e1, angles);
	m.e2 = rotate_xyz(m.e2, angles);
	m.e3 = rotate_xyz(m.e3, angles);
	return (m);
}
