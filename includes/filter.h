/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yruda <yruda@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 13:04:56 by myuliia           #+#    #+#             */
/*   Updated: 2019/09/27 21:44:40 by yruda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILTER_H
# define FILTER_H
# include "../includes/rt.h"

typedef	struct s_fil	t_fil;
typedef	struct s_color	t_color;

struct		s_color
{
	Uint32	r;
	Uint32	g;
	Uint32	b;
};

struct		s_fil
{
	t_color	rgb;
	t_color	array_filtr[10];
};

void		filter_blur(t_rt *rt, t_fil *f, int i, Uint32	*pixel);
void		blur(t_fil *f, t_color *array_filter);
t_color		int_to_rgb_arr(t_color array_filtr, Uint32 pixel);
void		filter1(t_fil *f);
void		filter_rand_noise(t_fil *f, int i);
void		filter_negative(t_fil *f);
void		filter_greyscale(t_fil *f);

#endif
