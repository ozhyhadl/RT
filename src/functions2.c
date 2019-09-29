/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 11:22:24 by apavlov           #+#    #+#             */
/*   Updated: 2019/09/28 12:52:29 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

cl_double3		canvas_to_viewport(int x, int y, t_pov pov)
{
	return ((cl_double3){{(double)x * pov.vw / pov.w, \
								-(double)y * pov.vh / pov.h, (double)pov.d}});
}

int				changes_norm(t_rt *rt, int *rotations, int *move)
{
	int	changes;

	changes = 0;
	changes += translate(rt);
	if (*rotations)
		changes += rotation(rt);
	else if (*move)
		changes += move_fig(rt);
	return (changes);
}

int				motion(t_rt *rt, cl_uint *pixels)
{
	cl_int	ret;
	int		i;

	ft_bzero(rt->filters.colors, sizeof(cl_double3) * rt->pov.w * rt->pov.h);
	i = -1;
	while (++i < RENDER_ITARATION)
	{
		move_obj_a_little(rt);
		ret = clEnqueueNDRangeKernel(rt->cl.command_queue, rt->cl.rt_kernel, \
		1, NULL, &rt->cl.global_size, &rt->cl.local_size, 0, NULL, NULL);
		if (ret != CL_SUCCESS)
			return (error_message(RED"Oops"COLOR_OFF));
		ret = clEnqueueReadBuffer(rt->cl.command_queue, rt->cl.pixel_ptr, 0, \
		0, sizeof(cl_uint) * rt->pov.w * rt->pov.h, rt->filters.buff, 0, 0, 0);
		clFinish(rt->cl.command_queue);
		add_to_buff_to_array(rt->filters.colors, rt->filters.buff, rt);
	}
	set_obj_back(rt);
	array_to_screen_pixels(pixels, rt->filters.colors, RENDER_ITARATION, rt);
	return (0);
}

int				static_render(t_rt *rt, cl_uint *pixels)
{
	cl_int	ret;

	ret = clEnqueueNDRangeKernel(rt->cl.command_queue, rt->cl.rt_kernel, 1, \
		NULL, &rt->cl.global_size, &rt->cl.local_size, 0, NULL, NULL);
	if (ret != CL_SUCCESS)
		return (error_message(RED"Oops"COLOR_OFF));
	ret = clEnqueueReadBuffer(rt->cl.command_queue, rt->cl.pixel_ptr, \
CL_FALSE, 0, sizeof(cl_uint) * rt->pov.w * rt->pov.h, pixels, 0, 0, 0);
	if (ret != CL_SUCCESS)
		return (error_message(RED"Oops"COLOR_OFF));
	ret = clEnqueueReadBuffer(rt->cl.command_queue, rt->cl.zbuff, CL_FALSE, 0,
		sizeof(cl_uint) * rt->pov.w * rt->pov.h, rt->filters.zbuff, 0, 0, 0);
	if (ret != CL_SUCCESS)
		return (error_message(RED"Oops"COLOR_OFF));
	clFinish(rt->cl.command_queue);
	return (0);
}
