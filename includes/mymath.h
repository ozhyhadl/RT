/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mymath.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhyhadl <ozhyhadl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 22:50:26 by ozhyhadl          #+#    #+#             */
/*   Updated: 2019/09/16 19:56:21 by ozhyhadl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYMATH_H
# define MYMATH_H

# include "rt.h"

#define ROTATION_SPEED	0.05	
#define TRANSLATE_SPEED 0.1

cl_double3	ft_rotate_camera(cl_double3 direction, t_pov pov);
cl_double3	add_double3(cl_double3 a, cl_double3 b);
double		vector_len(cl_double3 a);
t_rotation_matrix build_rotation_matrix_form_angles(cl_double3 rot);
cl_double3	ft_normalize(cl_double3 a);

cl_double3	ft_rotate_minus_camera(cl_double3 direction, t_pov pov);

#endif