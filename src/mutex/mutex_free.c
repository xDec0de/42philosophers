/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 15:52:25 by daniema3          #+#    #+#             */
/*   Updated: 2025/07/31 19:12:24 by daniema3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	mutex_free(pthread_mutex_t *mutex)
{
	if (mutex == NULL)
		return (true);
	if (pthread_mutex_unlock(mutex) != 0)
		return (false);
	err = pthread_mutex_destroy(mutex);
	if (err != 0)
		return (false);
	free(mutex);
	return (true);
}