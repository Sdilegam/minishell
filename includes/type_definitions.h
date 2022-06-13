/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_definitions.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 11:04:56 by sdi-lega          #+#    #+#             */
/*   Updated: 2022/06/13 13:28:50 by abkasmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_DEFINITIONS_H
# define TYPE_DEFINITIONS_H

typedef struct s_env
{
	char			*var;
	char			*content;
	struct s_env	*next;
}				t_env;

typedef struct s_var
{
	char	*name;
	char	*content;
}			t_var;

typedef struct s_comm
{
	char			**parameters;
	int				(*func)(struct s_comm *first, struct s_env *env, int n_p);
	struct s_comm	*previous;
	struct s_comm	*next;
}			t_comm;

#endif /* TYPE_DEFINITIONS_H */
