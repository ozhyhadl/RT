/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 16:54:35 by apavlov           #+#    #+#             */
/*   Updated: 2019/09/28 12:35:28 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int			read_file(char *file_name, char **file_text)
{
	int		fd;
	char	buf[BUFFER_SIZE];
	int		ret;
	char	*tmp;

	fd = open(file_name, O_RDONLY);
	ret = 0;
	*file_text = 0;
	tmp = 0;
	while ((ret = read(fd, buf, BUFFER_SIZE - 1)) > 0)
	{
		buf[ret] = 0;
		if (*file_text != 0)
		{
			tmp = ft_strjoin(*file_text, buf);
			free(*file_text);
		}
		else
			tmp = ft_strdup(buf);
		*file_text = tmp;
	}
	return (ret < 0 ? 1 : 0);
}

SDL_Surface	*load_tex(char *path, Uint32 format)
{
	SDL_Surface		*temp;
	SDL_Surface		*texture;

	temp = IMG_Load(path);
	if (temp == NULL)
	{
		SDL_FreeSurface(temp);
		error_message(RED"Texture load error\n"COLOR_OFF);
		exit(1);
	}
	texture = SDL_ConvertSurfaceFormat(temp, format, 0);
	if (texture == NULL)
	{
		SDL_FreeSurface(temp);
		error_message(RED"Texture load error\n"COLOR_OFF);
		exit(1);
	}
	SDL_FreeSurface(temp);
	return (texture);
}

void		*ft_realloc(void *p, size_t new_size, size_t prev_size)
{
	unsigned char	*res;
	unsigned char	*copy_of_p;
	size_t			i;

	res = 0;
	res = ft_memalloc(new_size);
	if (!res)
		exit(error_message(RED"malloc is that you?"COLOR_OFF));
	if (!p)
		return (res);
	copy_of_p = (unsigned char*)p;
	i = -1;
	if (prev_size > new_size)
		prev_size = new_size;
	while (++i < prev_size)
		res[i] = copy_of_p[i];
	return ((void*)res);
}

static void	make_it_simple(t_envi *envi, SDL_Surface *surr, \
	int *new_size, cl_uint **tmp)
{
	envi->txt_par[envi->txt_count].w = surr->w;
	envi->txt_par[envi->txt_count].h = surr->h;
	envi->txt_par[envi->txt_count].start_pos = envi->textures_size;
	*new_size = envi->textures_size + surr->w * surr->h;
	(*tmp) = (cl_uint*)ft_realloc(envi->txt, \
		sizeof(cl_uint) * (*new_size), sizeof(cl_uint) * envi->textures_size);
	if (!(*tmp))
		exit(0);
	if (envi->txt)
		free(envi->txt);
	envi->txt = (*tmp);
}

int			read_texture(char *file_name, t_envi *envi)
{
	SDL_Surface	*surr;
	cl_uint		*tmp;
	Uint8		*pixels;
	int			i;
	int			new_size;

	surr = load_tex(file_name, SDL_PIXELFORMAT_ARGB32);
	make_it_simple(envi, surr, &new_size, &tmp);
	if (envi->txt == 0)
	{
		return (error_message(RED"couldn't \
		reallocate for some reason"COLOR_OFF));
	}
	i = -1;
	pixels = (Uint8*)surr->pixels;
	while (++i < surr->w * surr->h)
		envi->txt[envi->txt_par[envi->txt_count].start_pos + i] = \
(pixels[i * 4] << 24) + (pixels[i * 4 + 1] << 16) + \
	(pixels[i * 4 + 2] << 8) + pixels[i * 4 + 3];
	SDL_FreeSurface(surr);
	envi->textures_size = new_size;
	envi->txt_count++;
	return (0);
}
