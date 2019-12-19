/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/27 20:54:13 by ebaudet           #+#    #+#             */
/*   Updated: 2019/12/19 17:49:15 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int		print_error(char *message)
{
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	return (EXIT_FAILURE);
}

int		file_error(char *message, char *file)
{
	ft_putstr_fd(file, 2);
	ft_putstr_fd(" ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	return (EXIT_FAILURE);
}

int		sec_error(char *file)
{
	return (file_error("truncated or malformed object (load commands ex\
tend past the end of the file)", file));
}
