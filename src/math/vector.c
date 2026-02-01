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

t_vector build_v2(uint x, uint y)
{
	return (t_vector){x, y};
}

t_vector v2_add(t_vector v1, t_vector v2) {
	t_vector ret = {v1.x + v2.x, v1.y + v2.y};
	return ret;
}

t_vector v2_sub(t_vector v1, t_vector v2) {
	t_vector ret = {v1.x - v2.x, v1.y - v2.y};
	return ret;
}

unsigned int v2_sqlen(t_vector v) {
	return v.x * v.x + v.y * v.y;
}

