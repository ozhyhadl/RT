/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yruda <yruda@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 16:19:40 by myuliia           #+#    #+#             */
/*   Updated: 2019/09/28 14:13:45 by yruda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"
#include "../includes/filter.h"

void		blur(t_fil *f, t_color *array_filter)
{
	f->rgb.r = (array_filter[0].r + array_filter[1].r + array_filter[2].r + \
	array_filter[3].r + array_filter[4].r + array_filter[5].r + \
	array_filter[6].r + array_filter[7].r + array_filter[8].r) / 9;
	f->rgb.g = (array_filter[0].g + array_filter[1].g + array_filter[2].g + \
	array_filter[3].g + array_filter[4].g + array_filter[5].g + \
	array_filter[6].g + array_filter[7].g + array_filter[8].g) / 9;
	f->rgb.b = (array_filter[0].b + array_filter[1].b + array_filter[2].b + \
	array_filter[3].b + array_filter[4].b + array_filter[5].b \
	+ array_filter[6].b
	+ array_filter[7].b + array_filter[8].b) / 9;
}

t_color		int_to_rgb_arr(t_color array_filtr, Uint32 pixel)
{
	array_filtr.r = (pixel & 0x00ff0000) >> 16;
	array_filtr.g = (pixel & 0x0000ff00) >> 8;
	array_filtr.b = (pixel & 0x000000ff);
	return (array_filtr);
}

void		int_to_rgb(t_fil *f, Uint32 pixel)
{
	f->rgb.r = (pixel & 0x00ff0000) >> 16;
	f->rgb.g = (pixel & 0x0000ff00) >> 8;
	f->rgb.b = (pixel & 0x000000ff);
}

void		change_filters(t_rt *rt, SDL_Event ev)
{
	const Uint8	*k_s;

	k_s = SDL_GetKeyboardState(0);
	if (k_s[SDL_SCANCODE_Z])
		return ;
	if (ev.key.keysym.sym == SDLK_1)
		rt->filters.index_filter = 1;
	else if (ev.key.keysym.sym == SDLK_2)
		rt->filters.index_filter = 2;
	else if (ev.key.keysym.sym == SDLK_3)
		rt->filters.index_filter = 3;
	else if (ev.key.keysym.sym == SDLK_4)
		rt->filters.index_filter = 4;
	else if (ev.key.keysym.sym == SDLK_5)
		rt->filters.index_filter = 5;
	else if (ev.key.keysym.sym == SDLK_6)
		rt->filters.index_filter = 0;
}

void		add_filter(t_rt *rt)
{
	t_fil	f;
	Uint32	*pixel;
	int		i;

	i = -1;
	pixel = (Uint32 *)rt->sdl.win_sur->pixels;
	while (++i != (rt->sdl.win_sur->w * rt->sdl.win_sur->h))
	{
		int_to_rgb(&f, pixel[i]);
		if (rt->filters.index_filter == 1)
			filter1(&f);
		else if (rt->filters.index_filter == 2)
			filter_greyscale(&f);
		else if (rt->filters.index_filter == 3)
			filter_negative(&f);
		else if (rt->filters.index_filter == 4)
			filter_rand_noise(&f, i);
		else if (rt->filters.index_filter == 5)
			filter_blur(rt, &f, i, pixel);
		pixel[i] = ((int)f.rgb.r << 16) + ((int)f.rgb.g << 8) + (int)f.rgb.b;
	}
}
