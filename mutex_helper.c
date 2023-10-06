/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 20:33:26 by danimart          #+#    #+#             */
/*   Updated: 2023/10/06 21:19:42 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philosophers.h"

pthread_mutex_t	*mutex_init(int *errors)
{
	pthread_mutex_t	mutex;
	pthread_mutex_t	*mutex_ptr;
	int				result;

	result = pthread_mutex_init(&mutex, NULL);
	mutex_ptr = &mutex;
	if (result == 0)
		return (mutex_ptr);
	printf(MUTEX_ERR);
	if (errors != NULL)
		*errors += 1;
	return (NULL);
}

t_philo	*set_philo_state(t_philo *philo, int state)
{
	char	*state_str;

	if (sim_ended(philo->prog_info))
		return (philo);
	if (state == DEAD)
		state_str = PHILO_DIED;
	else if (state == THINKING)
		state_str = PHILO_THINKING;
	else if (state == SLEEPING)
		state_str = PHILO_SLEEPING;
	else if (state == EATING)
		state_str = PHILO_EATING;
	pthread_mutex_lock(philo->m_state);
	philo->state = state;
	pthread_mutex_lock(philo->prog_info->m_print);
	printf(state_str, get_current_ms(philo->prog_info), philo->id);
	pthread_mutex_unlock(philo->prog_info->m_print);
	pthread_mutex_unlock(philo->m_state);
	return (philo);
}

int	sim_ended(t_philo_info *info)
{
	int	ended;

	pthread_mutex_lock(info->m_ended);
	ended = info->ended;
	pthread_mutex_unlock(info->m_ended);
	return (ended);
}

int	free_philo(t_philo *philo)
{
	pthread_detach(philo->th_id);
	pthread_mutex_unlock(philo->m_fork);
	pthread_mutex_destroy(philo->m_fork);
	pthread_mutex_unlock(philo->m_meal);
	pthread_mutex_destroy(philo->m_meal);
	pthread_mutex_unlock(philo->m_state);
	pthread_mutex_destroy(philo->m_state);
	free(philo);
	return (1);
}
