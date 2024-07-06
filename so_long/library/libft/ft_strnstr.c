/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mustyilm <mustyilm@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:07:44 by mustyilm          #+#    #+#             */
/*   Updated: 2023/10/19 15:11:04 by mustyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	hay;
	size_t	need;

	hay = 0;
	if (*needle == 0)
		return ((char *)haystack);
	while (haystack[hay] != 0 && hay < n)
	{
		need = 0;
		while (haystack[hay + need] == needle[need]
			&& needle[need] && need + hay < n)
			need++;
		if (need == ft_strlen(needle))
			return ((char *)&haystack[hay]);
		hay++;
	}
	return (NULL);
}
