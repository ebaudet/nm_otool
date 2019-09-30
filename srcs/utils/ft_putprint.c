/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 17:53:15 by ebaudet           #+#    #+#             */
/*   Updated: 2019/09/30 19:21:54 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"

void	ft_putprint(char const *s)
{
	int		i;

	if (s)
	{
		i = 0;
		while (!sec_ptr((char*)(&s[i])) && s[i] != 0)
		{
			ft_putchar(s[i]);
			i++;
		}
	}
}
