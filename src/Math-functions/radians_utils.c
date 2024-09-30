/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radians_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaukat <tlaukat@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 03:19:10 by tlaukat           #+#    #+#             */
/*   Updated: 2024/09/28 03:19:10 by tlaukat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xMath.h"

float	degrees_to_radians(float degrees)
{
	return (degrees * M_PI / 180.0);
}