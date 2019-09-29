/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_events2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yruda <yruda@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 20:20:11 by apavlov           #+#    #+#             */
/*   Updated: 2019/09/28 15:26:04 by yruda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

static void	cool_little_function(t_rt *rt, cl_double3 *data, cl_double3 dir)
{
	cl_double3		oc;

	oc = minus_double3(rt->pov.coord, *data);
	dir = increase_double3(dir, vector_len(oc));
	*data = add_double3(*data, dir);
}

static void	set_up_new_coord(t_rt *rt, int x, int y)
{
	cl_int2		g;
	cl_double3	*dot;
	t_fig		*obj;
	double		dir_len;
	cl_double3	dir;

	SDL_GetMouseState(&g.s[0], &g.s[1]);
	obj = rt->scene.obj + rt->edi.chosen_obj;
	dir_len = vector_len(canvas_to_viewport(g.s[0], g.s[1], rt->pov));
	dir = (cl_double3){{x * rt->pov.vh / (rt->pov.w * dir_len), \
		(-y) * rt->pov.vw / (rt->pov.h * dir_len), 0}};
	dir = new_basis(dir, rt->pov.pov_rm);
	if (obj->fig_type == RECTANGLE && obj->complex_fig > -1)
	{
		dot = &rt->scene.cubs[obj->complex_fig].cent;
		if (dot)
			cool_little_function(rt, dot, dir);
		ft_fill_rectangle(&rt->scene, obj->complex_fig, NULL, NULL);
	}
	else
	{
		dot = get_obj_dot(obj);
		if (dot)
			cool_little_function(rt, dot, dir);
	}
}

int			move_fig(t_rt *rt)
{
	int		x;
	int		y;
	cl_int	ret;

	if (rt->edi.chosen_obj != -1)
	{
		SDL_GetRelativeMouseState(&x, &y);
		if (x == 0 && y == 0)
			return (0);
		set_up_new_coord(rt, x, y);
		ret = clEnqueueWriteBuffer(rt->cl.command_queue, \
		rt->cl.scene_mem, CL_TRUE, 0, sizeof(t_scene), &rt->scene, 0, 0, 0);
		if (ret != CL_SUCCESS)
			exit(error_message(RED"Something went bad\n"COLOR_OFF));
		return (1);
	}
	return (0);
}

int			there_will_be_loop(t_rt *rt)
{
	int	ret;

	render_scene(rt);
	while (1)
	{
		if (user_events(rt))
		{
			ret = clSetKernelArg(rt->cl.rt_kernel, 2, \
			sizeof(rt->pov), &rt->pov);
			if (ret != CL_SUCCESS)
				return (error_message(RED"clSetKernelArg(4) \
				exception"COLOR_OFF));
			render_scene(rt);
		}
	}
	return (0);
}

int			mouse_events(t_rt *rt, Uint8 button, int x, int y)
{
	int		changes;

	changes = 0;
	if (button == SDL_BUTTON_LEFT)
	{
		rt->edi.chosen_obj = get_object_intersection(rt, x, y);
		SDL_GetRelativeMouseState(NULL, NULL);
		return (1);
	}
	else
		return (0);
}
