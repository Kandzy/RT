/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkliukin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 21:32:32 by dkliukin          #+#    #+#             */
/*   Updated: 2018/10/20 21:32:33 by dkliukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/rt.h"
#include "./../include/parsing.h"

int main(int ac, char *av[])
{
	if (ac > 0)
		run_scene(av[1], NULL);
	system("leaks rt | grep -iE \"leak\"");
	return (0);
}