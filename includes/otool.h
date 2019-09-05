/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 12:32:23 by ebaudet           #+#    #+#             */
/*   Updated: 2019/09/05 21:35:47 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTOOL_H
# define OTOOL_H

# include <stdbool.h>
# include "utils.h"

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
	char			*ptr_file;
	char			*ptr;
	unsigned int	segment;
	int				flag;
	unsigned int	nfat_arch;
	bool			isFat;
}				t_otool;

#endif
