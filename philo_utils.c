/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 16:51:49 by danimart          #+#    #+#             */
/*   Updated: 2023/10/13 18:45:26 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philosophers.h"

t_philo	*pause_philo(t_philo *philo, u_int64_t ms)
{
	useconds_t	to_match;

	to_match = get_current_ms(philo->prog_info) + ms;
	while (get_current_ms(philo->prog_info) < to_match)
	{
		mutex_lock(philo->m_dead);
		if (philo->dead == 1)
		{
			mutex_unlock(philo->m_dead, 0);
			return (NULL);
		}
		mutex_unlock(philo->m_dead, 0);
		usleep(100);
	}
	return (philo);
}

t_philo	*set_philo_state(t_philo *philo, int state, int print)
{
	char	*state_str;

	mutex_lock(philo->m_dead);
	if (philo->dead == 1)
	{
		mutex_unlock(philo->m_dead, 0);
		return (NULL);
	}
	if (state == DEAD)
		philo->dead = 1;
	mutex_unlock(philo->m_dead, 0);
	if (!print)
		return (philo);
	if (state == DEAD)
		state_str = PHILO_DIED;
	else if (state == THINKING)
		state_str = PHILO_THINKING;
	else if (state == SLEEPING)
		state_str = PHILO_SLEEPING;
	else if (state == EATING)
		state_str = PHILO_EATING;
	mutex_lock(philo->prog_info->m_print);
	printf(state_str, get_current_ms(philo->prog_info), philo->id);
	mutex_unlock(philo->prog_info->m_print, 0);
	return (philo);
}

int	free_philo(t_philo *philo)
{
	pthread_join(philo->th_id, NULL);
	mutex_unlock(philo->m_fork, 1);
	mutex_unlock(philo->m_meal, 1);
	mutex_unlock(philo->m_dead, 1);
	free(philo);
	return (1);
}
