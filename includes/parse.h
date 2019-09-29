/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yruda <yruda@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 15:31:31 by apavlov           #+#    #+#             */
/*   Updated: 2019/09/27 21:46:32 by yruda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "rt.h"

# define BUFFER_SIZE 200
# define COUNT_CL_FILES 6

int			read_file(char *file_name, char **file_text);
int			read_texture(char	*file_name, t_envi *envi);
SDL_Surface	*load_tex(char *path, Uint32 format);

#endif
