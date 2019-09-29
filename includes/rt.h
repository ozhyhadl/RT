/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 13:39:54 by apavlov           #+#    #+#             */
/*   Updated: 2019/09/28 15:37:38 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# ifndef CL_SILENCE_DEPRECATION
#  define CL_SILENCE_DEPRECATION
# endif

# ifndef CL_USE_DEPRECATED_OPENCL_1_2_APIS
#  define CL_USE_DEPRECATED_OPENCL_1_2_APIS
# endif

# include <fcntl.h>

# include "../libft/libft.h"
# ifdef __APPLE__
#  include "../frameworks/SDL2.framework/Headers/SDL.h"
#  include "../frameworks/SDL2_image.framework/Headers/SDL_image.h"
#  include "../frameworks/mxml-3.0/include/mxml.h"
#  include <OpenCL/opencl.h>
# else
#  include <SDL2/SDL.h>
#  include <CL/cl.h>
#  include <SDL2/SDL_image.h>
#  include <mxml.h>
# endif

# define DEVICE_TYPE	CL_DEVICE_TYPE_CPU
# ifdef __APPLE__
#  define WIN_WIDTH		800
#  define WIN_HEIGHT	600
# else
#  define WIN_WIDTH		1200
#  define WIN_HEIGHT	800
# endif
# define MAX_OBJ_COUNT 20
# define MAX_LIGHTING_COUNT 10
# define MAX_NEGATIVE_OBJ_COUNT 5
# define MAX_CUB_COUNT	5
# define RGB(v)	(((int)v[0] << 16) + ((int)v[1] << 8) + (int)v[2])
# define MIN(a,b)			(((a) < (b)) ? (a) : (b))
# define MAX(a,b)			(((a) > (b)) ? (a) : (b))
# define CLAMP(a, mi,ma)	MIN(MAX(a,mi),ma)
# define MIN_IOR 1.0004
# define MAX_IOR 2.0
# define D	0.1

# define BIG_VALUE 1000000
# define COUNT_BUTT 3
# define RENDER_ITARATION 20
# define MAX_TEXTURE_COUNT 20

# include "structures.h"
# include "terminal_colors.h"
# include "parse.h"
# include "mymath.h"
# include "xml.h"
# include "editor.h"
# include "functions.h"
# include "filter.h"
# include <time.h>

/*
**	Init
*/
int				init_start_params(t_rt *rt);
int				read_textures(t_rt *rt);

/*
**	CL		stuff
*/
int				init_cl(t_cl *cl);
int				create_program_and_kernels(t_cl *cl);
int				set_up_memory(t_rt *rt, t_cl *cl);
int				freed_up_memory(t_cl *cl, t_rt *rt);
int				set_global_and_local_item_size(t_cl *cl, t_rt *rt);
int				read_cl_files(char	**source_str, t_cl *cl);
int				build_program(t_cl *cl);

/*
**	SDL		stuff
*/
int				init_sdl(t_sdl *sdl, int w, int h);
int				close_sdl(t_sdl *sdl);

/*
**	Friendly user stuff
*/
int				error_message(char *mess);
int				print_usage(void);

/*
**	Render
*/
int				render_scene(t_rt *rt);

/*
**	User
*/
int				there_will_be_loop(t_rt *rt);
int				move_fig(t_rt *rt);
int				mouse_events(t_rt *rt, Uint8 button, int x, int y);
int				user_events(t_rt *rt);

/*
**	Button
*/
int				init_but(t_rt *rt);
void			apply_surface(SDL_Surface *dest, t_rt *rt);
int				pres_buttn(t_rt *rt, int x, int y);

/*
**	Edit
*/
int				ft_edit(t_fig *fig, t_rt *rt, SDL_Event ev);
void			add_filter(t_rt *rt);
void			change_filters(t_rt *rt, SDL_Event ev);

#endif
