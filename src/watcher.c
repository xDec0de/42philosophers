/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:08:05 by daniema3          #+#    #+#             */
/*   Updated: 2025/08/04 16:00:56 by daniema3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	on_philo_death(t_philo *philo)
{
	int	id;
	int	dead_id;
	int	ms;

	id = 0;
	dead_id = philo->id;
	ms = get_current_ms(philo->info);
	while (id < philo->info->philo_n)
	{
		philo = philo->info->philo_lst[id];
		pthread_mutex_lock(philo->m_state);
		philo->state = PAUSED;
		pthread_mutex_unlock(philo->m_state);
		id++;
	}
	free_info(philo->info);
	printf(PHILO_DIED, ms, dead_id);
	return (false);
}

bool	launch_watcher(t_philo_info *info)
{
	int				id;
	t_philo_state	state;
	int				inactive;
	int				ms;

	id = 0;
	inactive = 0;
	while (id < info->philo_n)
	{
		pthread_mutex_lock(info->philo_lst[id]->m_state);
		state = info->philo_lst[id]->state;
		pthread_mutex_unlock(info->philo_lst[id]->m_state);
		if (state == DEAD)
			return (on_philo_death(info->philo_lst[id]));
		else if (state == INACTIVE)
			inactive++;
		id++;
	}
	if (inactive != info->philo_n)
		return (true);
	ms = get_current_ms(info);
	free_info(info);
	printf(ALL_SURVIVED, ms);
	return (false);
}
