/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cl2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 11:52:52 by apavlov           #+#    #+#             */
/*   Updated: 2019/09/28 13:03:52 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void		print_compiles_errors(t_cl *cl)
{
	size_t	log_size;
	char	*log;

	ft_putstr(ON_PURPLE);
	clGetProgramBuildInfo(cl->program, cl->device_id, \
								CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
	log = (char*)malloc(log_size);
	clGetProgramBuildInfo(cl->program, cl->device_id, \
							CL_PROGRAM_BUILD_LOG, log_size, log, NULL);
	write(1, log, ft_strlen(log));
	free(log);
	ft_putstr(COLOR_OFF);
	exit(error_message(RED"clBuildProgram exception"COLOR_OFF));
}

int			set_global_and_local_item_size(t_cl *cl, t_rt *rt)
{
	cl_int	ret;

	cl->global_size = rt->pov.h * rt->pov.w;
	ret = clGetKernelWorkGroupInfo(cl->rt_kernel, \
		cl->device_id, CL_KERNEL_WORK_GROUP_SIZE, \
			sizeof(size_t), &cl->local_size, 0);
	cl->local_size = cl->local_size > cl->global_size ? \
							cl->global_size : cl->local_size;
	if (ret != CL_SUCCESS)
		return (error_message(RED"KernelWorkGroupInfo exception"COLOR_OFF));
	while (cl->global_size % cl->local_size)
		cl->local_size--;
	return (0);
}

int			read_cl_files(char **source_str, t_cl *cl)
{
	cl_int	ret;

	if (read_file("./src/cl/test.cl", source_str))
		return (error_message(RED"test.cl problem"COLOR_OFF));
	if (read_file("./src/cl/editor_click_intersection.cl", source_str + 1))
		return (error_message(RED"editor kernel problem"COLOR_OFF));
	if (read_file("./src/cl/intersection_with_figures_and_normals.cl", \
source_str + 2))
		return (error_message(RED"intersection cl file problem"COLOR_OFF));
	if (read_file("./src/cl/color_managment.cl", source_str + 3))
		return (error_message(RED"color_managment.cl problem"COLOR_OFF));
	if (read_file("./src/cl/other_function.cl", source_str + 4))
		return (error_message(RED"color_managment.cl problem"COLOR_OFF));
	if (read_file("./src/cl/textures_and_bump.cl", source_str + 5))
		return (error_message(RED"color_managment.cl problem"COLOR_OFF));
	cl->program = clCreateProgramWithSource(cl->context, 6, \
		(const char **)source_str, 0, &ret);
	if (ret != CL_SUCCESS)
		return (error_message(RED"clCreateProgram exception"COLOR_OFF));
	return (0);
}

int			build_program(t_cl *cl)
{
	cl_int	ret;

	ret = clBuildProgram(cl->program, 1, \
			&cl->device_id, "-I src/cl/", NULL, NULL);
	if (ret == CL_BUILD_PROGRAM_FAILURE)
		print_compiles_errors(cl);
	else if (ret != CL_SUCCESS)
		return (error_message(RED"clBuildProgram exception"COLOR_OFF));
	cl->rt_kernel = clCreateKernel(cl->program, "test_kernel", &ret);
	if (ret != CL_SUCCESS)
		return (error_message(RED"clCreateKernel test_kernel"COLOR_OFF));
	cl->click_kernel = clCreateKernel(cl->program, "click_kernel", &ret);
	if (ret != CL_SUCCESS)
		return (error_message(RED"clCreateKernel click_kernel"COLOR_OFF));
	return (0);
}

int			freed_up_memory(t_cl *cl, t_rt *rt)
{
	cl_int	ret;

	ret = clReleaseMemObject(cl->scene_mem);
	if (ret != CL_SUCCESS)
		error_message(RED"clReleaseMemObject(scene_mem)"COLOR_OFF);
	ret = clReleaseMemObject(cl->pixel_ptr);
	if (ret != CL_SUCCESS)
		error_message(RED"clReleaseMemObject(pixel_ptr)"COLOR_OFF);
	ret = clReleaseMemObject(cl->texture_mem);
	if (ret != CL_SUCCESS)
		error_message(RED"clReleaseMemObject(texture_mem)"COLOR_OFF);
	ret = clReleaseMemObject(cl->txt_param_mem);
	if (ret != CL_SUCCESS)
		error_message(RED"clReleaseMemObject(cl->txt_param_mem)"COLOR_OFF);
	free(rt->filters.buff);
	free(rt->filters.colors);
	free(rt->filters.zbuff);
	return (0);
}
