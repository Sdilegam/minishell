/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 19:31:53 by abkasmi           #+#    #+#             */
/*   Updated: 2022/07/13 19:32:39 by abkasmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;
	char	*ptr;

	ptr = b;
	i = 0;
	while (i < len)
	{
		ptr[i] = c;
		i++;
	}
	return (b);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*str;

	str = malloc(sizeof(char) * (size * nmemb));
	if (!str)
		return (NULL);
	ft_memset(str, 0, (size * nmemb));
	return (str);
}
