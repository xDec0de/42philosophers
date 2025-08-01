/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 15:52:25 by daniema3          #+#    #+#             */
/*   Updated: 2025/08/01 20:28:42 by daniema3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	mutex_free(pthread_mutex_t *mutex)
{
	bool	success;

	success = true;
	if (mutex == NULL)
		return (true);
	if (pthread_mutex_destroy(mutex) != 0)
		success = false;
	free(mutex);
	return (success);
}
