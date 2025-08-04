/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:08:05 by daniema3          #+#    #+#             */
/*   Updated: 2025/08/04 18:39:19 by daniema3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	on_philo_death(t_philo *philo)
{
	int	id;
	int	dead_id;
	int	ms;

	pthread_mutex_unlock(philo->m_last_meal_ms);
	id = 0;
	dead_id = philo->id;
	ms = get_current_ms(philo->info);
	while (id < philo->info->philo_n)
	{
		philo = philo->info->philo_lst[id];
		pthread_mutex_lock(philo->m_last_meal_ms);
		philo->last_meal_ms = LAST_MEAL_MS_DONE;
		pthread_mutex_unlock(philo->m_last_meal_ms);
		id++;
	}
	free_info(philo->info);
	printf(PHILO_DIED, ms, dead_id);
	return (false);
}

bool	launch_watcher(t_philo_info *info)
{
	int		id;
	int		inactive;
	t_philo	*philo;
	int		ms;

	id = 0;
	inactive = 0;
	ms = get_current_ms(info);
	while (id < info->philo_n)
	{
		philo = info->philo_lst[id];
		pthread_mutex_lock(philo->m_last_meal_ms);
		if (philo->last_meal_ms == LAST_MEAL_MS_DONE)
			inactive++;
		else if ((ms - philo->last_meal_ms) > info->die_ms)
			return (on_philo_death(philo));
		id++;
		pthread_mutex_unlock(philo->m_last_meal_ms);
	}
	if (inactive != info->philo_n)
		return (true);
	free_info(info);
	printf(ALL_SURVIVED, ms);
	return (false);
}
