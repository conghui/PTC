/**\file */
#ifndef SLIC_DECLARATIONS_FindWindowMaxAndRadius_H
#define SLIC_DECLARATIONS_FindWindowMaxAndRadius_H
#include "MaxSLiCInterface.h"
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define FindWindowMaxAndRadius_maxWindowSize (9)
#define FindWindowMaxAndRadius_PCIE_ALIGNMENT (16)


/*----------------------------------------------------------------------------*/
/*---------------------------- Interface weighted ----------------------------*/
/*----------------------------------------------------------------------------*/




/**
 * \brief Basic static function for the interface 'weighted'.
 * Runs moving average with weighting.
 * \param [in] param_size Interface Parameter "size".
 * \param [in] param_weights Interface Parameter array weights[] should be of size 3.
 * \param [in] instream_x The stream should be of size (param_size * 4) bytes.
 * \param [out] outstream_y The stream should be of size (param_size * 4) bytes.
 */
void FindWindowMaxAndRadius_weighted(
	int32_t param_size,
	const float *param_weights,
	const float *instream_x,
	float *outstream_y);

/**
 * \brief Basic static non-blocking function for the interface 'weighted'.
 * 
 * Schedule to run on an engine and return immediately.
 * The status of the run can be checked either by ::max_wait or ::max_nowait;
 * note that one of these *must* be called, so that associated memory can be released.
 * 
 * Runs moving average with weighting.
 * \param [in] param_size Interface Parameter "size".
 * \param [in] param_weights Interface Parameter array weights[] should be of size 3.
 * \param [in] instream_x The stream should be of size (param_size * 4) bytes.
 * \param [out] outstream_y The stream should be of size (param_size * 4) bytes.
 * \return A handle on the execution status, or NULL in case of error.
 */
max_run_t *FindWindowMaxAndRadius_weighted_nonblock(
	int32_t param_size,
	const float *param_weights,
	const float *instream_x,
	float *outstream_y);

/**
 * \brief Advanced static interface, structure for the engine interface 'weighted'
 * Runs moving average with weighting.
 */
typedef struct { 
	int32_t param_size; /**<  [in] Interface Parameter "size". */
	const float *param_weights; /**<  [in] Interface Parameter array weights[] should be of size 3. */
	const float *instream_x; /**<  [in] The stream should be of size (param_size * 4) bytes. */
	float *outstream_y; /**<  [out] The stream should be of size (param_size * 4) bytes. */
} FindWindowMaxAndRadius_weighted_actions_t;

/**
 * \brief Advanced static function for the interface 'weighted'.
 * Runs moving average with weighting.
 * \param [in] engine The engine on which the actions will be executed.
 * \param [in,out] interface_actions Actions to be executed.
 */
void FindWindowMaxAndRadius_weighted_run(
	max_engine_t *engine,
	FindWindowMaxAndRadius_weighted_actions_t *interface_actions);

/**
 * \brief Advanced static non-blocking function for the interface 'weighted'.
 *
 * Schedule the actions to run on the engine and return immediately.
 * The status of the run can be checked either by ::max_wait or ::max_nowait;
 * note that one of these *must* be called, so that associated memory can be released.
 *
 * Runs moving average with weighting.
 * \param [in] engine The engine on which the actions will be executed.
 * \param [in] interface_actions Actions to be executed.
 * \return A handle on the execution status of the actions, or NULL in case of error.
 */
max_run_t *FindWindowMaxAndRadius_weighted_run_nonblock(
	max_engine_t *engine,
	FindWindowMaxAndRadius_weighted_actions_t *interface_actions);

/**
 * \brief Group run advanced static function for the interface 'weighted'.
 * Runs moving average with weighting.
 * \param [in] group Group to use.
 * \param [in,out] interface_actions Actions to run.
 *
 * Run the actions on the first device available in the group.
 */
void FindWindowMaxAndRadius_weighted_run_group(max_group_t *group, FindWindowMaxAndRadius_weighted_actions_t *interface_actions);

/**
 * \brief Group run advanced static non-blocking function for the interface 'weighted'.
 * Runs moving average with weighting.
 *
 * Schedule the actions to run on the first device available in the group and return immediately.
 * The status of the run must be checked with ::max_wait. 
 * Note that use of ::max_nowait is prohibited with non-blocking running on groups:
 * see the ::max_run_group_nonblock documentation for more explanation.
 *
 * \param [in] group Group to use.
 * \param [in] interface_actions Actions to run.
 * \return A handle on the execution status of the actions, or NULL in case of error.
 */
max_run_t *FindWindowMaxAndRadius_weighted_run_group_nonblock(max_group_t *group, FindWindowMaxAndRadius_weighted_actions_t *interface_actions);

/**
 * \brief Array run advanced static function for the interface 'weighted'.
 * Runs moving average with weighting.
 * \param [in] engarray The array of devices to use.
 * \param [in,out] interface_actions The array of actions to run.
 *
 * Run the array of actions on the array of engines.  The length of interface_actions
 * must match the size of engarray.
 */
void FindWindowMaxAndRadius_weighted_run_array(max_engarray_t *engarray, FindWindowMaxAndRadius_weighted_actions_t *interface_actions[]);

/**
 * \brief Array run advanced static non-blocking function for the interface 'weighted'.
 * Runs moving average with weighting.
 *
 * Schedule to run the array of actions on the array of engines, and return immediately.
 * The length of interface_actions must match the size of engarray.
 * The status of the run can be checked either by ::max_wait or ::max_nowait;
 * note that one of these *must* be called, so that associated memory can be released.
 *
 * \param [in] engarray The array of devices to use.
 * \param [in] interface_actions The array of actions to run.
 * \return A handle on the execution status of the actions, or NULL in case of error.
 */
max_run_t *FindWindowMaxAndRadius_weighted_run_array_nonblock(max_engarray_t *engarray, FindWindowMaxAndRadius_weighted_actions_t *interface_actions[]);

/**
 * \brief Converts a static-interface action struct into a dynamic-interface max_actions_t struct.
 *
 * Note that this is an internal utility function used by other functions in the static interface.
 *
 * \param [in] maxfile The maxfile to use.
 * \param [in] interface_actions The interface-specific actions to run.
 * \return The dynamic-interface actions to run, or NULL in case of error.
 */
max_actions_t* FindWindowMaxAndRadius_weighted_convert(max_file_t *maxfile, FindWindowMaxAndRadius_weighted_actions_t *interface_actions);



/*----------------------------------------------------------------------------*/
/*---------------------------- Interface default -----------------------------*/
/*----------------------------------------------------------------------------*/




/**
 * \brief Basic static function for the interface 'default'.
 * Runs moving average with no weighting.
 * \param [in] param_size Interface Parameter "size".
 * \param [in] instream_x The stream should be of size (param_size * 4) bytes.
 * \param [out] outstream_y The stream should be of size (param_size * 4) bytes.
 */
void FindWindowMaxAndRadius(
	int32_t param_size,
	const float *instream_x,
	float *outstream_y);

/**
 * \brief Basic static non-blocking function for the interface 'default'.
 * 
 * Schedule to run on an engine and return immediately.
 * The status of the run can be checked either by ::max_wait or ::max_nowait;
 * note that one of these *must* be called, so that associated memory can be released.
 * 
 * Runs moving average with no weighting.
 * \param [in] param_size Interface Parameter "size".
 * \param [in] instream_x The stream should be of size (param_size * 4) bytes.
 * \param [out] outstream_y The stream should be of size (param_size * 4) bytes.
 * \return A handle on the execution status, or NULL in case of error.
 */
max_run_t *FindWindowMaxAndRadius_nonblock(
	int32_t param_size,
	const float *instream_x,
	float *outstream_y);

/**
 * \brief Advanced static interface, structure for the engine interface 'default'
 * Runs moving average with no weighting.
 */
typedef struct { 
	int32_t param_size; /**<  [in] Interface Parameter "size". */
	const float *instream_x; /**<  [in] The stream should be of size (param_size * 4) bytes. */
	float *outstream_y; /**<  [out] The stream should be of size (param_size * 4) bytes. */
} FindWindowMaxAndRadius_actions_t;

/**
 * \brief Advanced static function for the interface 'default'.
 * Runs moving average with no weighting.
 * \param [in] engine The engine on which the actions will be executed.
 * \param [in,out] interface_actions Actions to be executed.
 */
void FindWindowMaxAndRadius_run(
	max_engine_t *engine,
	FindWindowMaxAndRadius_actions_t *interface_actions);

/**
 * \brief Advanced static non-blocking function for the interface 'default'.
 *
 * Schedule the actions to run on the engine and return immediately.
 * The status of the run can be checked either by ::max_wait or ::max_nowait;
 * note that one of these *must* be called, so that associated memory can be released.
 *
 * Runs moving average with no weighting.
 * \param [in] engine The engine on which the actions will be executed.
 * \param [in] interface_actions Actions to be executed.
 * \return A handle on the execution status of the actions, or NULL in case of error.
 */
max_run_t *FindWindowMaxAndRadius_run_nonblock(
	max_engine_t *engine,
	FindWindowMaxAndRadius_actions_t *interface_actions);

/**
 * \brief Group run advanced static function for the interface 'default'.
 * Runs moving average with no weighting.
 * \param [in] group Group to use.
 * \param [in,out] interface_actions Actions to run.
 *
 * Run the actions on the first device available in the group.
 */
void FindWindowMaxAndRadius_run_group(max_group_t *group, FindWindowMaxAndRadius_actions_t *interface_actions);

/**
 * \brief Group run advanced static non-blocking function for the interface 'default'.
 * Runs moving average with no weighting.
 *
 * Schedule the actions to run on the first device available in the group and return immediately.
 * The status of the run must be checked with ::max_wait. 
 * Note that use of ::max_nowait is prohibited with non-blocking running on groups:
 * see the ::max_run_group_nonblock documentation for more explanation.
 *
 * \param [in] group Group to use.
 * \param [in] interface_actions Actions to run.
 * \return A handle on the execution status of the actions, or NULL in case of error.
 */
max_run_t *FindWindowMaxAndRadius_run_group_nonblock(max_group_t *group, FindWindowMaxAndRadius_actions_t *interface_actions);

/**
 * \brief Array run advanced static function for the interface 'default'.
 * Runs moving average with no weighting.
 * \param [in] engarray The array of devices to use.
 * \param [in,out] interface_actions The array of actions to run.
 *
 * Run the array of actions on the array of engines.  The length of interface_actions
 * must match the size of engarray.
 */
void FindWindowMaxAndRadius_run_array(max_engarray_t *engarray, FindWindowMaxAndRadius_actions_t *interface_actions[]);

/**
 * \brief Array run advanced static non-blocking function for the interface 'default'.
 * Runs moving average with no weighting.
 *
 * Schedule to run the array of actions on the array of engines, and return immediately.
 * The length of interface_actions must match the size of engarray.
 * The status of the run can be checked either by ::max_wait or ::max_nowait;
 * note that one of these *must* be called, so that associated memory can be released.
 *
 * \param [in] engarray The array of devices to use.
 * \param [in] interface_actions The array of actions to run.
 * \return A handle on the execution status of the actions, or NULL in case of error.
 */
max_run_t *FindWindowMaxAndRadius_run_array_nonblock(max_engarray_t *engarray, FindWindowMaxAndRadius_actions_t *interface_actions[]);

/**
 * \brief Converts a static-interface action struct into a dynamic-interface max_actions_t struct.
 *
 * Note that this is an internal utility function used by other functions in the static interface.
 *
 * \param [in] maxfile The maxfile to use.
 * \param [in] interface_actions The interface-specific actions to run.
 * \return The dynamic-interface actions to run, or NULL in case of error.
 */
max_actions_t* FindWindowMaxAndRadius_convert(max_file_t *maxfile, FindWindowMaxAndRadius_actions_t *interface_actions);

/**
 * \brief Initialise a maxfile.
 */
max_file_t* FindWindowMaxAndRadius_init(void);

/* Error handling functions */
int FindWindowMaxAndRadius_has_errors(void);
const char* FindWindowMaxAndRadius_get_errors(void);
void FindWindowMaxAndRadius_clear_errors(void);
/* Free statically allocated maxfile data */
void FindWindowMaxAndRadius_free(void);
/* returns: -1 = error running command; 0 = no error reported */
int FindWindowMaxAndRadius_simulator_start(void);
/* returns: -1 = error running command; 0 = no error reported */
int FindWindowMaxAndRadius_simulator_stop(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* SLIC_DECLARATIONS_FindWindowMaxAndRadius_H */

