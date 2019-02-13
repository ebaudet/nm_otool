/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fabs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 16:39:09 by ebaudet           #+#    #+#             */
/*   Updated: 2019/02/01 18:29:08 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The fabs() functions compute the absolute value of a floating-point
** number <i>.
*/

double		ft_fabs(double i)
{
	if (i < 0)
		return (-i);
	return (i);
}
