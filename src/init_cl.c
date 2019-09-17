/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhyhadl <ozhyhadl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 15:02:32 by apavlov           #+#    #+#             */
/*   Updated: 2019/09/14 18:59:01 by ozhyhadl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int			init_cl(t_cl *cl)
{
	cl_device_fp_config	tmp;
	cl_int				ret;

	ret = clGetPlatformIDs(1, &cl->platform_id, &cl->platform_count);
	if (ret != CL_SUCCESS)
		return (error_message(RED"clGetPlatformIDs exception"COLOR_OFF));
	ret = clGetDeviceIDs(cl->platform_id, DEVICE_TYPE, 1, &cl->device_id, &cl->device_count);
	if (!cl->device_id)
		return (error_message(RED"clGetDeviceIDs problem"COLOR_OFF));
	if (ret != CL_SUCCESS)
		return (error_message(RED"clGetDeviceIDs exception"COLOR_OFF));
	clGetDeviceInfo(cl->device_id, CL_DEVICE_DOUBLE_FP_CONFIG, sizeof(tmp), &tmp, 0);
	if (!(tmp & (CL_FP_FMA | CL_FP_ROUND_TO_NEAREST | CL_FP_ROUND_TO_ZERO |
			CL_FP_ROUND_TO_INF | CL_FP_INF_NAN | CL_FP_DENORM)))
		return (error_message(RED"CL_DEVICE_DOUBLE_FP_CONFIG exception"COLOR_OFF));
	cl->context = clCreateContext( NULL, 1, &cl->device_id, NULL, NULL, &ret);
	if (ret != CL_SUCCESS)
		return (error_message(RED"clCreateContext exception"COLOR_OFF));
	cl->command_queue = clCreateCommandQueue(cl->context, cl->device_id, 0, &ret);
	if (ret != CL_SUCCESS)
		return (error_message(RED"clCreateCommandQueue exception"COLOR_OFF));
	return (0);
}

void		print_compiles_errors(t_cl *cl)
{
	size_t log_size;

	ft_putstr(ON_PURPLE);

	clGetProgramBuildInfo(cl->program, cl->device_id, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
	char *log = (char *) malloc(log_size);
	clGetProgramBuildInfo(cl->program, cl->device_id, CL_PROGRAM_BUILD_LOG, log_size, log, NULL);
	write(1, log, ft_strlen(log));
	free(log);

	ft_putstr(COLOR_OFF);
	exit(error_message(RED"clBuildProgram exception"COLOR_OFF));
}

int			create_program_and_kernels(t_cl *cl)
{
	char	**source_str;
	cl_int	ret;

	ret = 0;
	source_str = (char**)ft_memalloc(sizeof(char*) * COUNT_CL_FILES);
	if (read_file("./src/cl/test.cl", source_str))
		return (error_message(RED"test.cl problem"COLOR_OFF));
	if (read_file("./src/cl/editor_click_intersection.cl", source_str + 1))
		return (error_message(RED"editor_click_intersection.cl problem"COLOR_OFF));
	if (read_file("./src/cl/intersection_with_figures_and_normals.cl", source_str + 2))
		return (error_message(RED"intersection_with_figures_and_normals.cl problem"COLOR_OFF));
	if (read_file("./src/cl/color_managment.cl", source_str + 3))
		return (error_message(RED"color_managment.cl problem"COLOR_OFF));
	if (read_file("./src/cl/other_function.cl", source_str + 4))
		return (error_message(RED"color_managment.cl problem"COLOR_OFF));
	if (read_file("./src/cl/textures_and_bump.cl", source_str + 5))
		return (error_message(RED"color_managment.cl problem"COLOR_OFF));

	cl->program = clCreateProgramWithSource(cl->context, 6, \
		(const char **)source_str, 0, &ret);
	if (ret != CL_SUCCESS)
		return (error_message(RED"clCreateProgramWithSource exception"COLOR_OFF));

	ret = -1;
	while (++ret < COUNT_CL_FILES)
		free(source_str[ret]);
	free(source_str);

	ret = clBuildProgram(cl->program, 1, &cl->device_id, "-I includes", NULL, NULL);
	if (ret == CL_BUILD_PROGRAM_FAILURE)
		print_compiles_errors(cl);
	else if (ret != CL_SUCCESS)
		return (error_message(RED"clBuildProgram exception"COLOR_OFF));
		
	cl->rt_kernel = clCreateKernel(cl->program, "test_kernel", &ret);
	if (ret != CL_SUCCESS)
		return (error_message(RED"clCreateKernel test_kernel exception"COLOR_OFF));
	cl->click_kernel = clCreateKernel(cl->program, "click_kernel", &ret);
	if (ret != CL_SUCCESS)
		return (error_message(RED"clCreateKernel click_kernel exception"COLOR_OFF));
	return (0);
}

int			set_global_and_local_item_size(t_cl *cl, t_rt *rt)
{
	cl_int	ret;

	cl->global_size = rt->pov.h * rt->pov.w;
	ret = clGetKernelWorkGroupInfo(cl->rt_kernel, cl->device_id, CL_KERNEL_WORK_GROUP_SIZE, sizeof(size_t), &cl->local_size, 0);
	cl->local_size = cl->local_size > cl->global_size ? cl->global_size : cl->local_size;
	if (ret != CL_SUCCESS)
		return (error_message(RED"clGetKernelWorkGroupInfo exception"COLOR_OFF));
	while (cl->global_size % cl->local_size)
		cl->local_size--;
	return (0);
}

int			set_up_memory(t_rt *rt, t_cl *cl)
{
	cl_int	ret;

	cl->scene_mem = clCreateBuffer(cl->context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, sizeof(t_scene), &rt->scene, &ret);
	if (ret != CL_SUCCESS)
		return (error_message(RED"clCreateBuffer(scene_mem) exception"COLOR_OFF));
	cl->pixel_ptr = clCreateBuffer(cl->context, CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY, sizeof(cl_uint) * rt->pov.h * rt->pov.w, 0, &ret);
	if (ret != CL_SUCCESS)
		return (error_message(RED"clCreateBuffer(pixel_ptr) exception"COLOR_OFF));
	cl->texture_mem = clCreateBuffer(cl->context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(cl_uint) * rt->envi.textures_size, rt->envi.txt, &ret);
	if (ret != CL_SUCCESS)
		return (error_message(RED"clCreateBuffer(texture_mem) exception"COLOR_OFF));
	cl->txt_param_mem = clCreateBuffer(cl->context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(t_txt_params) * rt->envi.txt_count, rt->envi.txt_par, &ret);
	if (ret != CL_SUCCESS)
		return (error_message(RED"clCreateBuffer(texture_mem) exception"COLOR_OFF));
	
	//mem obj for id click
	cl->id_obj = clCreateBuffer(cl->context, CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY, sizeof(int), 0, &ret);
	if (ret != CL_SUCCESS)
		return (error_message(RED"clCreateBuffer(texture_mem) exception"COLOR_OFF));

	//should i set another local and global size for second kernel?
	ret = set_global_and_local_item_size(cl, rt);
	if (ret != CL_SUCCESS)
		return (1);

	/* Argument list for test_kernel*/
	ret = clSetKernelArg(cl->rt_kernel, 0, sizeof(cl->scene_mem), &cl->scene_mem);
	if (ret != CL_SUCCESS)
		return (error_message(RED"clSetKernelArg(0) exception"COLOR_OFF));
	ret = clSetKernelArg(cl->rt_kernel, 1, sizeof(cl->pixel_ptr), &cl->pixel_ptr);
	if (ret != CL_SUCCESS)
		return (error_message(RED"clSetKernelArg(1) exception"COLOR_OFF));
	ret = clSetKernelArg(cl->rt_kernel, 2, sizeof(rt->pov), &rt->pov);
	if (ret != CL_SUCCESS)
		return (error_message(RED"clSetKernelArg(2) exception"COLOR_OFF));
	ret = clSetKernelArg(cl->rt_kernel, 3, sizeof(cl->texture_mem), &cl->texture_mem);
	if (ret != CL_SUCCESS)
		return (error_message(RED"clSetKernelArg(3) exception"COLOR_OFF));
	ret = clSetKernelArg(cl->rt_kernel, 4, sizeof(cl->txt_param_mem), &cl->txt_param_mem);
	if (ret != CL_SUCCESS)
		return (error_message(RED"clSetKernelArg(4) exception"COLOR_OFF));

	/* Argument list for click_kernel*/
	ret = clSetKernelArg(cl->click_kernel, 0, sizeof(cl->scene_mem), &cl->scene_mem);
	if (ret != CL_SUCCESS)
		return (error_message(RED"clSetKernelArg(0) exception"COLOR_OFF));
	ret = clSetKernelArg(cl->click_kernel, 3, sizeof(rt->pov), &rt->pov);
	if (ret != CL_SUCCESS)
		return (error_message(RED"clSetKernelArg(3) exception"COLOR_OFF));
	ret = clSetKernelArg(cl->click_kernel, 4, sizeof(cl->id_obj), &cl->id_obj);
	if (ret != CL_SUCCESS)
		return (error_message(RED"clSetKernelArg(4) exception"COLOR_OFF));
	return (0);
}

int			freed_up_memory(t_cl *cl)
{
	cl_int	ret;

	ret = clReleaseMemObject(cl->scene_mem);
	if (ret != CL_SUCCESS)
		error_message(RED"clReleaseMemObject(scene_mem) exception but whatever"COLOR_OFF);
	ret = clReleaseMemObject(cl->pixel_ptr);
	if (ret != CL_SUCCESS)
		error_message(RED"clReleaseMemObject(pixel_ptr) exception but whatever"COLOR_OFF);
	ret = clReleaseMemObject(cl->texture_mem);
	if (ret != CL_SUCCESS)
		error_message(RED"clReleaseMemObject(texture_mem) exception but whatever"COLOR_OFF);
	ret = clReleaseMemObject(cl->txt_param_mem);
	if (ret != CL_SUCCESS)
		error_message(RED"clReleaseMemObject(cl->txt_param_mem) exception but whatever"COLOR_OFF);
	return (0);
}