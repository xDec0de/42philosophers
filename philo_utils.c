/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 16:51:49 by danimart          #+#    #+#             */
/*   Updated: 2023/10/08 17:08:37 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philosophers.h"

t_philo	*pause_philo(t_philo *philo, useconds_t ms)
{
	useconds_t	i;

	i = 1;
	while (i < ms)
	{
		pthread_mutex_lock(philo->m_state);
		if (philo->state == DEAD)
			return (NULL);
		pthread_mutex_unlock(philo->m_state);
		usleep(1000);
		i++;
	}
	return (philo);
}

t_philo	*set_philo_state(t_philo *philo, int state)
{
	char	*state_str;

	pthread_mutex_lock(philo->m_state);
	if (state == DEAD || philo->state == DEAD)
		return (mutex_unlock(philo->m_state, NULL, 0));
	philo->state = state;
	pthread_mutex_unlock(philo->m_state);
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
	mutex_unlock(philo->m_r_fork, NULL, 1);
	mutex_unlock(philo->m_l_fork, NULL, 1);
	mutex_unlock(philo->m_meal, NULL, 1);
	mutex_unlock(philo->m_state, NULL, 1);
	pthread_join(philo->th_id, NULL);
	free(philo);
	return (1);
}