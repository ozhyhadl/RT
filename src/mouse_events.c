/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 16:59:03 by apavlov           #+#    #+#             */
/*   Updated: 2019/09/14 16:59:22 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int			get_object_intersection(t_rt *rt, int x, int y)
{
	cl_int	ret;
	int		id_obj;

	ret = clSetKernelArg(rt->cl.click_kernel, 1, sizeof(int), &x);
	if (ret != CL_SUCCESS)
		exit(error_message(RED"clSetKernelArg(1) exception"COLOR_OFF));
	ret = clSetKernelArg(rt->cl.click_kernel, 2, sizeof(int), &y);
	if (ret != CL_SUCCESS)
		exit(error_message(RED"clSetKernelArg(2) exception"COLOR_OFF));
	ret = clSetKernelArg(rt->cl.click_kernel, 3, sizeof(rt->pov), &rt->pov);
	if (ret != CL_SUCCESS)
		exit(error_message(RED"clSetKernelArg(3) exception"COLOR_OFF));
	ret = clEnqueueTask (rt->cl.command_queue, rt->cl.click_kernel, 0, NULL, NULL);
	if (ret != CL_SUCCESS)
		exit(error_message(RED"Oops"COLOR_OFF));
	ret = clEnqueueReadBuffer(rt->cl.command_queue, rt->cl.id_obj, CL_FALSE, 0, sizeof(cl_int), &id_obj, 0, 0, 0);
	if (ret != CL_SUCCESS)
		exit(error_message(RED"Oops"COLOR_OFF));
	clFinish(rt->cl.command_queue);
	return (id_obj);
}
