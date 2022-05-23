/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdi-lega <sdi-lega@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 12:59:38 by abkasmi           #+#    #+#             */
/*   Updated: 2022/05/23 16:44:04 by sdi-lega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	function(char *rl)
{
	char	*test[3];
	char	*test1[1];
	
	test[1] = "0";
	test[0] = rl;
	test[1] = "test";
	test[2] = 0;
	if (fork() == 0)
		execve(test[0], test, test1);
}


int	main(void)
{
	char	*rl;
	int		*test;

	print_header();
	while (1)
	{
		rl = readline("minishell:$>");
		printf("%d\n", count_words(rl));
		free(rl);
	}
}
