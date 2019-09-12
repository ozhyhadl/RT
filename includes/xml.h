/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozhyhadl <ozhyhadl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 22:50:17 by ozhyhadl          #+#    #+#             */
/*   Updated: 2019/09/12 22:52:50 by ozhyhadl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XML_H
# define XML_H

# include "rt.h"

/*
**	Add ++ parse xml
*/
int		ft_parse_xml(char *name_file, t_scene *scene, t_pov *pov);
int		ft_check_child(mxml_node_t *node);
int		ft_is_cam(mxml_node_t *node, t_pov *pov, int what_is);
int		ft_is_light(mxml_node_t *node, t_scene *scene, int l, int what_is);
int		ft_is_param(mxml_node_t *node, t_scene *scene, int i, int what_is);
int		ft_is_obj(const char *str, t_scene *scene, int *il, t_pov *pov);

/*
**	Add ++ create define figure and light
*/
void	ft_create_cylin(t_scene *scene, int i);
void	ft_create_cone(t_scene *scene, int i);
void	ft_create_pale(t_scene *scene, int i);
void	ft_create_spher(t_scene *scene, int i);
void	ft_creat_light(t_scene *scene, int l);

/*
**	Add ++ add_param(position, radius, normal, dir, tang, type) to figure
*/
int		add_position(const char *str, t_scene *scene, int i, const char *tag);
int		ft_add_radius(const char *str, t_scene *scene, int i);
int		ft_add_normal_dir(const char *str, t_scene *scene, int i, const char *tag);
int		ft_add_tanget(const char *str, t_scene *scene, int i);
int		ft_add_type_light(t_scene *scene, int l, char *str);

/*
**	Add ++ add_param(color, specular, reflection) to figure
*/
int		add_for_all_obj(const char *str, t_scene *scene, int i, const char *tag);
int		ft_add_rgb(const char *str, t_scene *scene, int i);
int		ft_get_3param(int i, const char *str, cl_double3 *dot, cl_double *one_dot);

/*
**	Add ++ add_param to cam
*/
void	ft_create_cam(t_pov *pov);
int		ft_add_cam_dot(const char *str, t_pov *pov);

/*
**	Add ++ xml write to xml file
*/

int		ft_xml_save(char *name_file, t_scene *scene, t_pov pov);
void	ft_write_to_xml(t_fig fig, mxml_node_t *data);
void	ft_write_all(t_fig fig, mxml_node_t *node);
void	ft_write_3param(cl_double3 param, mxml_node_t *node, const char *name);
void	ft_write_param(cl_double param, mxml_node_t *node, const char *name);
void	ft_write_cam(t_pov pov, mxml_node_t *data);
void	ft_write_light(t_light light, mxml_node_t *data);

#endif