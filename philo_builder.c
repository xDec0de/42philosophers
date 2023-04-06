/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_builder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 18:55:03 by danimart          #+#    #+#             */
/*   Updated: 2023/04/06 19:36:47 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philosophers.h"

t_philo_info	*build_philosophers(t_philo_info *info)
{
	t_philo			philo;
	int				id;

	id = 0;
	while (id < info->amount)
	{
		philo.id = id;
		philo.state = INACTIVE;
		philo.fork = FK_NONE;
		info->philo_lst[id] = philo;
		id++;
	}
	return (info);
}
