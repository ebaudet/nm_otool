/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 12:32:09 by ebaudet           #+#    #+#             */
/*   Updated: 2019/02/15 01:19:30 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

int				print_error(char *message);
int				file_error(char *message, char *file);
unsigned int	endian_swap(unsigned int x);

typedef struct			s_ftnm
{
	unsigned long	offset;
	char			symbol;
	char			*table_index;
	struct s_ftnm	*next;
}						t_ftnm;

#endif
