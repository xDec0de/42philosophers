/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_builder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 18:55:03 by danimart          #+#    #+#             */
/*   Updated: 2023/09/19 04:33:12 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philosophers.h"

char	*get_state_name(int state)
{
	if (state == DEAD)
		return RED"dead";
	else if (state == INACTIVE)
		return YELLOW"inactive";
	else if (state == EATING)
		return B_GREEN"eating";
	else if (state == F_EATING)
		return B_GREEN"eating"B_GRAY" ("WHITE"Finished"B_GRAY")";
	else if (state == SLEEPING)
		return MAGENTA"sleeping";
	else if (state == F_SLEEPING)
		return MAGENTA"sleeping"B_GRAY" ("WHITE"Finished"B_GRAY")";
	else if (state == THINKING)
		return B_BLUE"thinking";
	return B_RED"broken";
}

t_philo_info	*test_philosophers(t_philo_info* info)
{
	int		id;
	t_philo	philo;

	if (!DEBUG)
		return (info);
	id = 0;
	while (id < info->amount)
	{
		philo = info->philo_lst[id];
		printf(PHILO_STATE, id, get_state_name(philo.state));
		id++;
	}
	return (info);
}

t_philo_info	*build_philosophers(t_philo_info *info)
{
	t_philo	philo;
	int		id;

	id = 0;
	while (id < info->amount)
	{
		philo.id = id;
		philo.state = INACTIVE;
		philo.fork = FK_NONE;
		info->philo_lst[id] = philo;
		id++;
	}
	return (test_philosophers(info));
}
