/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdi-lega <sdi-lega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 11:07:00 by sdi-lega          #+#    #+#             */
/*   Updated: 2022/06/10 15:14:57 by sdi-lega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	and(t_comm *first, t_env *env)
{
	char	**env_array;

	env_array = list_to_array(env);
	function(first->parameters, env, env_array);
	second->func(second, second->next);
	free(env_array);
}
