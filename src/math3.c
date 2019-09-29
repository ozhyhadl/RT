/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 18:48:24 by apavlov           #+#    #+#             */
/*   Updated: 2019/09/26 18:58:22 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

double			dot(cl_double3 a, cl_double3 b)
{
	return (a.s[0] * b.s[0] + a.s[1] * b.s[1] + a.s[2] * b.s[2]);
}

double			vector_len(cl_double3 a)
{
	return (sqrt(a.s[0] * a.s[0] + a.s[1] * a.s[1] + a.s[2] * a.s[2]));
}

cl_double3		ft_normalize(cl_double3 a)
{
	double	lenght;

	lenght = vector_len(a);
	return ((cl_double3){{a.s[0] / lenght, a.s[1] / lenght, a.s[2] / lenght}});
}

cl_double3		rotate_x(cl_double3 v, double angle)
{
	double y;
	double c;
	double s;

	y = v.s[1];
	c = cos(angle);
	s = sin(angle);
	v.s[1] = y * c - s * v.s[2];
	v.s[2] = y * s + c * v.s[2];
	return (v);
}

cl_double3		rotate_y(cl_double3 v, double angle)
{
	double x;
	double c;
	double s;

	x = v.s[0];
	c = cos(angle);
	s = sin(angle);
	v.s[0] = x * c + s * v.s[2];
	v.s[2] = -x * s + c * v.s[2];
	return (v);
}
