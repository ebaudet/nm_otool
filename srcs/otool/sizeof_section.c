/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sizeof_section.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 13:45:51 by ebaudet           #+#    #+#             */
/*   Updated: 2019/09/26 13:53:51 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

size_t	sizeof_section(t_arch arch)
{
	if (arch == E_32B)
		return (sizeof(struct section));
	return (sizeof(struct section_64));
}
