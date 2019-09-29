/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cl3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 12:49:17 by apavlov           #+#    #+#             */
/*   Updated: 2019/09/26 12:50:22 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

static int	create_buffers_2(t_rt *rt, t_cl *cl)
{
	cl_int	r;

	cl->texture_mem = clCreateBuffer(cl->context, CL_MEM_READ_ONLY | \
		CL_MEM_COPY_HOST_PTR, sizeof(cl_uint) * \
			rt->envi.textures_size, rt->envi.txt, &r);
	if (r != CL_SUCCESS)
		return (error_message(RED"clCreateBuffer exception"COLOR_OFF));
	cl->txt_param_mem = clCreateBuffer(cl->context, CL_MEM_READ_ONLY | \
	CL_MEM_COPY_HOST_PTR, sizeof(t_txt_params) * \
					rt->envi.txt_count, rt->envi.txt_par, &r);
	if (r != CL_SUCCESS)
		return (error_message(RED"clCreateBuffer exception"COLOR_OFF));
	cl->id_obj = clCreateBuffer(cl->context, CL_MEM_WRITE_ONLY \
			| CL_MEM_HOST_READ_ONLY, sizeof(int), 0, &r);
	if (r != CL_SUCCESS)
		return (error_message(RED"clCreateBuffer exception"COLOR_OFF));
	return (0);
}

int			create_buffers(t_rt *rt, t_cl *cl)
{
	cl_int	r;

	cl->scene_mem = clCreateBuffer(cl->context, CL_MEM_READ_ONLY \
		| CL_MEM_USE_HOST_PTR, sizeof(t_scene), &rt->scene, &r);
	if (r != CL_SUCCESS)
		return (error_message(RED"clCreateBuffer exception"COLOR_OFF));
	cl->zbuff = clCreateBuffer(cl->context, CL_MEM_WRITE_ONLY, \
			sizeof(cl_float) * rt->pov.h * rt->pov.w, 0, &r);
	if (r != CL_SUCCESS)
		return (error_message(RED"clCreateBuffer exception"COLOR_OFF));
	cl->pixel_ptr = clCreateBuffer(cl->context, CL_MEM_WRITE_ONLY, \
			sizeof(cl_uint) * rt->pov.h * rt->pov.w, 0, &r);
	if (r != CL_SUCCESS)
		return (error_message(RED"clCreateBuffer exception"COLOR_OFF));
	if (create_buffers_2(rt, cl))
		return (1);
	return (0);
}

int			set_main_kernel_args(t_rt *rt, t_cl *cl)
{
	cl_int	r;

	r = clSetKernelArg(cl->rt_kernel, 0, sizeof(cl->scene_mem), &cl->scene_mem);
	if (r != CL_SUCCESS)
		return (error_message(RED"clSetKernelArg(0) exception"COLOR_OFF));
	r = clSetKernelArg(cl->rt_kernel, 1, sizeof(cl->pixel_ptr), &cl->pixel_ptr);
	if (r != CL_SUCCESS)
		return (error_message(RED"clSetKernelArg(1) exception"COLOR_OFF));
	r = clSetKernelArg(cl->rt_kernel, 2, sizeof(rt->pov), &rt->pov);
	if (r != CL_SUCCESS)
		return (error_message(RED"clSetKernelArg(2) exception"COLOR_OFF));
	r = clSetKernelArg(cl->rt_kernel, 3, \
			sizeof(cl->texture_mem), &cl->texture_mem);
	if (r != CL_SUCCESS)
		return (error_message(RED"clSetKernelArg(3) exception"COLOR_OFF));
	r = clSetKernelArg(cl->rt_kernel, 4, \
			sizeof(cl->txt_param_mem), &cl->txt_param_mem);
	if (r != CL_SUCCESS)
		return (error_message(RED"clSetKernelArg(4) exception"COLOR_OFF));
	r = clSetKernelArg(cl->rt_kernel, 5, sizeof(cl->zbuff), &cl->zbuff);
	if (r != CL_SUCCESS)
		return (error_message(RED"clSetKernelArg(5) exception"COLOR_OFF));
	return (0);
}

int			set_additional_kernel_args(t_rt *rt, t_cl *cl)
{
	int	r;

	r = clSetKernelArg(cl->click_kernel, 0, \
			sizeof(cl->scene_mem), &cl->scene_mem);
	if (r != CL_SUCCESS)
		return (error_message(RED"clSetKernelArg(0) exception"COLOR_OFF));
	r = clSetKernelArg(cl->click_kernel, 3, sizeof(rt->pov), &rt->pov);
	if (r != CL_SUCCESS)
		return (error_message(RED"clSetKernelArg(3) exception"COLOR_OFF));
	r = clSetKernelArg(cl->click_kernel, 4, sizeof(cl->id_obj), &cl->id_obj);
	if (r != CL_SUCCESS)
		return (error_message(RED"clSetKernelArg(4) exception"COLOR_OFF));
	return (0);
}

int			set_up_memory(t_rt *rt, t_cl *cl)
{
	cl_int	r;

	rt->filters.colors = ft_memalloc(sizeof(cl_double3) * \
			rt->pov.w * rt->pov.h);
	if (!rt->filters.colors)
		return (error_message(RED"malloc is it you?"COLOR_OFF));
	rt->filters.buff = ft_memalloc(sizeof(cl_double3) * rt->pov.w * rt->pov.h);
	if (!rt->filters.buff)
		return (error_message(RED"malloc is it you?"COLOR_OFF));
	rt->filters.zbuff = ft_memalloc(sizeof(float) * rt->pov.w * rt->pov.h);
	if (!rt->filters.zbuff)
		return (error_message(RED"malloc is it you?"COLOR_OFF));
	if (create_buffers(rt, cl))
		return (1);
	r = set_global_and_local_item_size(cl, rt);
	if (r != CL_SUCCESS)
		return (1);
	if (set_main_kernel_args(rt, cl))
		return (1);
	if (set_additional_kernel_args(rt, cl))
		return (1);
	return (0);
}
