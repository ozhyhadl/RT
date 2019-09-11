/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_event.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 14:15:40 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/21 14:15:40 by apavlov          ###   ########.fr       */
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
	rt->pov.dir.s0 += (y) * ROTATION_SPEED;
	rt->pov.dir.s1 += (x) * ROTATION_SPEED;
	rt->pov.cx = cos(rt->pov.dir.s0 / 180 * M_PI);
	rt->pov.sx = sin(rt->pov.dir.s0 / 180 * M_PI);
	rt->pov.cy = cos(rt->pov.dir.s1 / 180 * M_PI);
	rt->pov.sy = sin(rt->pov.dir.s1 / 180 * M_PI);
	return (1);
}

int			mouse_events(t_rt *rt, Uint8 button)
{
	if (button == SDL_BUTTON_LEFT)
	{
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
			mouse_events(rt, ev.button.button);
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
			ret = clSetKernelArg(rt->cl.rt_kernel, 4, sizeof(rt->pov), &rt->pov);
			if (ret != CL_SUCCESS)
				return (error_message(RED"clSetKernelArg(4) exception"COLOR_OFF));
			/*__________________________________________________*/


			render_scene(rt);
		}
	}
	return (0);
}
