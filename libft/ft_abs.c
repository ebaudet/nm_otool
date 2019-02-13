/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 16:39:09 by ebaudet           #+#    #+#             */
/*   Updated: 2019/02/01 18:26:56 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The abs() function computes the absolute value of the integer <i>.
*/

int		ft_abs(int i)
{
	if (i < 0)
		return (-i);
	return (i);
}
