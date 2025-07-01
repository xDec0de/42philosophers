/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 20:33:26 by danimart          #+#    #+#             */
/*   Updated: 2025/07/01 20:48:02 by daniema3         ###   ########.fr       */
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
	int	err;
	int	attempts;

	attempts = 0;
	err = 1;
	while (err != 0 && attempts < MUTEX_ATTEMPTS)
	{
		err = pthread_mutex_unlock(mutex);
		attempts++;
	}
	if (err != 0 || !destroy)
		return (err == 0);
	attempts = 0;
	err = 1;
	while (err != 0 && attempts < MUTEX_ATTEMPTS)
	{
		err = pthread_mutex_destroy(mutex);
		attempts++;
	}
	free(mutex);
	return (err == 0);
}

bool	mutex_lock(pthread_mutex_t *mutex)
{
	int	err;
	int	attempts;

	attempts = 0;
	err = 1;
	while (err != 0 && attempts < MUTEX_ATTEMPTS)
	{
		err = pthread_mutex_lock(mutex);
		attempts++;
	}
	return (err == 0);
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
