/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 18:47:41 by apavlov           #+#    #+#             */
/*   Updated: 2019/09/26 18:56:21 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

cl_double2	*reverse_matrix_2x2(cl_double2 *src)
{
	cl_double2	col1;
	cl_double2	col2;
	double		det;

	col1 = src[0];
	col2 = src[1];
	det = det_matrix_2x2(src);
	src[0].s[0] = col2.s[1] / det;
	src[1].s[0] = -col2.s[0] / det;
	src[0].s[1] = -col1.s[1] / det;
	src[1].s[1] = col1.s[0] / det;
	return (src);
}

double		det_matrix_2x2(cl_double2 *src)
{
	return (src[0].s[0] * src[1].s[1] - src[1].s[0] * src[0].s[1]);
}

cl_double3	add_double3(cl_double3 a, cl_double3 b)
{
	return ((cl_double3){{a.s[0] + b.s[0], a.s[1] + b.s[1], a.s[2] + b.s[2]}});
}

cl_double3	minus_double3(cl_double3 a, cl_double3 b)
{
	return ((cl_double3){{a.s[0] - b.s[0], a.s[1] - b.s[1], a.s[2] - b.s[2]}});
}

cl_double3	increase_double3(cl_double3 a, double multi)
{
	return ((cl_double3){{a.s[0] * multi, a.s[1] * multi, a.s[2] * multi}});
}
