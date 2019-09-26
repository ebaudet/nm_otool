/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_in_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 02:31:42 by ebaudet           #+#    #+#             */
/*   Updated: 2019/09/26 13:29:30 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_in_array(const unsigned int *haystack, size_t size, unsigned int needle)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (haystack[i] == needle)
			return (1);
		i++;
	}
	return (0);
}
