/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 12:32:23 by ebaudet           #+#    #+#             */
/*   Updated: 2019/05/18 01:37:46 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTOOL_H
# define OTOOL_H

typedef enum	te_arch
{
	E_32B,
	E_64B
}				e_arch;

typedef enum	te_end
{
	E_BIG,
	E_LITTLE
}				e_end;

typedef struct	s_otool
{
	e_arch			arch;
	e_end			endian;
	char			*file;
	char			*ptr;
	unsigned int	segment;
}				t_otool;

#endif
