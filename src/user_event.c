/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_event.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhyhadl <ozhyhadl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 14:15:40 by apavlov           #+#    #+#             */
/*   Updated: 2019/09/28 15:44:12 by ozhyhadl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int			translate(t_rt *rt)
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
	translate_vector = new_basis(translate_vector, rt->pov.pov_rm);
	rt->pov.coord = add_double3(rt->pov.coord, translate_vector);
	if (vector_len(translate_vector) != 0)
		return (1);
	return (0);
}

int			rotation(t_rt *rt)
{
	int				x;
	int				y;
	cl_double3		rotate_vector;

	SDL_GetRelativeMouseState(&x, &y);
	if (x == 0 && y == 0)
		return (0);
	rotate_vector.s[0] = (y) * ROTATION_SPEED;
	rotate_vector.s[1] = (x) * ROTATION_SPEED;
	rotate_vector.s[2] = 0;
	rt->pov.pov_rm = rotate_matrix_of_rotation(rt->pov.pov_rm, rotate_vector);
	rt->pov.dir = find_angles_from_rotation_matrix(rt->pov.pov_rm);
	return (1);
}

static void	user_events_keydown(t_rt *rt, SDL_Event ev, \
					int *changes, int *rotations)
{
	if (ev.key.keysym.sym == SDLK_1 || ev.key.keysym.sym == SDLK_2 ||
	ev.key.keysym.sym == SDLK_3 || ev.key.keysym.sym == SDLK_4 ||
	ev.key.keysym.sym == SDLK_5 || ev.key.keysym.sym == SDLK_6)
	{
		change_filters(rt, ev);
		(*changes)++;
	}
	if (ev.key.keysym.sym == SDLK_ESCAPE)
		exit(error_message(GREEN"Bye bye"COLOR_OFF) - 1);
	else if (ev.key.keysym.sym == SDLK_0)
	{
		*rotations = !(*rotations);
		SDL_SetRelativeMouseMode(*rotations);
		SDL_GetRelativeMouseState(NULL, NULL);
	}
	else if (ev.key.keysym.sym == SDLK_TAB && (*changes = 1))
		rt->filters.info = !rt->filters.info;
	else if (ev.key.keysym.sym == SDLK_m)
	{
		rt->filters.obj_movement[0].move = 1;
		rt->filters.obj_movement[0].dir = (cl_double3){{0, 0, 0.05}};
		rt->filters.motion = !rt->filters.motion;
		(*changes) = 1;
	}
}

static void	road_to_editor(t_rt *rt, int *changes, SDL_Event ev)
{
	int		ret;

	if (rt->edi.chosen_obj != -1)
	{
		if (((*changes) += ft_edit(rt->scene.obj + rt->edi.chosen_obj, rt, ev)))
		{
			ret = clEnqueueWriteBuffer(rt->cl.command_queue, \
rt->cl.scene_mem, CL_TRUE, 0, sizeof(t_scene), &rt->scene, 0, 0, 0);
			if (ret != CL_SUCCESS)
				exit(error_message(RED"Something went bad\n"COLOR_OFF));
		}
	}
}

int			user_events(t_rt *rt)
{
	SDL_Event	ev;
	int			changes;
	static int	rotations = 0;
	static int	move = 0;

	changes = changes_norm(rt, &rotations, &move);
	while (SDL_PollEvent(&ev))
	{
		if (ev.type == SDL_KEYDOWN)
			user_events_keydown(rt, ev, &changes, &rotations);
		else if (ev.type == SDL_QUIT)
			exit(error_message(GREEN"Bye bye"COLOR_OFF) - 1);
		else if (ev.type == SDL_MOUSEBUTTONDOWN)
		{
			if (ev.button.button == SDL_BUTTON_LEFT)
				changes += pres_buttn(rt, ev.button.x, ev.button.y);
			move = mouse_events(rt, ev.button.button, ev.button.x, ev.button.y);
		}
		else if (ev.type == SDL_MOUSEBUTTONUP \
			&& ev.button.button == SDL_BUTTON_LEFT)
			move = 0;
		else
			road_to_editor(rt, &changes, ev);
	}
	return (changes);
}
