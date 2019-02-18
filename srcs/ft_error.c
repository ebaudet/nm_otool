/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/27 20:54:13 by ebaudet           #+#    #+#             */
/*   Updated: 2019/02/18 17:44:27 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "libftprintf.h"

int		print_error(char *message)
{
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	return (EXIT_FAILURE);
}

int		file_error(char *message, char *file, char *function)
{
	ft_printf_fd(2, "%s: %s %s\n", function, file, message);
	return (EXIT_FAILURE);
}
