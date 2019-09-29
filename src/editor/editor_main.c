/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yruda <yruda@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 18:05:09 by ozhyhadl          #+#    #+#             */
/*   Updated: 2019/09/28 14:30:28 by yruda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

void	sphere_editor(t_fig *fig, const Uint8 *k_s)
{
	if (k_s[SDL_SCANCODE_R] && k_s[87])
		fig->shape.sphere.radius =
			ft_clamp(fig->shape.sphere.radius + 0.1, 0.01, BIG_VALUE);
	else if (k_s[SDL_SCANCODE_R] && k_s[86])
		fig->shape.sphere.radius =
			ft_clamp(fig->shape.sphere.radius - 0.1, 0.01, BIG_VALUE);
	else if (k_s[SDL_SCANCODE_U])
	{
		if (k_s[SDL_SCANCODE_KP_2])
			fig->rotation.s[0] -= 0.05;
		else if (k_s[SDL_SCANCODE_KP_8])
			fig->rotation.s[0] += 0.05;
		else if (k_s[SDL_SCANCODE_KP_4])
			fig->rotation.s[1] += 0.05;
		else if (k_s[SDL_SCANCODE_KP_6])
			fig->rotation.s[1] -= 0.05;
		else if (k_s[SDL_SCANCODE_KP_7] || k_s[SDL_SCANCODE_KP_1])
			fig->rotation.s[2] += 0.1;
		else if (k_s[SDL_SCANCODE_KP_9] || k_s[SDL_SCANCODE_KP_3])
			fig->rotation.s[2] -= 0.1;
		fig->rotation_martix = build_rotation_matrix_form_angles(fig->rotation);
	}
}

void	cone_editor(t_fig *fig, const Uint8 *k_s, SDL_Event ev)
{
	if (k_s[SDL_SCANCODE_R] && k_s[87])
		fig->shape.cone.tangent =
			ft_clamp(fig->shape.cone.tangent + 0.05, 0.01, 3.14);
	else if (k_s[SDL_SCANCODE_R] && k_s[86])
		fig->shape.cone.tangent =
			ft_clamp(fig->shape.cone.tangent - 0.05, 0.01, 3.14);
	else if (ev.type == SDL_MOUSEWHEEL)
	{
		if (k_s[SDL_SCANCODE_PAGEUP])
			fig->shape.cone.mmax = ft_clamp(fig->shape.cone.mmax +
				(cl_double)ev.wheel.y / 100.0, fig->shape.cone.mmin + 0.01,
				BIG_VALUE);
		else if (k_s[SDL_SCANCODE_PAGEDOWN])
			fig->shape.cone.mmin = ft_clamp(fig->shape.cone.mmin +
				(cl_double)ev.wheel.y / 100.0, -BIG_VALUE,
				fig->shape.cone.mmax - 0.01);
		else
		{
			fig->shape.cone.mmax = ft_clamp(fig->shape.cone.mmax +
				(cl_double)ev.wheel.y / 100.0, 0.0, BIG_VALUE);
			fig->shape.cone.mmin = ft_clamp(fig->shape.cone.mmin -
				(cl_double)ev.wheel.y / 100.0, -BIG_VALUE, 0.0);
		}
	}
}

void	cylin_editor(t_fig *fig, const Uint8 *k_s, SDL_Event ev)
{
	if (k_s[SDL_SCANCODE_R] && k_s[87])
		fig->shape.cylin.radius =
			ft_clamp(fig->shape.disk.radius + 0.1, 0.01, BIG_VALUE);
	else if (k_s[SDL_SCANCODE_R] && k_s[86])
		fig->shape.cylin.radius =
			ft_clamp(fig->shape.disk.radius - 0.1, 0.01, BIG_VALUE);
	else if (ev.type == SDL_MOUSEWHEEL)
	{
		fig->shape.cylin.mmax = ft_clamp(fig->shape.cylin.mmax +
			(cl_double)ev.wheel.y / 100.0, 0.01, BIG_VALUE);
		fig->shape.cylin.mmin = ft_clamp(fig->shape.cylin.mmin -
			(cl_double)ev.wheel.y / 100.0, -BIG_VALUE, -0.01);
	}
}

void	disk_editor(t_fig *fig, const Uint8 *k_s)
{
	if (k_s[SDL_SCANCODE_R] && k_s[87])
		fig->shape.disk.radius =
			ft_clamp(fig->shape.disk.radius + 0.1, 0.01, BIG_VALUE);
	else if (k_s[SDL_SCANCODE_R] && k_s[86])
		fig->shape.disk.radius =
			ft_clamp(fig->shape.disk.radius - 0.1, 0.01, BIG_VALUE);
}

/*
**	T [+/-] - changes transparency
**	Y - changes textures
**	I [+/-] - changes ior
**	U & [1...9] - rotating texture in sphere
**	N & [1...9] rotating normal/direction and cutting plane if such exists
**	C - change colours
**	mouse wheel - change min/max
*/

int		ft_edit(t_fig *fig, t_rt *rt, SDL_Event ev)
{
	const Uint8	*k_s;

	k_s = SDL_GetKeyboardState(0);
	if (k_s[SDL_SCANCODE_T] || k_s[SDL_SCANCODE_I] || k_s[SDL_SCANCODE_V])
		visual_effects_editor(fig, k_s);
	else if (k_s[SDL_SCANCODE_Y])
		change_texture(fig);
	else if (k_s[SDL_SCANCODE_N])
		rotate_by_type(k_s, fig, &rt->scene);
	else if (k_s[SDL_SCANCODE_C])
		change_colours(fig);
	else if (fig->fig_type == SPHERE)
		sphere_editor(fig, k_s);
	else if (fig->fig_type == CONE)
		cone_editor(fig, k_s, ev);
	else if (fig->fig_type == DISK)
		disk_editor(fig, k_s);
	else if (fig->fig_type == CYLIN)
		cylin_editor(fig, k_s, ev);
	else
		return (k_s[SDL_SCANCODE_Z] && change_noise(fig, k_s)) ? 1 : 0;
	if (fig->fig_type == RECTANGLE && fig->complex_fig > -1)
		ft_fill_rectangle(&rt->scene, fig->complex_fig, fig, &rt->filters);
	return (1);
}
