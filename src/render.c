/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhyhadl <ozhyhadl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 13:52:27 by apavlov           #+#    #+#             */
/*   Updated: 2019/09/16 19:54:37 by ozhyhadl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int			render_scene(t_rt *rt)
{
	int		ret;
	cl_uint	*pixels;
	pixels = (cl_uint*)rt->sdl.win_sur->pixels;
	ret = clEnqueueNDRangeKernel(rt->cl.command_queue, rt->cl.rt_kernel, 1, NULL, \
					&rt->cl.global_size, &rt->cl.local_size, 0, NULL, NULL);
	if (ret != CL_SUCCESS)
		return (error_message(RED"Oops"COLOR_OFF));
	ret = clEnqueueReadBuffer(rt->cl.command_queue, rt->cl.pixel_ptr, CL_FALSE, 0,
		sizeof(cl_uint) * WIN_WIDTH * WIN_HEIGHT, pixels, 0, 0, 0);
	if (ret != CL_SUCCESS)
		return (error_message(RED"Oops"COLOR_OFF));		
	clFinish(rt->cl.command_queue);

	SDL_UpdateWindowSurface(rt->sdl.win);
	return (0);
}