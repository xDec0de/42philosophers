/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 16:51:49 by danimart          #+#    #+#             */
/*   Updated: 2023/10/08 18:17:01 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philosophers.h"

t_philo	*pause_philo(t_philo *philo, useconds_t ms)
{
	useconds_t	i;

	i = 1;
	while (i < ms)
	{
		pthread_mutex_lock(philo->m_dead);
		if (philo->dead == 1)
			return (NULL);
		pthread_mutex_unlock(philo->m_dead);
		usleep(1000);
		i++;
	}
	return (philo);
}

t_philo	*set_philo_state(t_philo *philo, int state, int print)
{
	char	*state_str;

	pthread_mutex_lock(philo->m_dead);
	if (philo->dead == 1)
		return (NULL);
	if (state == DEAD)
		philo->dead = 1;
	pthread_mutex_unlock(philo->m_dead);
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
	pthread_mutex_lock(philo->prog_info->m_print);
	printf(state_str, get_current_ms(philo->prog_info), philo->id);
	pthread_mutex_unlock(philo->prog_info->m_print);
	return (philo);
}

int	free_philo(t_philo *philo)
{
	mutex_unlock(philo->m_fork, NULL, 1);
	mutex_unlock(philo->m_meal, NULL, 1);
	mutex_unlock(philo->m_dead, NULL, 1);
	pthread_join(philo->th_id, NULL);
	free(philo);
	return (1);
}
