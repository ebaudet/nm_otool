/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/24 19:50:19 by ebaudet           #+#    #+#             */
/*   Updated: 2014/04/24 19:50:32 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long long int		ft_pow(int nb, int pow)
{
	int				i;
	long long int	result;

	if (pow == 0)
		return (1);
	result = nb;
	i = 1;
	while (i < pow)
	{
		result *= nb;
		i++;
	}
	return (result);
}
