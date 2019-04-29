/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_filewithanameverylongtotestwhatisthecomportementofthefunctionnmewiththearchive.c:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 11:06:05 by ebaudet           #+#    #+#             */
/*   Updated: 2019/04/29 18:14:04 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*
** The bzero() function writes <n> zeroed bytes to the string <s>.
** If <n> is zero, bzero() does nothing.
*/

void	ft_filewithanameverylongtotestwhatisthecomportementofthefunctionnmewiththearchive(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
