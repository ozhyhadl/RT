/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhyhadl <ozhyhadl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 13:39:54 by apavlov           #+#    #+#             */
/*   Updated: 2019/09/17 14:13:00 by ozhyhadl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CL_SILENCE_DEPRECATION
#  define CL_SILENCE_DEPRECATION
#endif

#ifndef CL_USE_DEPRECATED_OPENCL_1_2_APIS
# define CL_USE_DEPRECATED_OPENCL_1_2_APIS
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
#  include <mxml.h>
# endif
# include <stdio.h>
# include "terminal_colors.h"



# define DEVICE_TYPE	CL_DEVICE_TYPE_CPU
# ifdef __APPLE__
# define WIN_WIDTH	800
# define WIN_HEIGHT	600
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
# define AIR_IOR 1.00029;
# define D	0.1


# define MAX_TEXTURE_COUNT 10

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

typedef struct	s_rotation_matrix
{
	cl_double3		e1;
	cl_double3		e2;
	cl_double3		e3;
}				t_rotation_matrix;

struct	s_fig
{
	cl_int		fig_type;
	t_shape		shape;

	cl_double3	color;
	cl_int		specular;
	cl_double	reflective;
	cl_double	trans;
	cl_double3	rotation;
	t_rotation_matrix	rotation_martix;
	cl_double	ior;
	cl_int		text_no;
	cl_int		normal_map_no;
	cl_double2	txt_offset;
	cl_double2	txt_scale;
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
	cl_int		w;
	cl_int		h;
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

	/*		kernels		*/
	
	cl_kernel			rt_kernel;
	cl_kernel			click_kernel;

	/*		memory objects		*/
	
	cl_mem				scene_mem;
	cl_mem				pixel_ptr;
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

typedef struct	s_envi
{
	cl_int			txt_count; //number of textures
	cl_uint			*txt; //could be uint16 : rgb565. to save more space for kernel
	int				textures_size; //the sumary size of all textures
	t_txt_params	txt_par[MAX_TEXTURE_COUNT]; //w, h and start point for each texture in txt array
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
**	Init
*/

int		init_start_params(t_rt *rt);
int		read_textures(t_rt *rt);

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

int			init_sdl(t_sdl *sdl, int w, int h);
int			close_sdl(t_sdl *sdl);

/*
**	Friendly user stuff
*/
int			error_message(char *mess);
int			print_usage(void);


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

# include "parse.h"
# include "mymath.h"
# include "xml.h"
# include "editor.h"

#endif
