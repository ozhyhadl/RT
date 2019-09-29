/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mymath.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yruda <yruda@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 22:50:26 by ozhyhadl          #+#    #+#             */
/*   Updated: 2019/09/27 21:44:16 by yruda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYMATH_H
# define MYMATH_H

# include "rt.h"

# define ROTATION_SPEED	-0.002
# define TRANSLATE_SPEED 0.1

cl_double3			rotate_z(cl_double3 v, double angle);
cl_double3			rotate_x(cl_double3 v, double angle);
cl_double3			rotate_y(cl_double3 v, double angle);
cl_double3			rotate_xyz(cl_double3 v, cl_double3 a);

cl_double3			new_basis(cl_double3 point, t_rotation_matrix m);
cl_double3			transpone_basis(cl_double3 point, t_rotation_matrix m);
t_rotation_matrix	rotate_matrix_of_rotation(t_rotation_matrix m,
					cl_double3 angles);
cl_double3			find_angles_from_rotation_matrix(t_rotation_matrix rm);
t_rotation_matrix	build_rotation_matrix_for_rectangles(cl_double3 normal,
					t_rectangle_data r);

cl_double3			add_double3(cl_double3 a, cl_double3 b);
cl_double3			minus_double3(cl_double3 a, cl_double3 b);
cl_double3			increase_double3(cl_double3 a, double multi);
double				dot(cl_double3 a, cl_double3 b);
cl_double3			cross(cl_double3 a, cl_double3 b);

double				det_matrix_2x2(cl_double2 *src);
cl_double2			*reverse_matrix_2x2(cl_double2 *src);

double				vector_len(cl_double3 a);
t_rotation_matrix	build_rotation_matrix_form_angles(cl_double3 rot);
t_rotation_matrix	build_rotation_matrix_for_dir(cl_double3 dir);
cl_double3			ft_normalize(cl_double3 a);

int					check_rectangle_in_plane(t_rectangle_data rectange);

#endif
