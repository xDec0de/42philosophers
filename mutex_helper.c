/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 20:33:26 by danimart          #+#    #+#             */
/*   Updated: 2023/10/07 17:40:39 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philosophers.h"

pthread_mutex_t	*mutex_init(int *errors)
{
	pthread_mutex_t	*mutex;
	int				result;

	mutex = malloc(sizeof(pthread_mutex_t));
	result = pthread_mutex_init(mutex, NULL);
	if (result == 0)
		return (mutex);
	printf(MUTEX_ERR);
	if (errors != NULL)
		*errors += 1;
	return (NULL);
}

t_philo	*set_philo_state(t_philo *philo, int state)
{
	char	*state_str;

	pthread_mutex_lock(philo->m_state);
	if (philo->state == DEAD)
		return (NULL);
	if (state == DEAD)
		state_str = PHILO_DIED;
	else if (state == THINKING)
		state_str = PHILO_THINKING;
	else if (state == SLEEPING)
		state_str = PHILO_SLEEPING;
	else if (state == EATING)
		state_str = PHILO_EATING;
	philo->state = state;
	pthread_mutex_unlock(philo->m_state);
	if (state == DEAD)
		return (NULL);
	pthread_mutex_lock(philo->prog_info->m_print);
	printf(state_str, get_current_ms(philo->prog_info), philo->id);
	pthread_mutex_unlock(philo->prog_info->m_print);
	return (philo);
}

int	free_philo(t_philo *philo)
{
	pthread_mutex_unlock(philo->m_r_fork);
	pthread_mutex_destroy(philo->m_r_fork);
	free(philo->m_r_fork);
	pthread_mutex_unlock(philo->m_l_fork);
	pthread_mutex_destroy(philo->m_l_fork);
	free(philo->m_l_fork);
	pthread_mutex_unlock(philo->m_meal);
	pthread_mutex_destroy(philo->m_meal);
	free(philo->m_meal);
	pthread_mutex_unlock(philo->m_state);
	pthread_mutex_destroy(philo->m_state);
	free(philo->m_state);
	pthread_join(philo->th_id, NULL);
	free(philo);
	return (1);
}
