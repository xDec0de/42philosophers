/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 20:33:26 by danimart          #+#    #+#             */
/*   Updated: 2023/10/07 18:08:48 by danimart         ###   ########.fr       */
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

void	*mutex_unlock(pthread_mutex_t *mutex, void *res, int destroy)
{
	pthread_mutex_unlock(mutex);
	if (destroy)
	{
		pthread_mutex_destroy(mutex);
		free(mutex);
	}
	return (res);
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
