/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 16:42:15 by ebaudet           #+#    #+#             */
/*   Updated: 2019/02/01 18:40:34 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** The memccpy() function copies bytes from string <src> to string <dst>.
** If the character <c> (as converted to an unsigned char) occurs in
** the string <src>, the copy stops and a pointer to the byte after the copy
** of <c> in the string <dst> is returned.  Otherwise, <n> bytes are copied,
** and a NULL pointer is returned.
**
** The source and destination strings should not overlap, as the behavior
** is undefined.
*/

void	*ft_memccpy(void *dst, void const *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	if (!dst || !src)
		return (NULL);
	ptr1 = (unsigned char *)dst;
	ptr2 = (unsigned char *)src;
	i = 0;
	while (n--)
	{
		ptr1[i] = ptr2[i];
		if (ptr2[i] == c)
			return (ptr1 + i + 1);
		i++;
	}
	return (NULL);
}
