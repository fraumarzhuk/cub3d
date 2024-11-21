/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radians_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaukat <tlaukat@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 03:19:10 by tlaukat           #+#    #+#             */
/*   Updated: 2024/10/07 00:25:28 by tlaukat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xMath.h"

double	degrees_to_radians(double degrees)
{
	return (degrees * M_PI / 180.0);
}
