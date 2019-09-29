/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 17:27:18 by myuliia           #+#    #+#             */
/*   Updated: 2019/09/27 17:19:54 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"
#include "../includes/filter.h"

void		filter1(t_fil *f)
{
	f->rgb.r = (f->rgb.r * 0.544) + (f->rgb.g * 0.765) + (f->rgb.b * 0.764);
	f->rgb.g = (f->rgb.r * 0.349) + (f->rgb.g * 0.689) + (f->rgb.b * 0.168);
	f->rgb.b = (f->rgb.r * 0.272) + (f->rgb.g * 0.534) + (f->rgb.b * 0.131);
	f->rgb.r = (f->rgb.r > 255) ? 255 : f->rgb.r;
	f->rgb.g = (f->rgb.g > 255) ? 255 : f->rgb.g;
	f->rgb.b = (f->rgb.b > 255) ? 255 : f->rgb.b;
}

void		filter_rand_noise(t_fil *f, int i)
{
	if ((i % 2) != 0)
	{
		f->rgb.r = (double)(rand() % 256);
		f->rgb.g = (double)(rand() % 256);
		f->rgb.b = (double)(rand() % 256);
	}
}

void		filter_negative(t_fil *f)
{
	f->rgb.r = 255 - f->rgb.r;
	f->rgb.g = 255 - f->rgb.g;
	f->rgb.b = 255 - f->rgb.b;
}

void		filter_greyscale(t_fil *f)
{
	f->rgb.r = (0.2126 * f->rgb.r) + (0.7152 * f->rgb.g)
	+ (0.0722 * f->rgb.b);
	f->rgb.g = f->rgb.r;
	f->rgb.b = f->rgb.r;
}

void		filter_blur(t_rt *rt, t_fil *f, int i, Uint32 *pixel)
{
	int		k;

	if ((i % 2 == 0) && (i < (rt->sdl.win_sur->w * rt->sdl.win_sur->h - 20)))
	{
		k = -1;
		while (++k < 10)
			f->array_filtr[k] =
			int_to_rgb_arr(f->array_filtr[k], pixel[i + k]);
	}
	blur(f, f->array_filtr);
}
