/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 15:31:31 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/29 15:31:32 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "rt.h" 

# define BUFFER_SIZE 200
# define COUNT_CL_FILES 6

int			read_file(char *file_name, char **file_text);
cl_uint		*read_texture(char	*file_name, t_txt_params *params);
SDL_Surface	*load_tex(char *path, Uint32 format);

#endif
