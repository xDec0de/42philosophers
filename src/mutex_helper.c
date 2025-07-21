/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 20:33:26 by danimart          #+#    #+#             */
/*   Updated: 2025/07/21 18:50:49 by daniema3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

pthread_mutex_t	*mutex_init(int *errors)
{
	pthread_mutex_t	*mutex;
	int				result;

	mutex = malloc(sizeof(pthread_mutex_t));
	if (mutex == NULL)
		return (printf(MALLOC_ERR), NULL);
	result = pthread_mutex_init(mutex, NULL);
	if (result == 0)
		return (mutex);
	printf(MUTEX_ERR);
	if (errors != NULL)
		*errors += 1;
	return (NULL);
}

bool	mutex_unlock(pthread_mutex_t *mutex, bool destroy)
{
	if (pthread_mutex_unlock(mutex) != 0)
		return (false);
	if (destroy)
	{
		if (pthread_mutex_destroy(mutex) != 0)
			return (false);
		free(mutex);
	}
	return (true);
}

bool	mutex_lock(pthread_mutex_t *mutex)
{
	return (pthread_mutex_lock(mutex) == 0);
}

void	*lock_fork(t_philo *philo)
{
	bool	ended;

	mutex_lock(philo->m_ended);
	ended = philo->ended;
	mutex_unlock(philo->m_ended, false);
	if (ended)
		return (NULL);
	mutex_lock(philo->m_fork);
	return (philo);
}
