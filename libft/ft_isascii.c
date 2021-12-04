/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 18:19:41 by aignacz           #+#    #+#             */
/*   Updated: 2021/05/17 21:47:34 by aignacz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int c)
{
	int	out;

	if (c >= '\0' && c <= 127)
		out = 1;
	else
		out = 0;
	return (out);
}
