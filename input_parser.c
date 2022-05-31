/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:05:44 by danimart          #+#    #+#             */
/*   Updated: 2022/05/31 14:07:24 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo_info	parse_arguments(int argc, char **args)
{
	t_philo_info	info;

	(void) args;
	(void) argc;
	info.amount = 10;
	return (info);
}
