/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 11:07:00 by sdi-lega          #+#    #+#             */
/*   Updated: 2022/06/10 16:59:29 by abkasmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	and(t_comm *first, t_env *env)
{
	char	**env_array;
	t_comm	*second;

	env_array = list_to_array(env);
	function(first->parameters, env, env_array);
	second->func(second, second->next);
	free(env_array);
}
