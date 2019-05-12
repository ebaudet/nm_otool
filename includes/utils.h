/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/24 19:51:44 by ebaudet           #+#    #+#             */
/*   Updated: 2019/05/09 23:09:44 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# define FLAG_P		0b1
# define FLAG_PCAPS	0b10
# define FLAG_R		0b100
# define FLAG_ARCH	0b1000
# define FLAG_BIGEN	0b10000
# define FLAG_N		0b100000
# define FLAG_PRINT	0b1000000
# define FLAG_PPC	0b10000000

long long int		ft_pow(int nb, unsigned int pow);
void				ft_puthex(long long int nb, int width);
char				*ft_gethex(long long int nb, int width);

/*
** endian_swap.c
*/
unsigned int		endian_swap(unsigned int x);
unsigned long		lendian_swap(unsigned long x);
unsigned int		bed(unsigned int x, int flag);
unsigned long		lbed(unsigned long x, int flag);

#endif
