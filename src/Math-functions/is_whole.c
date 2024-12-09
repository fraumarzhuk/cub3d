/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_whole.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:10:12 by mzhukova          #+#    #+#             */
/*   Updated: 2024/11/19 15:10:12 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xMath.h"

int	is_whole(double number)
{
	return (floor(number) == number);
}

int	is_whole_t(double number, double tolerance)
{
	return (round(number) + tolerance >= number
		&& round(number) - tolerance <= number);
}
