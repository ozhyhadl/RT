/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel.hh                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 15:30:22 by apavlov           #+#    #+#             */
/*   Updated: 2019/09/28 15:30:25 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KERNEL_H
# define KERNEL_H

# define MAX_OBJ_COUNT 20
# define MAX_LIGHTING_COUNT 10
# define MAX_NEGATIVE_OBJ_COUNT 5
# define MAX_CUB_COUNT 5

__constant double random[100] = {-0.363205, -0.218511, 0.192709, 0.448668, \
		-0.175750, 0.095103, -0.446748, -0.941968, 0.638122, 0.169040, -0.852021, \
		-0.551432, -0.845788, 0.630999, 0.495960, 0.184360, 0.508963, -0.088337, \
		-0.578247, -0.212776, -0.868777, 0.515795, -0.260676, 0.944700, -0.889511, \
		-0.011554, 0.382379, -0.389282, -0.654632, 0.069955, -0.846122, -0.017837, \
		0.851444, 0.346587, -0.569168, -0.053453, -0.829163, -0.015916, 0.004579, \
		0.808959, -0.846876, 0.152557, -0.742473, -0.692664, -0.216444, 0.753487, \
		0.491696, -0.707481, -0.334850, 0.913450, 0.079743, -0.203628, 0.429245, \
		0.819067, -0.258927, 0.539734, -0.192487, -0.876549, -0.849548, 0.152881, \
		0.193406, -0.695670, -0.864956, 0.044850, 0.650917, -0.434125, 0.991397, \
		0.821753, 0.549959, -0.004024, 0.630712, 0.703083, -0.851467, 0.888239, \
		-0.989581, -0.067911, 0.641726, 0.502115, 0.224608, -0.693124, 0.415565, \
		-0.695649, 0.103249, -0.155190, -0.876582, 0.844321, -0.615456, -0.069070, \
		0.967772, -0.465004, -0.916189, 0.161179, -0.160674, -0.781145, -0.793971, \
		-0.509758, -0.215270, -0.802574, -0.688004, -0.665311};


__constant double EPSILON = 0.00001;
__constant double BIG_VALUE = 9e9;
__constant double3 BACKGROUND_COLOR =  ((double3)(0.f, 0.f, 0.f));
__constant double	MINIMUM_INTENSITY = 0.01;
__constant int tree_nodes =	31;
__constant double	PI = 3.14159265359;

enum	e_fig
{
	SPHERE = 1, PLANE, CONE, CYLIN, RECTANGLE, TRIANGLE, DISK, ELLIPSE, TORUS
};
enum	e_light
{
	AMBIENT = 1, DIRECT, POINT
};

typedef struct	s_sphere_data
{
	double3				cent;
	double				radius;
}				t_sphere_data;

typedef struct	s_plane_data
{
	double3				normal;
	double3				dot;
}				t_plane_data;

typedef struct	s_cone_data
{
	double3				vertex;
	double3				dir;
	double				tangent;
	double				mmax;
	double				mmin;
}				t_cone_data;

typedef struct	s_rectangle_data
{
	double3				v0;
	double3				v1;
	double3				v2;
	double3				v3;
}				t_rectangle_data;

typedef struct	s_disk_data
{
	double3				cent;
	double3 			normal;
	double				radius;
}				t_disk_data;

typedef struct	s_torus_data
{
	double3	cent;
	double3	dir;
	double	big_radius;
	double	inner_radius;
}				t_torus_data;

typedef struct	s_ellipse_data
{
	double3	cent;
	double	dist_btwn_cent;
	double3	dir;
	double	radius_sum;
}				t_ellipse_data;

typedef struct	s_triangle_data
{
	double3				v0;
	double3				v1;
	double3				v2;
}				t_triangle_data;

typedef struct	s_rotation_matrix
{
	double3				e1;
	double3				e2;
	double3				e3;
}				t_rotation_matrix;

typedef struct	s_cube
{
	int			no;
	double3		cent;
	double3		rotation;
	t_rotation_matrix	rotation_matrix;
	double		dist;
}				t_cube;

typedef struct	s_cylin_data
{
	double3				dir;
	double3				dot;
	double				radius;
	double				mmax;
	double				mmin;
}				t_cylin_data;

typedef union	u_shape
{
	t_sphere_data		sphere;
	t_cone_data			cone;
	t_plane_data		plane;
	t_cylin_data		cylin;
	t_rectangle_data	rectangle;
	t_triangle_data		triangle;
	t_torus_data		torus;
	t_ellipse_data		ellipse;
	t_disk_data			disk;
}				t_shape;

typedef struct	s_fig
{
	int					fig_type;
	t_shape				shape;

	double3				color;
	int					color_index;
	int					specular;
	double				reflective;
	double				trans;
	double3				rotation;
	t_rotation_matrix	rotation_martix;
	double				ior;
	int					noise;
	int					text_no;
	int					normal_map_no;
	int					transparancy_map_no;
	double2				txt_offset;
	double2				txt_scale;

	int					cutting;
	t_plane_data		cutting_plane;
	int					complex_fig;
}				t_fig;

typedef struct	s_pov
{
	double3				coord;
	double3				dir;
	t_rotation_matrix	pov_rm;
	double				d;
	double				vh;
	double				vw;
	int					w;
	int					h;
}				t_pov;

typedef struct	s_raytrace_tree
{
	double			part_of_primary_ray;
	double3			start;
	double3			dir;
	double			min_range;
	double			max_range;
}				t_raytrace_tree;

typedef struct	s_obj_and_dist
{
	int				obj;
	double			dist;
}				t_obj_and_dist;

typedef struct	s_light
{
	int				type_num;
	double3			intensity;
	double3			v;
}				t_light;

typedef struct	s_negative_fig
{
	int					fig_type;
	t_shape				shape;
	t_rotation_matrix	rotation_matrix;
}				t_negative_fig;

typedef struct	s_scene
{
	int					count_obj;
	t_fig				obj[MAX_OBJ_COUNT];
	int					count_light;
	t_light				light[MAX_LIGHTING_COUNT];
	int					count_neg_obj;
	t_negative_fig		neg_obj[MAX_NEGATIVE_OBJ_COUNT];
	t_cube				cubs[MAX_CUB_COUNT];
	int					count_cubs;
}				t_scene;

typedef struct	s_txt_params
{
	int					w;
	int					h;
	int					start_pos;
}				t_txt_params;

double3		ray_trace(double3 eye, double3 dir, __global t_scene *scene, double min_range, double max_range, __global uint *texture, __global t_txt_params *txt_params, float *zbuff);
double3		canvas_to_viewport(int x, int y, int w, int h, t_pov pov);
double3		calculate_light(__global t_scene *scene, double3 eye, \
						double3 dir, double3 normal, double3 intersect_point, \
						t_fig fig, __global uint *texture, __global t_txt_params *txt_params, double2 texture_coords);

double3		get_intersity_after_shadow_rays(double3 intersect_point, double3 light_dir, \
										__global t_scene *scene, double min_range, \
										double max_range, __global t_light *light);
double3		refract_ray(double3 prim_ray, double3 normal, double ior2_new);
double3		reflected_ray(double3 normal, double3 prim_ray);
double		fresnel(double3 prim_ray, double3 normal, double n1);
double3		beers_law(double distance, double3 obj_absorb);

double3		new_basis(double3 point, t_rotation_matrix m);

double2		intersect_sphere(double3 eye, double3 dir, t_sphere_data sphere);
double2		intersect_plane(double3 eye, double3 dir, t_plane_data plane);
double2		intersect_cylin(double3 eye, double3 dir, t_cylin_data cylin);
double2		intersect_ellipse(double3 eye, double3 dir, t_ellipse_data ellipse);
double2		intersect_cone(double3 eye, double3 dir, t_cone_data cone);
double2		intersect_triangle(double3 eye, double3 dir, t_triangle_data triangle);
double2		intersect_rectangle(double3 eye, double3 dir, t_rectangle_data rectangle);
double2		intersect_disk(double3 eye, double3 dir, t_disk_data disk);
double3		get_obj_dot(t_fig fig);

double2		cut_result_with_personal_planes(double2 prev, t_fig fig, double3 eye, double3 dir);
double2		cut_with_sphere(double2 prev, double3 *point, t_sphere_data sphere);
double2		cut_with_plane(double2 prev, double3 *point, t_plane_data plane);
double2		cut_with_cylin(double2 prev, double3 *point, t_negative_fig cylin);
double2		cut_result_with_negative_obj(double2 prev, __global t_scene *scene, double3 eye, double3 dir);
void		cut_4_roots(double3 eye, double3 dir, double4 res, \
								__global t_scene *scene, int *closest_obj, \
								double *closest_dist, double mini, \
								double maxi, t_fig fig, int fig_no);

double3			calculate_normal(t_fig fig, double3 intersect_point, t_raytrace_tree curr_node);
t_obj_and_dist	check_closest_inter(double3 eye, double3 dir, \
										__global t_scene *scene, \
										double mini, double max);

double3		uint_to_double3(uint a);
double3		trim_color(double3 color);
uint		color_to_canvas(double3 color);

double2		get_sperical_coords(double3 intersect_point, t_fig data);
double2		get_plane_coords(double3 intersect_point, t_fig data);
double2		get_cylin_coords(double3 intersect_point, t_fig data);
double2		get_rectangle_coords(double3 intersect_point, t_fig data);
double2		get_triangle_coords(double3 intersect_point, t_fig data);
double2		get_disk_coords(double3 intersect_point, t_fig data);
double2		get_cone_coords(double3 intersect_point, t_fig data);
double3		new_basis(double3 point, t_rotation_matrix m);
double2		get_texture_space_coords(double3 intersect_point, t_fig data);
uint		get_texture_pixel(double2 coord, __global uint *texture, t_txt_params params, int no);

void		swap(double* a, double*b);
double		line_point(double start, double end, double p);

double3		ft_noise	(double2 coords);
double3		ft_noise1 	(double2 coords);
double3		ft_noise2 	(double2 coords);
double3		ft_noise3 	(double2 coords);
double 		noise(int x, int y);
double 		cos_interpole(double a, double b, double x);

#endif
