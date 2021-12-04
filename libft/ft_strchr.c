/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aignacz <aignacz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 14:54:54 by aignacz           #+#    #+#             */
/*   Updated: 2021/05/17 22:19:02 by aignacz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	char	*p;
	char	ch;

	p = (char *) s;
	ch = (char) c;
	while (*p && *p != ch)
		p++;
	if (*p != ch)
		p = 0;
	return (p);
}
