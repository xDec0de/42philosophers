/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:36:41 by danimart          #+#    #+#             */
/*   Updated: 2023/09/30 16:22:55 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <limits.h>
# include <pthread.h>
# include <stdlib.h>
# include "philosopher.h"

// Struct used to store program information such as parameters and philosophers
typedef struct s_philo_info {
	int		amount;
	int		die_time;
	int		eat_time;
	int		sleep_time;
	int		eat_num;
	t_philo	philo_lst[MAX_PHILOSOPHERS];
}				t_philo_info;

/* Error messages */

// Invalid argument count.
# define ARGC_ERR "\e[0;31mError\e[1;30m: \e[1;31mInvalid input\
\e[1;30m.\e[0m\n"
// Invalid amount of philosophers.
# define AMOUNT_ERR "\e[0;31mError\e[1;30m: \e[1;31mInvalid number\
 of philosophers \e[1;30m(\e[1;33mMax is %d\e[1;30m)\e[0m\n"
// Warn philosophers over 200 if a higher amount is allowed.
# define AMOUNT_WARN "\e[0;33mWarning\e[1;30m: \e[1;33mUsing over\
 200 philosophers is not recommended\e[1;30m.\e[0m\n"
// Invalid time to die.
# define DIE_TIME_ERR "\e[0;31mError\e[1;30m: \e[1;31mInvalid time\
 to die\e[1;30m.\e[0m\n"
// Invalid time to eat.
# define EAT_TIME_ERR "\e[0;31mError\e[1;30m: \e[1;31mInvalid time\
 to eat\e[1;30m.\e[0m\n"
// Invalid time to sleep.
# define SLEEP_TIME_ERR "\e[0;31mError\e[1;30m: \e[1;31mInvalid time\
 to sleep\e[1;30m.\e[0m\n"
// Invalid amount of times to eat.
# define EAT_NUM_ERR "\e[0;31mError\e[1;30m: \e[1;31mInvalid amount\
 of times to eat\e[1;30m.\e[0m\n"
// Error creating a thread.
# define THREAD_ERR "\e[0;31mError\e[1;30m: \e[1;31mCould not create\
 a new thread\e[1;30m.\e[0m\n"

/* Debug messages, debug should be disabled on evaluation just in case */

// Notication message sent if debug mode is on
# define DEBUG_NOTE "\e[1;37mDebug \e[1;32menabled\e[1;37m, run\
 \e[1;33mmake re DEBUG=0 \e[1;37mto disable\e[1;30m.\e[0m\n"
// Header of the program info
# define INFO_HEADER "\n\e[0;37m|-------------------------->\e[0m\n"
// Info slot about the program with a numeric value
# define INFO_NUM "\e[1;31m* \e[1;37m%s\e[1;30m: \e[0;33m%d\e[0m\n"
// Footer of the program info
# define INFO_FOOTER "\e[0;37m|-------------------------->\e[0m\n\n"
// Prefix used for debug messages
# define DEBUG_PREFIX "\e[1;30m[\e[1;37mDEBUG\e[1;30m]\e[0m"
// Philosopher state debug message
# define PHILO_STATE " \e[0;37mPhilosopher \e[0;33m%i\e[0;37m\
 is %s\e[1;30m.\e[0m\n"

/* Philosopher log messages */

// A philosopher takes a fork (Right hand).
# define PHILO_TAKE_RFORK "\e[1;30m[\e[0;33m%d\e[1;30m] \e[1;33m%d \e[1;37m\
has taken a \e[1;33mfork \e[1;30m(\e[1;34mRight\e[1;30m)\e[0m\n"
// A philosopher takes a fork (Left hand).
# define PHILO_TAKE_LFORK "\e[1;30m[\e[0;33m%d\e[1;30m] \e[1;33m%d \e[1;37m\
has taken a \e[1;33mfork \e[1;30m(\e[1;34mLeft\e[1;30m)\e[0m\n"
// A philosopher is eating
# define PHILO_EATING "\e[1;30m[\e[0;33m%d\e[1;30m] \e[1;33m%d \e[1;37m\
is \e[1;35mmeating\e[1;30m.\e[0m\n"
// A philosopher is sleeping.
# define PHILO_SLEEPING "\e[1;30m[\e[0;33m%d\e[1;30m] \e[1;33m%d \e[1;37m\
is \e[1;36msleeping\e[1;30m.\e[0m\n"
// A philosopher is thinking.
# define PHILO_THINKING "\e[1;30m[\e[0;33m%d\e[1;30m] \e[1;33m%d \e[1;37m\
is \e[1;32mthinking\e[1;30m.\e[0m\n"
// A philosopher died :(
# define PHILO_DIED "\e[1;30m[\e[0;31m%d\e[1;30m] \e[1;31m%d \
died\e[1;30m.\e[0m\n"

/* philosophers.c */

void			exit_error(char *err, t_philo_info *info);

/* input_parser.c */

t_philo_info	*parse_arguments(int argc, char **argv);

/* philo_builder.c */

t_philo_info	*build_philosophers(t_philo_info *info);

/* debug_helper.c */

t_philo_info	*test_philosophers(t_philo_info *info);

#endif