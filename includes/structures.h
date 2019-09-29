/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yruda <yruda@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 22:00:09 by yruda             #+#    #+#             */
/*   Updated: 2019/09/27 22:08:27 by yruda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "rt.h"

typedef	struct s_fig	t_fig;
typedef	struct s_sdl	t_sdl;
typedef	struct s_scene	t_scene;
typedef	struct s_rt		t_rt;
typedef	struct s_pov	t_pov;
typedef	double	t_vector __attribute__((vector_size(sizeof(double)*4)));

enum			e_but
{
	SENT = 1, SAVE, SCREEN
};

enum			e_fig
{
	SPHERE = 1, PLANE, CONE, CYLIN, RECTANGLE, TRIANGLE, DISK, ELLIPSE, TORUS
};
enum			e_light
{
	AMBIENT = 1, DIRECT, POINT
};

typedef struct	s_sphere_data
{
	cl_double3	cent;
	cl_double	radius;
}				t_sphere_data;

typedef struct	s_plane_data
{
	cl_double3	normal;
	cl_double3	dot;
}				t_plane_data;

typedef struct	s_cone_data
{
	cl_double3	vertex;
	cl_double3	dir;
	cl_double	tangent;
	cl_double	mmax;
	cl_double	mmin;
}				t_cone_data;

typedef struct	s_rectangle_data
{
	cl_double3	v0;
	cl_double3	v1;
	cl_double3	v2;
	cl_double3	v3;
}				t_rectangle_data;

typedef struct	s_disk_data
{
	cl_double3	cent;
	cl_double3	normal;
	cl_double	radius;
}				t_disk_data;

typedef struct	s_torus_data
{
	cl_double3	cent;
	cl_double3	dir;
	cl_double	big_radius;
	cl_double	inner_radius;
}				t_torus_data;

/*
**	dist_btwn_cent > 0
**	radius_sum > 0
*/

typedef struct	s_ellipse_data
{
	cl_double3	cent;
	cl_double	dist_btwn_cent;
	cl_double3	dir;
	cl_double	radius_sum;
}				t_ellipse_data;

typedef struct	s_triangle_data
{
	cl_double3	v0;
	cl_double3	v1;
	cl_double3	v2;
}				t_triangle_data;

typedef struct	s_cylin_data
{
	cl_double3	dir;
	cl_double3	dot;
	cl_double	radius;
	cl_double	mmax;
	cl_double	mmin;
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

typedef struct	s_rotation_matrix
{
	cl_double3		e1;
	cl_double3		e2;
	cl_double3		e3;
}				t_rotation_matrix;

typedef struct	s_cube
{
	cl_int				no;
	cl_double3			cent;
	cl_double3			rotation;
	t_rotation_matrix	rotation_matrix;
	cl_double			dist;
}				t_cube;

/*
**	figure's parametres:
**	specular - (-1) is off; [0 - 1000]
**	reflective - [0 - 1]
**	trans - transparency [0 - 1]
**	rotation - rotation of the texture
**	ior - Index of refraction [1.0004 - 2.0] or [MIN_IOR - MAX_IOR]
**	cutting - if cutting = 0, then no cutting plane
**	text_no - if (-1), then no texture
**	complex_fig - if (1), then fig is a part of the complex figure
*/

struct			s_fig
{
	cl_int				fig_type;
	t_shape				shape;

	cl_double3			color;
	cl_int				color_index;
	cl_int				specular;
	cl_double			reflective;
	cl_double			trans;
	cl_double3			rotation;
	t_rotation_matrix	rotation_martix;
	cl_double			ior;
	cl_int				noise;
	cl_int				text_no;
	cl_int				normal_map_no;
	cl_int				transparancy_map_no;
	cl_double2			txt_offset;
	cl_double2			txt_scale;

	cl_int				cutting;
	t_plane_data		cutting_plane;
	cl_int				complex_fig;
};

struct			s_sdl
{
	SDL_Window	*win;
	SDL_Surface	*win_sur;
};

struct			s_pov
{
	cl_double3			coord;
	cl_double3			dir;
	t_rotation_matrix	pov_rm;
	cl_double			d;
	cl_double			vh;
	cl_double			vw;
	cl_int				w;
	cl_int				h;
};

typedef struct	s_light
{
	cl_int		type_num;
	cl_double3	intensity;
	cl_double3	v;
}				t_light;

/*
**	rotation_matrix is only for cylinder
*/

typedef struct	s_negative_fig
{
	cl_int				fig_type;
	t_shape				shape;
	t_rotation_matrix	rotation_matrix;
}				t_negative_fig;

struct			s_scene
{
	cl_int			count_obj;
	t_fig			obj[MAX_OBJ_COUNT];
	cl_int			count_light;
	t_light			light[MAX_LIGHTING_COUNT];
	cl_int			count_neg_obj;
	t_negative_fig	neg_obj[MAX_NEGATIVE_OBJ_COUNT];
	t_cube			cubs[MAX_CUB_COUNT];
	cl_int			count_cubs;
};

/*
**	t_cl contains kernels and memory objects
*/

typedef struct	s_cl
{
	cl_device_id		device_id;
	cl_uint				device_count;
	cl_platform_id		platform_id;
	cl_uint				platform_count;
	cl_context			context;
	cl_command_queue	command_queue;
	cl_program			program;

	cl_kernel			rt_kernel;
	cl_kernel			click_kernel;

	cl_mem				scene_mem;
	cl_mem				pixel_ptr;
	cl_mem				zbuff;
	cl_mem				texture_mem;
	cl_mem				txt_param_mem;
	cl_mem				id_obj;

	size_t				global_size;
	size_t				local_size;
}				t_cl;

typedef struct	s_txt_params
{
	cl_int		w;
	cl_int		h;
	cl_int		start_pos;
}				t_txt_params;

/*
**	t_envi:
**	txt_count - number of textures
**	textures_size - sumary size of all textures
**	txt_par - w, h and start point for each texture in txt array
*/

typedef struct	s_envi
{
	cl_int			txt_count;
	cl_uint			*txt;
	cl_int			textures_size;
	t_txt_params	txt_par[MAX_TEXTURE_COUNT];
}				t_envi;

typedef struct	s_edi
{
	int		chosen_obj;
}				t_edi;

typedef struct	s_button
{
	int			type;
	SDL_Surface	*image;
	SDL_Rect	offset;
	int			available;
}				t_button;

typedef struct	s_obj_movement
{
	int			move;
	cl_double3	dir;
}				t_obj_movement;

typedef struct	s_filters
{
	int				motion;
	cl_double3		*colors;
	cl_uint			*buff;
	cl_float		*zbuff;
	t_obj_movement	obj_movement[MAX_OBJ_COUNT];
	int				index_filter;
	int				info;
	SDL_Surface		*image;
}				t_filters;

struct			s_rt
{
	t_sdl		sdl;
	t_scene		scene;
	t_pov		pov;
	t_cl		cl;
	t_envi		envi;
	t_filters	filters;
	t_edi		edi;
	t_button	butt[COUNT_BUTT];
};

#endif
