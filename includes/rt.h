/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhyhadl <ozhyhadl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 13:39:54 by apavlov           #+#    #+#             */
/*   Updated: 2019/09/11 17:04:30 by ozhyhadl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CL_SILENCE_DEPRECATION
#  define CL_SILENCE_DEPRECATION
#endif

#ifndef RT_H
# define RT_H

# include <fcntl.h>

# include "../libft/libft.h"
# ifdef __APPLE__
#  include "../frameworks/SDL2.framework/Headers/SDL.h"
#  include "../frameworks/SDL2_image.framework/Headers/SDL_image.h"
#  include "../frameworks/mxml-3.0/include/mxml.h" // Add path mxml header ++
#  include <OpenCL/opencl.h>
# else
#  include <SDL2/SDL.h>
#  include <CL/cl.h>
#  include <SDL2/SDL_image.h>
# endif
# include <stdio.h>
# include "terminal_colors.h"



# define DEVICE_TYPE	CL_DEVICE_TYPE_GPU
# ifdef __APPLE__
#  define WIN_WIDTH	1600
#  define WIN_HEIGHT	1200
# else
#  define WIN_WIDTH	1200
#  define WIN_HEIGHT	800
# endif
# define MAX_OBJ_COUNT 20
# define MAX_LIGHTING_COUNT 10
# define RGB(v) (((int)v[0] << 16) + ((int)v[1] << 8) + (int)v[2])
# define MIN(a,b)				(((a) < (b)) ? (a) : (b))
# define MAX(a,b)				(((a) > (b)) ? (a) : (b))
# define CLAMP(a, mi,ma)		MIN(MAX(a,mi),ma)

# define D	0.1
# define VW	(1.155 * D)
# define VH	(VW * WIN_HEIGHT / WIN_WIDTH)

# define BIG_VALUE 9e9

typedef	struct s_fig	t_fig;
typedef	struct s_sdl	t_sdl;
typedef	struct s_scene	t_scene;
typedef	struct s_rt		t_rt;
typedef	struct s_pov	t_pov;

enum	e_fig
{
	SPHERE = 1, PLANE, CONE, CYLIN
};
enum	e_light
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
}				t_cone_data;

typedef struct	s_cylin_data
{
	cl_double3	dir;
	cl_double3	dot;
	cl_double	radius;
}				t_cylin_data;

typedef union	u_shape
{
	t_sphere_data	sphere;
	t_cone_data		cone;
	t_plane_data	plane;
	t_cylin_data	cylin;
}				t_shape;

struct	s_fig
{
	cl_int		fig_type;
	t_shape		shape;

	cl_double3	color;
	//cl_int		text_no;
	cl_int		specular;
	cl_double	reflective;
	cl_double	trans;
	cl_double3	rotation;
	cl_double	ior;
	cl_int		text_no;
	cl_int		normal_map_no;
};

struct	s_sdl
{
	SDL_Window	*win;
	SDL_Surface	*win_sur;
};

struct	s_pov
{
	cl_double3	coord;
	cl_double3	dir;
	double		cx;
	double		cy;
	double		sx;
	double		sy;
	cl_double	d;
	cl_double	vh;
	cl_double	vw;
};

typedef struct	s_light
{
	cl_int		type_num;
	cl_double3	intensity;
	cl_double3	v;
}				t_light;

struct	s_scene
{
	cl_int		count_obj;
	t_fig		obj[MAX_OBJ_COUNT];
	cl_int		count_light;
	t_light		light[MAX_LIGHTING_COUNT];
};

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

	cl_mem				texture_mem;
	cl_mem				bump_mem;

	size_t				global_size;
	size_t				local_size;

	cl_uint				*pixels_to_read_into;
}				t_cl;

typedef struct	s_txt_params
{
	cl_int		w;
	cl_int		h;
}				t_txt_params;

typedef struct	s_envi
{
	cl_int			txt_count;
	cl_uint			*txt; //could be uint16 : rgb565. to save more space for kernel
	t_txt_params	txt_par; // must be an array for all textures
	cl_uint			*bump; //could be uint16 : blue value isnt needed. to save more space for kernel
	t_txt_params	bump_par; // must be an array for all textures
}				t_envi;

typedef struct	s_edi
{
	int		chosen_obj;
}				t_edi;


struct	s_rt
{
	t_sdl	sdl;
	t_scene	scene;
	t_pov	pov;
	t_cl	cl;
	t_envi	envi;
	t_edi	edi;
};

/*
**	CL		stuff
*/
int			init_cl(t_cl *cl);
int			create_program_and_kernels(t_cl *cl);
int			set_up_memory(t_rt *rt, t_cl *cl);
int			freed_up_memory(t_cl *cl);

/*
**	SDL		stuff
*/
int			init_sdl(t_sdl *sdl);
int			close_sdl(t_sdl *sdl);

/*
**	Friendly user stuff
*/
int			error_message(char *mess);


/*
**	Render
*/
int			render_scene(t_rt *rt);

/*
**	User
*/
int			there_will_be_loop(t_rt *rt);

/*
**	Parse
*/


/*
**	Add ++ parse xml
*/
int			ft_parse_xml(char *name_file, t_scene *scene, t_pov *pov);
int			ft_check_child(mxml_node_t *node);
int			ft_is_cam(mxml_node_t *node, t_pov *pov, int what_is);
int			ft_is_light(mxml_node_t *node, t_scene *scene, int l, int what_is);
int			ft_is_param(mxml_node_t *node, t_scene *scene, int i, int what_is);
int			ft_is_obj(const char *str, t_scene *scene, int *il, t_pov *pov);

/*
**	Add ++ create define figure and light
*/
void		ft_create_cylin(t_scene *scene, int i);
void		ft_create_cone(t_scene *scene, int i);
void		ft_create_pale(t_scene *scene, int i);
void		ft_create_spher(t_scene *scene, int i);
void		ft_creat_light(t_scene *scene, int l);

/*
**	Add ++ add_param(position, radius, normal, dir, tang, type) to figure
*/
int			add_position(const char *str, t_scene *scene, int i, const char *tag);
int			ft_add_radius(const char *str, t_scene *scene, int i);
int			ft_add_normal_dir(const char *str, t_scene *scene, int i, const char *tag);
int			ft_add_tanget(const char *str, t_scene *scene, int i);
int			ft_add_type_light(t_scene *scene, int l, char *str);

/*
**	Add ++ add_param(color, specular, reflection) to figure
*/
int			add_for_all_obj(const char *str, t_scene *scene, int i, const char *tag);
int			ft_add_rgb(const char *str, t_scene *scene, int i);
int			ft_get_3param(int i, const char *str, cl_double3 *dot, cl_double *one_dot);

/*
**	Add ++ add_param to cam
*/
void		ft_create_cam(t_pov *pov);
int			ft_add_cam_dot(const char *str, t_pov *pov);

/*
**	Add ++ xml save
*/

int			ft_xml_save(char *name_file, t_scene *scene, t_pov *pov);

# include "parse.h"
# include "mymath.h"

#endif
