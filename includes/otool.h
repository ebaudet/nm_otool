/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 12:32:23 by ebaudet           #+#    #+#             */
/*   Updated: 2019/09/26 13:22:22 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTOOL_H
# define OTOOL_H

# include <stdbool.h>
# include "utils.h"

typedef enum	e_arch
{
	E_32B,
	E_64B
}				t_arch;

typedef enum	e_end
{
	E_BIG,
	E_LITTLE
}				t_end;

typedef struct	s_otool
{
	t_arch			arch;
	t_end			endian;
	char			*file;
	char			*ptr_file;
	char			*ptr;
	unsigned int	segment;
	int				flag;
	unsigned int	nfat_arch;
	bool			is_fat;
}				t_otool;

#endif
