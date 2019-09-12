/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_event.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 14:15:40 by apavlov           #+#    #+#             */
/*   Updated: 2019/09/12 16:38:05 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

static int	translate(t_rt *rt)
{
	const Uint8		*keyboard_state = SDL_GetKeyboardState(0);
	cl_double3		translate_vector;

	translate_vector = (cl_double3){{0, 0, 0}};
	if (keyboard_state[SDL_SCANCODE_D])
		translate_vector.s[0] += TRANSLATE_SPEED;
	if (keyboard_state[SDL_SCANCODE_A])
		translate_vector.s[0] -= TRANSLATE_SPEED;
	if (keyboard_state[SDL_SCANCODE_W])
		translate_vector.s[2] += TRANSLATE_SPEED;
	if (keyboard_state[SDL_SCANCODE_S])
		translate_vector.s[2] -= TRANSLATE_SPEED;
	if (keyboard_state[SDL_SCANCODE_SPACE])
		translate_vector.s[1] += TRANSLATE_SPEED;
	if (keyboard_state[SDL_SCANCODE_LCTRL])
		translate_vector.s[1] -= TRANSLATE_SPEED;
	translate_vector = ft_rotate_camera(translate_vector, rt->pov);
	rt->pov.coord = add_double3(rt->pov.coord, translate_vector);
	if (vector_len(translate_vector) != 0)
		return (1);
	return (0);
}

int			rotation(t_rt *rt) //sometimes its must rotate z coordinate also
{
	int				x;
	int				y;

	SDL_GetRelativeMouseState(&x, &y);
	if (x == 0 && y == 0)
		return (0);
	rt->pov.dir.s[0] += (y) * ROTATION_SPEED;
	rt->pov.dir.s[1] += (x) * ROTATION_SPEED;
	rt->pov.cx = cos(rt->pov.dir.s[0] / 180 * M_PI);
	rt->pov.sx = sin(rt->pov.dir.s[0] / 180 * M_PI);
	rt->pov.cy = cos(rt->pov.dir.s[1] / 180 * M_PI);
	rt->pov.sy = sin(rt->pov.dir.s[1] / 180 * M_PI);
	return (1);
}

int			mouse_events(t_rt *rt, Uint8 button, int x, int y)
{
	cl_int	ret;
	cl_int	id_obj;

	if (button == SDL_BUTTON_LEFT)
	{

		ret = clSetKernelArg(rt->cl.click_kernel, 1, sizeof(int), &x);
		if (ret != CL_SUCCESS)
			return (error_message(RED"clSetKernelArg(1) exception"COLOR_OFF));
		ret = clSetKernelArg(rt->cl.click_kernel, 2, sizeof(int), &y);
		if (ret != CL_SUCCESS)
			return (error_message(RED"clSetKernelArg(2) exception"COLOR_OFF));
		ret = clSetKernelArg(rt->cl.click_kernel, 3, sizeof(rt->pov), &rt->pov);
		if (ret != CL_SUCCESS)
			return (error_message(RED"clSetKernelArg(3) exception"COLOR_OFF));

		ret = clEnqueueTask (rt->cl.command_queue, rt->cl.click_kernel, 0, NULL, NULL);
		if (ret != CL_SUCCESS)
			return (error_message(RED"Oops"COLOR_OFF));
		ret = clEnqueueReadBuffer(rt->cl.command_queue, rt->cl.id_obj, CL_FALSE, 0, sizeof(cl_int), &id_obj, 0, 0, 0);
		if (ret != CL_SUCCESS)
			return (error_message(RED"Oops"COLOR_OFF));

		clFinish(rt->cl.command_queue);
		
		printf("%i\n", id_obj);
		return (1);
	}
	else	
		return (0);
}

int			user_events(t_rt *rt)
{
	SDL_Event	ev;
	int			changes;
	static int	rotations = 0;

	changes = 0;
	changes += translate(rt);
	if (rotations)
		changes += rotation(rt);
	while (SDL_PollEvent(&ev))
	{
		if (ev.type == SDL_KEYDOWN)
		{
			if (ev.key.keysym.sym == SDLK_ESCAPE)
				exit(error_message(GREEN"Bye bye"COLOR_OFF) - 1);
			else if (ev.key.keysym.sym == SDLK_0)
			{
				rotations = !rotations;
				SDL_SetRelativeMouseMode(rotations);
				SDL_GetRelativeMouseState(NULL, NULL);
			}
		}
		else if (ev.type == SDL_QUIT)
			exit(error_message(GREEN"Bye bye"COLOR_OFF) - 1);
		else if (ev.type == SDL_MOUSEBUTTONDOWN)
			mouse_events(rt, ev.button.button, ev.button.x, ev.button.y);
	}
	return (changes);
}

int			there_will_be_loop(t_rt *rt)
{
	int	ret;

	render_scene(rt);
	while (1)
	{
		if (user_events(rt))
		{

			
			/*There should be relinkage to OpenCL*/
			ret = clSetKernelArg(rt->cl.rt_kernel, 2, sizeof(rt->pov), &rt->pov);
			if (ret != CL_SUCCESS)
				return (error_message(RED"clSetKernelArg(4) exception"COLOR_OFF));
			/*__________________________________________________*/


			render_scene(rt);
		}
	}
	return (0);
}
