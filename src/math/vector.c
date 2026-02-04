/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 11:26:46 by trupham           #+#    #+#             */
/*   Updated: 2026/01/27 11:27:12 by trupham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

t_vector2f v2f_build(float x, float y)
{
	t_vector2f v;
	
	v.x = x;
	v.y = y;
	return (v);
}

t_vector v2i_build(int x, int y)
{
	t_vector v;
	
	v.x = x;
	v.y = y;
	return (v);
}

t_vector v2i_add(t_vector v1, t_vector v2) {
	t_vector ret = {v1.x + v2.x, v1.y + v2.y};
	return ret;
}

t_vector v2i_sub(t_vector v1, t_vector v2) {
	t_vector ret;
	
	ret.x = v1.x - v2.x;
	ret.y = v1.y - v2.y;
	return ret;
}

float v2i_sqlen(t_vector v)
{
	return v.x * v.x + v.y * v.y;
}
