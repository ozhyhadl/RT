/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 15:02:46 by apavlov           #+#    #+#             */
/*   Updated: 2019/09/28 12:16:25 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int			init_sdl(t_sdl *sdl, int w, int h)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return (error_message((char *)SDL_GetError()));
	if (!(sdl->win = SDL_CreateWindow("RT", SDL_WINDOWPOS_CENTERED, \
		SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN)))
		return (error_message((char *)SDL_GetError()));
	if (!(sdl->win_sur = SDL_GetWindowSurface(sdl->win)))
		return (error_message((char *)SDL_GetError()));
	if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF) \
		!= (IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF))
		return (error_message((char *)SDL_GetError()));
	return (0);
}

int			close_sdl(t_sdl *sdl)
{
	SDL_FreeSurface(sdl->win_sur);
	sdl->win_sur = 0;
	SDL_DestroyWindow(sdl->win);
	sdl->win = 0;
	SDL_Quit();
	return (0);
}
