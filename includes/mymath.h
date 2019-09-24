/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mymath.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 22:50:26 by ozhyhadl          #+#    #+#             */
/*   Updated: 2019/09/22 18:57:00 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYMATH_H
# define MYMATH_H

# include "rt.h"

#define ROTATION_SPEED	0.05	
#define TRANSLATE_SPEED 0.1

cl_double3		rotate_z(cl_double3 v, double angle);
cl_double3		rotate_x(cl_double3 v, double angle);
cl_double3		rotate_y(cl_double3 v, double angle);

cl_double3	ft_rotate_camera(cl_double3 direction, t_pov pov);

cl_double3	add_double3(cl_double3 a, cl_double3 b);
cl_double3	minus_double3(cl_double3 a, cl_double3 b);
cl_double3	increase_double3(cl_double3 a, double multi);

double		det_matrix_2x2(cl_double2 *src);
cl_double2	*reverse_matrix_2x2(cl_double2 *src);

double		vector_len(cl_double3 a);
t_rotation_matrix build_rotation_matrix_form_angles(cl_double3 rot);
t_rotation_matrix build_rotation_matrix_for_cylin(cl_double3 dir);
cl_double3	ft_normalize(cl_double3 a);

cl_double3	ft_rotate_reverse_camera(cl_double3 direction, t_pov pov);

#endif