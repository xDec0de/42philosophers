/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 20:33:03 by daniema3          #+#    #+#             */
/*   Updated: 2025/08/01 21:54:42 by daniema3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	is_philo_dead(t_philo *philo)
{
	int	current_ms;

	current_ms = get_current_ms(philo->info);
	return ((current_ms - philo->last_meal_ms) >= philo->info->die_ms);
}

void	launch_philo(t_philo *philo)
{
	while (true)
	{
		p_printf(PHILO_THINKING, get_current_ms(philo->info), philo->id);
		if (is_philo_dead(philo))
			break ;
		p_printf(PHILO_SLEEPING, get_current_ms(philo->info), philo->id);
		p_sleep(philo->info->sleep_ms);
	}
	pthread_mutex_lock(philo->m_state);
	philo->state = INACTIVE;
	pthread_mutex_unlock(philo->m_state);
}
