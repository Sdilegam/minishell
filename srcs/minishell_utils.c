/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdi-lega <sdi-lega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:34:18 by sdi-lega          #+#    #+#             */
/*   Updated: 2022/05/23 16:42:38 by sdi-lega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char chara)
{
	if (!chara)
		return (0);
	if (chara == ' ')
		return (1);
	return (0);
}

int	is_alpha(char chara)
{
	if (!chara)
		return (0);
	if (('a' <= chara && chara <= 'z') || ('A' <= chara && chara <= 'Z'))
		return (1);
	return (0);
}
