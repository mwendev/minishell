/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 18:48:24 by aignacz           #+#    #+#             */
/*   Updated: 2021/05/17 21:46:37 by aignacz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t nelem, size_t elsize)
{
	void	*out;

	out = malloc(nelem * elsize);
	if (out != 0)
		ft_bzero(out, nelem * elsize);
	return (out);
}
