/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdi-lega <sdi-lega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 01:30:18 by sdi-lega          #+#    #+#             */
/*   Updated: 2022/06/15 12:24:23 by sdi-lega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*here_doc(char *string)
{
	char	*temp_test = malloc (5);

	(void)string;
	temp_test[0] = 't';
	temp_test[1] = 'e';
	temp_test[2] = 's';
	temp_test[3] = 't';
	temp_test[4] = 0;
	return (temp_test);
}
