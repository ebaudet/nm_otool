/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/27 20:54:13 by ebaudet           #+#    #+#             */
/*   Updated: 2019/05/09 21:24:06 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "libftprintf.h"
#include "nm.h"

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

int		nm_error(char *message, t_nm *nm)
{
	ft_printf_fd(2, "%s: %s %s\n", nm->command, nm->file, message);
	return (EXIT_FAILURE);
}
