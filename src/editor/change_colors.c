/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_colors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yruda <yruda@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 18:02:40 by yruda             #+#    #+#             */
/*   Updated: 2019/09/28 14:10:25 by yruda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

int		change_noise(t_fig *fig, const Uint8 *k_s)
{
	if (k_s[SDL_SCANCODE_1])
		fig->noise = 0;
	else if (k_s[SDL_SCANCODE_2])
		fig->noise = 1;
	else if (k_s[SDL_SCANCODE_3])
		fig->noise = 2;
	else if (k_s[SDL_SCANCODE_4])
		fig->noise = 3;
	else if (k_s[SDL_SCANCODE_5])
		fig->noise = 4;
	else if (k_s[SDL_SCANCODE_6])
		fig->noise = -1;
	else
		return (0);
	return (1);
}

/*
**	put in the number of textures that are properly textures
*/

void	change_texture(t_fig *fig)
{
	if (fig->text_no >= 3)
		fig->text_no = -1;
	else
		fig->text_no++;
}

void	change_colours(t_fig *fig)
{
	cl_double3	colours[6];

	fig->color_index = (fig->color_index <= 4 && fig->color_index >= -1) ?
		fig->color_index + 1 : 0;
	colours[0] = (cl_double3){{249, 162, 108}};
	colours[1] = (cl_double3){{238, 69, 64}};
	colours[2] = (cl_double3){{199, 44, 65}};
	colours[3] = (cl_double3){{128, 19, 54}};
	colours[4] = (cl_double3){{81, 10, 50}};
	colours[5] = (cl_double3){{0, 255, 255}};
	fig->color = colours[fig->color_index];
}

void	visual_effects_editor(t_fig *fig, const Uint8 *k_s)
{
	if (k_s[SDL_SCANCODE_T] && k_s[87])
		fig->trans = ft_clamp(fig->trans + 0.04, 0, 1);
	else if (k_s[SDL_SCANCODE_T] && k_s[86])
		fig->trans = ft_clamp(fig->trans - 0.04, 0, 1);
	else if (k_s[SDL_SCANCODE_I] && k_s[87])
		fig->ior = ft_clamp(fig->ior + 0.04, MIN_IOR, MAX_IOR);
	else if (k_s[SDL_SCANCODE_I] && k_s[86])
		fig->ior = ft_clamp(fig->ior - 0.04, MIN_IOR, MAX_IOR);
	else if (k_s[SDL_SCANCODE_V] && k_s[86])
		fig->reflective = ft_clamp(fig->reflective - 0.04, 0.0, 1.0);
	else if (k_s[SDL_SCANCODE_V] && k_s[87])
		fig->reflective = ft_clamp(fig->reflective + 0.04, 0.0, 1.0);
}
