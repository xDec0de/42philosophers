/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:36:41 by danimart          #+#    #+#             */
/*   Updated: 2025/07/21 17:27:23 by daniema3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/* - printf - */
# include <stdio.h>

/* - usleep - */
# include <unistd.h>

/* - INT_MAX macro - */
# include <limits.h>

/* - pthread (Multithreading) related functions - */
# include <pthread.h>

/* - malloc, free & NULL pointer */
# include <stdlib.h>

/* - gettimeofday - */
# include <sys/time.h>

/* - bool type - */
# include <stdbool.h>

# ifndef MAX_PHILOSOPHERS
// The maximum amount of philosophers. 200 by default
#  define MAX_PHILOSOPHERS 200
# endif

// Enum used to represent the different states a philosopher can be in
typedef enum e_philo_state
{
	// Philosopher is currently EATING, next action is SLEEPING.
	EATING,
	// Philosopher is currently SLEEPING, next action is THINKING.
	SLEEPING,
	// Philosopher has finished SLEEPING and should start THINKING.
	THINKING
}	t_philo_state;

struct	s_philo_info;

/**
 * Struct used to represent an actual philosopher
 *
 * Here is all the data stored in this struct:
 * - *prog_info: Program info, ONLY to access the print mutex and fork
 *   availability.
 * - th_id: The thread id of this philosopher.
 * - id: The internal id of this philosopher.
 * - *m_fork: Mutex to interact with t_philo::fork.
 * - *m_ended: Mutex to interact ith t_philo::ended.
 * - ended: 1 means this philosopher is stopped, 0 means its still active.
 * - *m_meal: Mutex to interact with t_philo::meals.
 * - meals: The amount of times this philosopher ate so far.
 * - last_meal: The date of the last meal of this philosopher (millis).
 */
typedef struct s_philo
{
	struct s_philo_info	*prog_info;
	pthread_t			th_id;
	int					id;
	pthread_mutex_t		*m_fork;
	pthread_mutex_t		*m_ended;
	bool				ended;
	pthread_mutex_t		*m_meal;
	int					meals;
	int					last_meal;
	pthread_mutex_t		*m_ready;
	bool				ready;
}			t_philo;

/**
 * Struct used to store program information such as parameters and philosophers
 * 
 * Here is all the data stored in this struct:
 * - amount: The amount of philosophers, this is final.
 * - die_time: The time to die for philosophers, this is final.
 * - eat_time: The time to eat for philosophers, this is final.
 * - sleep_time: The time to sleep for philosophers, this is final.
 * - eat_num: The amount of times every philosopher must eat, this is final.
 * - *philo_lst[MAX_PHILOSOPHERS]: An array of all existing philosophers.
 * - start_date: The date (In milliseconds) when the program started.
 * - *m_print: Mutex for message printing (printf calls).
 * - valid: Either 0 or 1, only 0 when an error ocurred.
 */
typedef struct s_philo_info
{
	int				amount;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				eat_num;
	t_philo			*philo_lst[MAX_PHILOSOPHERS];
	int				start_date;
	pthread_mutex_t	*m_print;
	bool			valid;
	pthread_mutex_t	*m_ready;
	bool			ready;
}				t_philo_info;

/* Input error messages */

// Input error: Invalid argument count - Too many arguments
# define ARGC_LONG "\e[0;31mError\e[1;30m: \e[1;31mToo many arguments\
\e[1;30m.\e[0m\n"

// Input error: Invalid argument count - Missing arguments title
# define ARGC_SMALL "\e[0;31mError\e[1;30m: \e[1;31mThe following\
 program arguments are missing\e[1;30m:\e[0m\n"

// Input error: Invalid argument count - Missing argument description
# define MISSING_ARG " \e[1;30m- \e[0;31m%s\e[1;30m.\e[0m\n"

// Input error: Invalid argument - Amount of philosophers
# define AMOUNT_ERR "\e[0;31mError\e[1;30m: \e[1;31mInvalid number\
 of philosophers \e[1;30m[\e[1;33m1\e[1;30m-\e[1;33m%d\e[1;30m]\e[0m\n"

// Input warning: Too many philosophers - Using over 200 philosophers
# define AMOUNT_WARN "\e[0;33mWarning\e[1;30m: \e[1;33mUsing over\
 200 philosophers is not recommended\e[1;30m.\e[0m\n"

// Input error: Invalid argument - Time to die
# define DIE_TIME_ERR "\e[0;31mError\e[1;30m: \e[1;31mInvalid time\
 to die\e[1;30m.\e[0m\n"

// Input error: Invalid argument - Time to eat
# define EAT_TIME_ERR "\e[0;31mError\e[1;30m: \e[1;31mInvalid time\
 to eat\e[1;30m.\e[0m\n"

// Input error: Invalid argument - Time to sleep
# define SLEEP_TIME_ERR "\e[0;31mError\e[1;30m: \e[1;31mInvalid time\
 to sleep\e[1;30m.\e[0m\n"

// Input error: Invalid argument - Times to eat
# define EAT_NUM_ERR "\e[0;31mError\e[1;30m: \e[1;31mInvalid amount\
 of times to eat\e[1;30m.\e[0m\n"

/* External error messages */

// Internal error: Thread creation
# define THREAD_ERR "\e[0;31mError\e[1;30m: \e[1;31mCould not create\
 a new thread\e[1;30m.\e[0m\n"

// Internal error: Get time of day
# define GET_TIME_ERR "\e[0;31mError\e[1;30m: \e[1;31mCould not get current\
 time\e[1;30m.\e[0m\n"

// Internal error: Mutex creation
# define MUTEX_ERR "\e[0;31mError\e[1;30m: \e[1;31mCould not create\
 a new mutex\e[1;30m.\e[0m\n"

// Internal error: Malloc
# define MALLOC_ERR "\e[0;31mError\e[1;30m: \e[1;31mMalloc failed\e[1;30m.\
\e[0m\n"

/* Philosopher log messages */

// Log message: A philosopher took a fork (Left hand)
# define PHILO_TAKE_RFORK "\e[1;30m[\e[0;33m%llu\e[1;30m] \e[1;33m%d \e[1;37m\
has taken a \e[1;33mfork \e[1;30m(\e[1;34mRight\e[1;30m)\e[0m\n"

// Log message: A philosopher took a fork (Left hand)
# define PHILO_TAKE_LFORK "\e[1;30m[\e[0;33m%llu\e[1;30m] \e[1;33m%d \e[1;37m\
has taken a \e[1;33mfork \e[1;30m(\e[1;34mLeft\e[1;30m)\e[0m\n"

// Log message: A philosopher changed its state to EATING
# define PHILO_EATING "\e[1;30m[\e[0;33m%llu\e[1;30m] \e[1;33m%d \e[1;37m\
is \e[1;35meating\e[1;30m.\e[0m\n"

// Log message: A philosopher changed its state to SLEEPING
# define PHILO_SLEEPING "\e[1;30m[\e[0;33m%llu\e[1;30m] \e[1;33m%d \e[1;37m\
is \e[1;36msleeping\e[1;30m.\e[0m\n"

// Log message: A philosopher changed its state to THINKING
# define PHILO_THINKING "\e[1;30m[\e[0;33m%llu\e[1;30m] \e[1;33m%d \e[1;37m\
is \e[1;32mthinking\e[1;30m.\e[0m\n"

// Log message: A philosopher died :( - Simulation ends
# define PHILO_DIED "\e[1;30m[\e[0;31m%llu\e[1;30m] \e[1;31m%d \
died\e[1;30m.\e[0m\n"

// Log message: All philosophers survived - Simulation ends
# define ALL_SURVIVED "\e[1;30m[\e[0;32m%llu\e[1;30m] \e[1;32mAll philosophers\
 ate enough times, ending the simulation\e[1;30m.\e[0m\n"

// The amount of times to try to lock / unock a mutex before giving up.
# define MUTEX_ATTEMPTS 42

/* philosophers.c */

/**
 * @brief Prints an error message, freeing all program info.
 * 
 * @param err the error message to print, if NULL, nothing will be printed.
 * @param info the program info struct, will be freed if necessary, can be NULL.
 * @param result whatever you want this method to return, can be NULL.
 * 
 * @returns Whatever was specified as a result, can be NULL.
 */
void			*free_info(char *err, t_philo_info *info, void *result);

/* input_parser.c */

// Parses program arguments to create a t_philo_info struct
/**
 * @brief Parses program arguments to create a t_philo_info struct.
 * 
 * @param argc the argument count of the program (Directly from main)
 * @param argv the argument values of the program (Directly from main)
 * 
 * @return The info struct, NULL if any argument was invalid.
 */
t_philo_info	*parse_arguments(int argc, char **argv);

/* philo_builder.c */

/**
 * @brief Builds all required philosophers and creates a thread for each one.
 * 
 * @param info the program info struct.
 * 
 * @return The program info struct with all created philosophers,
 * NULL if any error occurs.
 */
t_philo_info	*build_philosophers(t_philo_info *info);

/* philo_handler.c */

/**
 * @brief Starts the routine of a philosopher.
 * 
 * @param philo_ptr a void pointer of any philosopher (t_philo).
 * 
 * @return The same pointer that was supplied to this function,
 * this is pretty irrelevant as this is meant to run on a different
 * thread for any amount of time.
 */
void			*philo_routine(void *philo_ptr);

/* mutex_helper.c */

/**
 * @brief Creates a mutex, handling any error that occurs by returning
 * NULL and printing the error. Info won't be freed.
 * 
 * @param errors a nullable integer pointer that will increase by one
 * if pthread_mutex_init fails.
 * 
 * @return A new pthread_mutex_t pointer. NULL if any error occurs.
 */
pthread_mutex_t	*mutex_init(int	*errors);

/**
 * @brief Unlocks a mutex and optionally destoys and frees it. This method
 * will try to unlock the mutex up to MUTEX_ATTEMPTS times if any error occurs.
 * 
 * @param mutex the pthread_mutex_t to unlock and optionally destroy.
 * @param destroy whether to to destroy and free mutex.
 * 
 * @return true on success, false on failure. Failure will only
 * happen after attempting MUTEX_ATTEMPTS times.
 */
bool			mutex_unlock(pthread_mutex_t *mutex, bool destroy);

/**
 * @brief Locks a mutex. This method will try to unlock the mutex up
 * to `MUTEX_ATTEMPTS` times if any error occurs.
 * 
 * @param mutex the `pthread_mutex_t` to lock.
 * 
 * @return true on success, false on failure. Failure will only
 * happen after attempting `MUTEX_ATTEMPTS` times.
 */
bool			mutex_lock(pthread_mutex_t *mutex);

/**
 * @brief Locks the fork mutex of a philosopher.
 * 
 * @param philo the philosopher to use.
 * @return `NULL` if the philosopher dies before the fork is locked,
 * `philo` otherwise.
 */
void			*lock_fork(t_philo *philo);

/** philo_utils.c */

/**
 * @brief Gets the current timestamp of the program (Milliseconds since start)
 * 
 * @param info the program info struct, used to get `t_philo_info::start_date`
 * and to `free` said struct if an error occurs.
 * 
 * @return The current timestamp of the program, `-1` if an error occurred.
 */
int				get_current_ms(t_philo_info *info);

/**
 * @brief Gets the current time of the system in milliseconds.
 * This is used to get the current time of the system, not the
 * current time of the program.
 * 
 * @param info the program info struct, `free`'d if an error occurs.
 * 
 * @return The current time in milliseconds, `-1` if an error occurred.
 */
int				get_current_time(t_philo_info *info);

/**
 * @brief Pauses a thread for the specified amount of ms, this
 * function must be called from the thread of the specified philo,
 * as this will check if the program is trying to end while this
 * philosopher thread is paused.
 * 
 * @param philo the philosopher that is going to be paused.
 * @param ms the time in milliseconds that that the thread will be paused.
 * 
 * @return The same philosopher that was supplied to this function.
 */
t_philo			*pause_philo(t_philo *philo, int ms);

/**
 * @brief Changes the state of a philosopher, the state will
 * be changed safely and a state change message will be printed,
 * also safely. But the philosopher won't start any action, this
 * is just to change data internally and to notify about changes.
 * 
 * @param philo the philosopher to change.
 * @param state the new state of the philosopher.
 * @param print whether to print the new state message or not.
 * 
 * @return The same philosopher that was supplied to this function.
 */
t_philo			*set_philo_state(t_philo *philo, t_philo_state state,
					bool print);

/**
 * @brief Frees all philosophers, joining their threads first to avoid
 * unexpected behaviour.
 * 
 * @param info the program info.
 */
void			free_philos(t_philo_info *info);

#endif