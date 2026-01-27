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

vector_t build_v2(uint x, uint y)
{
	return (vector_t){x, y};
}

vector_t v2_add(vector_t v1, vector_t v2) {
	vector_t ret = {v1.x + v2.x, v1.y + v2.y};
	return ret;
}

vector_t v2_sub(vector_t v2, vector_t v1) {
	vector_t ret = {v1.x - v2.x, v1.y - v2.y};
	return ret;
}

unsigned int v2_sqlen(vector_t v) {
	return v.x * v.x + v.y * v.y;
}

