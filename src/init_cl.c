/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 15:02:32 by apavlov           #+#    #+#             */
/*   Updated: 2019/09/26 12:50:36 by apavlov          ###   ########.fr       */
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
	ret = clGetDeviceIDs(cl->platform_id, DEVICE_TYPE, \
								1, &cl->device_id, &cl->device_count);
	if (!cl->device_id)
		return (error_message(RED"clGetDeviceIDs problem"COLOR_OFF));
	if (ret != CL_SUCCESS)
		return (error_message(RED"clGetDeviceIDs exception"COLOR_OFF));
	clGetDeviceInfo(cl->device_id, \
					CL_DEVICE_DOUBLE_FP_CONFIG, sizeof(tmp), &tmp, 0);
	if (!(tmp & (CL_FP_FMA | CL_FP_ROUND_TO_NEAREST | CL_FP_ROUND_TO_ZERO |
			CL_FP_ROUND_TO_INF | CL_FP_INF_NAN | CL_FP_DENORM)))
		return (error_message(RED"DOUBLE_FP_CONFIG exception"COLOR_OFF));
	cl->context = clCreateContext(NULL, 1, &cl->device_id, NULL, NULL, &ret);
	if (ret != CL_SUCCESS)
		return (error_message(RED"clCreateContext exception"COLOR_OFF));
	cl->command_queue = clCreateCommandQueue(cl->context, \
							cl->device_id, 0, &ret);
	if (ret != CL_SUCCESS)
		return (error_message(RED"clCreateCommandQueue exception"COLOR_OFF));
	return (0);
}

int			create_program_and_kernels(t_cl *cl)
{
	char	**source_str;
	cl_int	ret;

	ret = 0;
	source_str = (char**)ft_memalloc(sizeof(char*) * COUNT_CL_FILES);
	if (read_cl_files(source_str, cl))
		return (1);
	ret = -1;
	while (++ret < COUNT_CL_FILES)
		free(source_str[ret]);
	free(source_str);
	build_program(cl);
	return (0);
}
