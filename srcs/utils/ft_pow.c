/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/24 19:50:19 by ebaudet           #+#    #+#             */
/*   Updated: 2019/05/18 01:38:52 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long long int	ft_pow(int nb, unsigned int pow)
{
	unsigned int	i;
	long long int	result;

	if (pow == 0)
		return (1);
	result = nb;
	i = 0;
	while (++i < pow)
		result *= nb;
	return (result);
}
