/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_secure.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 12:31:43 by ebaudet           #+#    #+#             */
/*   Updated: 2019/05/09 21:17:18 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/*
** Store the size of the file.
*/

int		get_size(int size)
{
	static int	static_size = -1;

	if (static_size == -1 || size >= 0)
		static_size = size;
	return (static_size);
}

/*
** Store the original ptr of a function.
*/

char	*get_ptr(char *ptr)
{
	static char	*static_ptr = NULL;

	if (static_ptr == NULL || ptr != NULL)
		static_ptr = ptr;
	return (static_ptr);
}

/*
** check if the given <ptr> is inside the defined file or not.
** return 0 if error. 1 if success
*/

int		sec_ptr(char *ptr)
{
	char	*start_ptr;
	int		file_size;

	if ((start_ptr = get_ptr(NULL)) <= 0)
		return (0);
	if ((file_size = get_size(-1)) < 0)
		return (0);
	if ((ptr >= start_ptr) && (ptr < (start_ptr + file_size)))
		return (1);
	return (0);
}
