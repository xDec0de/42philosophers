/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:05:44 by danimart          #+#    #+#             */
/*   Updated: 2022/06/03 15:59:12 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo_info	*parse_arguments(int argc, char **args)
{
	t_philo_info	info;
	t_philo_info	*res;

	(void) args;
	if (argc < 5 || argc > 6)
		print_error(ARGC_ERR);
	info.amount = 10;
	res = &info;
	return (res);
}
