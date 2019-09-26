/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sizeof_segment_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 13:45:00 by ebaudet           #+#    #+#             */
/*   Updated: 2019/09/26 13:53:59 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

size_t	sizeof_segment_command(t_arch arch)
{
	if (arch == E_32B)
		return (sizeof(struct segment_command));
	return (sizeof(struct segment_command_64));
}
