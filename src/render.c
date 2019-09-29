/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 13:52:27 by apavlov           #+#    #+#             */
/*   Updated: 2019/09/28 12:49:32 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void		move_obj_a_little(t_rt *rt)
{
	int				i;
	cl_double3		*dot;
	t_obj_movement	move;
	int				ret;

	i = -1;
	while (++i < rt->scene.count_obj)
	{
		move = rt->filters.obj_movement[i];
		if (move.move)
		{
			dot = get_obj_dot(rt->scene.obj + i);
			if (dot)
				*dot = add_double3(*dot, move.dir);
		}
	}
	ret = clEnqueueWriteBuffer(rt->cl.command_queue, \
	rt->cl.scene_mem, CL_TRUE, 0, sizeof(t_scene), &rt->scene, 0, 0, 0);
	if (ret != CL_SUCCESS)
		exit(error_message(RED"Something went bad\n"COLOR_OFF));
}

void		set_obj_back(t_rt *rt)
{
	int				i;
	cl_double3		*dot;
	t_obj_movement	move;
	int				ret;

	i = -1;
	while (++i < rt->scene.count_obj)
	{
		move = rt->filters.obj_movement[i];
		if (move.move)
		{
			dot = get_obj_dot(rt->scene.obj + i);
			if (dot)
			{
				move.dir = increase_double3(move.dir, RENDER_ITARATION);
				*dot = minus_double3(*dot, move.dir);
			}
		}
	}
	ret = clEnqueueWriteBuffer(rt->cl.command_queue, \
	rt->cl.scene_mem, CL_TRUE, 0, sizeof(t_scene), &rt->scene, 0, 0, 0);
	if (ret != CL_SUCCESS)
		exit(error_message(RED"Something went bad\n"COLOR_OFF));
}

void		add_to_buff_to_array(cl_double3 *arr, Uint32 *buff, t_rt *rt)
{
	int		x;
	int		y;
	int		indx;

	y = -1;
	while (++y < rt->pov.h)
	{
		x = -1;
		while (++x < rt->pov.w)
		{
			indx = y * rt->pov.w + x;
			arr[indx].s[0] += (buff[indx] >> 16 & 0xff);
			arr[indx].s[1] += (buff[indx] >> 8 & 0xff);
			arr[indx].s[2] += (buff[indx] & 0xff);
		}
	}
}

void		array_to_screen_pixels(Uint32 *pix, \
					cl_double3 *arr, int div, t_rt *rt)
{
	int		x;
	int		y;
	int		indx;

	y = -1;
	while (++y < rt->pov.h)
	{
		x = -1;
		while (++x < rt->pov.w)
		{
			indx = y * rt->pov.w + x;
			pix[indx] = ((Uint32)(arr[indx].s[0] / div) << 16) + \
			((Uint32)(arr[indx].s[1] / div) << 8) + \
			((Uint32)(arr[indx].s[2] / div));
		}
	}
}

int			render_scene(t_rt *rt)
{
	cl_uint	*pixels;

	pixels = (cl_uint*)rt->sdl.win_sur->pixels;
	if (rt->filters.motion)
	{
		if (motion(rt, pixels))
			exit(1);
	}
	else
	{
		if (static_render(rt, pixels))
			exit(1);
	}
	add_filter(rt);
	if (rt->filters.info == 0)
		apply_surface(rt->sdl.win_sur, rt);
	else if (rt->filters.info == 1)
	{
		SDL_BlitScaled(rt->filters.image, NULL,
			rt->sdl.win_sur, &(SDL_Rect){0, 0, rt->pov.w, rt->pov.h});
	}
	SDL_UpdateWindowSurface(rt->sdl.win);
	return (0);
}
