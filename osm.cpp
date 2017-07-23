/**
 * @file osm.cpp
 * @author Itai Tagar <itagar>
 *
 * @brief A Library which provides functions to measure the time it takes to
 *        perform four different operations:
 *          1. A simple instruction.
 *          2. An empty function call.
 *          3. A trap.
 *          4. Accessing the disk.
 *        The library also provides a function, which returns a struct
 *        containing all the data we are interested in.
 */


/*-----=  Includes  =-----*/


#include "osm.h"
#include "emptyFunction.h"
#include <sys/time.h>
#include <unistd.h>
#include <memory>
#include <fcntl.h>
#include <malloc.h>
#include <stdlib.h>


/*-----=  Definitions  =-----*/


/**
* @def SUCCESS_STATE 0
* @brief A Macro that sets return state in case of success.
*/
# define SUCCESS_STATE 0

/**
* @def FAILURE_STATE -1
* @brief A Macro that sets return state in case of failure.
*/
# define FAILURE_STATE -1

/**
* @def FILE_OPEN_FAILURE -1
* @brief A Macro that sets the failure value for the open() function.
*/
# define FILE_OPEN_FAILURE -1

/**
* @def SUCCESS_ERRNO 0
* @brief A Macro for the Success errno.
*/
# define SUCCESS_ERRNO 0

/**
* @def INVALID_ITERATION_NUMBER 0
* @brief A Macro that sets the invalid number of iterations.
*/
# define INVALID_ITERATION_NUMBER 0

/**
* @def DEFAULT_ITERATION_NUMBER 1000
* @brief A Macro that sets the default number of iterations.
*/
# define DEFAULT_ITERATION_NUMBER 1000

/**
* @def MICRO_TO_NANO_FACTOR 1000
* @brief A Macro that sets the factor to convert micro-seconds to nano-seconds.
*/
# define MICRO_TO_NANO_FACTOR 1000

/**
* @def SECONDS_TO_NANO_FACTOR 1000000000
* @brief A Macro that sets the factor to convert seconds to nano-seconds.
*/
# define SECONDS_TO_NANO_FACTOR 1000000000

/**
* @def LOOP_UNROLLING_FACTOR 10
* @brief A Macro that sets the iterations facor while using loop unrolling.
*/
# define LOOP_UNROLLING_FACTOR 10

/**
* @def MACHINE_NAME_LENGTH 256
* @brief A Macro that sets the length of the machine name.
*/
# define MACHINE_NAME_LENGTH 256

/**
* @def TEMP_FILE_PATH "/tmp/myFile.txt"
* @brief A Macro that sets the path used for the file in disk measurement.
*/
# define TMP_FILE_PATH "/tmp/myFile.txt"

/**
* @def EMPTY_MACHINE_NAME ""
* @brief A Macro that sets the empty machine name.
*/
# define EMPTY_MACHINE_NAME ""

/**
* @def START_ITERATION_INDEX 0
* @brief A Macro that sets the start index for the iterations.
*/
# define START_ITERATION_INDEX 0

/**
* @def BLOCK_SIZE 4096
* @brief A Macro that sets the block size in the file system.
*/
# define BLOCK_SIZE 4096


/*-----=  Global Variables  =-----*/


/**
 * @brief The variable which holds the machine name.
 */
char *gMachineName = nullptr;


/*-----=  Measurement Functions  =-----*/


/**
 * @brief Initialization function that the user must call before running
 *        any other library function.
 * @return Returns 0 upon success and -1 on failure
 */
int osm_init()
{
    // Allocate memory for the machine name.
    try
    {
        gMachineName = new char[MACHINE_NAME_LENGTH];
    }
    catch (std::bad_alloc &exception)
    {
        // If memory allocation failed.
        gMachineName = nullptr;
        return FAILURE_STATE;
    }

    // Set machine name.
    if (gethostname(gMachineName, MACHINE_NAME_LENGTH))
    {
        // If setting the machine name using 'gethostname()' failed.
        gMachineName = nullptr;
        return FAILURE_STATE;
    }

    return SUCCESS_STATE;
}

/**
 * @brief finalizer function that the user must call after running
 *        any other library function.
 * @return Returns 0 upon success and -1 on failure
 */
int osm_finalizer()
{
    delete[] gMachineName;
    return SUCCESS_STATE;
}

/**
 * @brief Calculates the time elapsed from the given start timestamp to
 *        the end timestamp in nano-seconds.
 * @param start The start timestamp.
 * @param end The end timestamp.
 * @param operations The number of operations performed in this time period.
 * @return The time elapsed in nano-seconds from start to end.
 */
double calculateTime(const timeval &start, const timeval &end,
                     const unsigned int &operations)
{
    double seconds = (end.tv_sec - start.tv_sec) * SECONDS_TO_NANO_FACTOR;
    double microSeconds = (end.tv_usec - start.tv_usec) * MICRO_TO_NANO_FACTOR;
    return (seconds + microSeconds) / ((double) operations);
}

/**
 * @brief Validates the iteartions argument given to some measurement function.
 *        If the number invalid we set it to be the default iterations number,
 *        otherwise we keep it as is.
 * @param iterations The given iterations number.
 */
void validateIterations(unsigned int &iterations)
{
    if (iterations == INVALID_ITERATION_NUMBER)
    {
        iterations = DEFAULT_ITERATION_NUMBER;
    }
}

/**
 * @brief A dummy function used to make the given variables in use.
 */
void dummyCheck(int &arg1, int &arg2, int &arg3, int &arg4, int &arg5,
                int &arg6, int &arg7, int &arg8, int &arg9, int &arg10)
{

}

/**
 * @brief Time measurement function for a simple arithmetic operation.
 * @param iterations The number of iterations to perform in the measurement.
 * @return Returns time in nano-seconds upon success, and -1 upon failure.
 */
double osm_operation_time(unsigned int iterations)
{
    // Handle the case of invalid iterations argument.
    validateIterations(iterations);

    // Set the data required for the measurement process.
    timeval start, end;
    int tempNumber1, tempNumber2, tempNumber3, tempNumber4,
            tempNumber5, tempNumber6, tempNumber7, tempNumber8,
            tempNumber9, tempNumber10 = 0;

    // Set the start timestamp.
    if (gettimeofday(&start, nullptr))
    {
        // In case of failure of 'gettimeofday()', return failure.
        return FAILURE_STATE;
    }
    // Run the measurement iterations.
    unsigned int operations = START_ITERATION_INDEX;
    for ( ; operations < iterations; operations += LOOP_UNROLLING_FACTOR)
    {
        tempNumber1 = 5 + 8;
        tempNumber2 = 4 & 7;
        tempNumber3 = 6 + 0;
        tempNumber4 = 7 & 3;
        tempNumber5 = 4 + 2;
        tempNumber6 = 5 + 8;
        tempNumber7 = 4 & 7;
        tempNumber8 = 6 + 0;
        tempNumber9 = 7 & 3;
        tempNumber10 = 4 + 2;
    }
    // Set the end timestamp.
    if (gettimeofday(&end, nullptr))
    {
        // In case of failure of 'gettimeofday()', return failure.
        return FAILURE_STATE;
    }

    // Used for making the assignments not redundant.
    dummyCheck(tempNumber1, tempNumber2, tempNumber3, tempNumber4,
               tempNumber5, tempNumber6, tempNumber7, tempNumber8,
               tempNumber9, tempNumber10);

    // Calculate the measurement with the actual number of operations performed.
    return calculateTime(start, end, operations);
}

/**
 * @brief Time measurement function for an empty function call.
 * @param iterations The number of iterations to perform in the measurement.
 * @return Returns time in nano-seconds upon success, and -1 upon failure.
 */
double osm_function_time(unsigned int iterations)
{
    // Handle the case of invalid iterations argument.
    validateIterations(iterations);

    // Set the data required for the measurement process.
    timeval start, end;

    // Set the start timestamp.
    if (gettimeofday(&start, nullptr))
    {
        // In case of failure of 'gettimeofday()', return failure.
        return FAILURE_STATE;
    }
    // Run the measurement iterations.
    unsigned int operations = START_ITERATION_INDEX;
    for ( ; operations < iterations; operations += LOOP_UNROLLING_FACTOR)
    {
        emptyFunction();
        emptyFunction();
        emptyFunction();
        emptyFunction();
        emptyFunction();
        emptyFunction();
        emptyFunction();
        emptyFunction();
        emptyFunction();
        emptyFunction();
    }
    // Set the end timestamp.
    if (gettimeofday(&end, nullptr))
    {
        // In case of failure of 'gettimeofday()', return failure.
        return FAILURE_STATE;
    }

    // Calculate the measurement with the actual number of operations performed.
    return calculateTime(start, end, operations);
}

/**
 * @brief Time measurement function for an empty trap into the operating system.
 * @param iterations The number of iterations to perform in the measurement.
 * @return Returns time in nano-seconds upon success, and -1 upon failure.
 */
double osm_syscall_time(unsigned int iterations)
{
    // Handle the case of invalid iterations argument.
    validateIterations(iterations);

    // Set the data required for the measurement process.
    timeval start, end;

    // Set the start timestamp.
    if (gettimeofday(&start, nullptr))
    {
        // In case of failure of 'gettimeofday()', return failure.
        return FAILURE_STATE;
    }
    // Run the measurement iterations.
    unsigned int operations = START_ITERATION_INDEX;
    for ( ; operations < iterations; operations += LOOP_UNROLLING_FACTOR)
    {
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;
    }
    // Set the end timestamp.
    if (gettimeofday(&end, nullptr))
    {
        // In case of failure of 'gettimeofday()', return failure.
        return FAILURE_STATE;
    }

    // Calculate the measurement with the actual number of operations performed.
    return calculateTime(start, end, operations);
}

/**
 * @brief Used to close open streams and utilities used for disk measurements.
 * @param fd File Descriptor to close.
 * @param path Path of file to remove.
 * @param fileBuffer FileBuffer to deAlloc.
 */
void closeGeneral(const int &fd, const char *path, char *fileBuffer)
{
    if (fd != FILE_OPEN_FAILURE)
    {
        close(fd);
    }
    remove(path);
    free(fileBuffer);
}

/**
 * @brief Used to close open streams and utilities used for disk measurements
 *        upon failure.
 * @param fd File Descriptor to close.
 * @param path Path of file to remove.
 * @param fileBuffer FileBuffer to deAlloc.
 * @return Failure state.
 */
int closeUponFailure(const int &fd, const char *path, char *fileBuffer)
{
    closeGeneral(fd, path, fileBuffer);
    return FAILURE_STATE;
}

/**
 * @brief Used to close open streams and utilities used for disk measurements
 *        upon success.
 * @param fd File Descriptor to close.
 * @param path Path of file to remove.
 * @param fileBuffer FileBuffer to deAlloc.
 * @return Success state.
 */
int closeUponSuccess(const int &fd, const char *path, char *fileBuffer)
{
    closeGeneral(fd, path, fileBuffer);
    return SUCCESS_STATE;
}

/**
 * @brief Fills the buffer with data in the size of Block Size in order to
 *        use it during the write operations.
 * @param fileBuffer The buffer to fill.
 */
void fillBuffer(char *fileBuffer)
{
    for (int i = START_ITERATION_INDEX; i < BLOCK_SIZE; ++i)
    {
        fileBuffer[i] = '1';
    }
}

/**
 * @brief Time measurement function for accessing the disk.
 * @param iterations The number of iterations to perform in the measurement.
 * @return Returns time in nano-seconds upon success, and -1 upon failure.
 */
double osm_disk_time(unsigned int iterations)
{
    // Handle the case of invalid iterations argument.
    validateIterations(iterations);

    // Create a buffer to perform operations on the file.
    char *fileBuffer = nullptr;
    fileBuffer = (char *) aligned_alloc(BLOCK_SIZE, BLOCK_SIZE);
    if (fileBuffer == nullptr)
    {
        return FAILURE_STATE;
    }
    fillBuffer(fileBuffer);

    // Create some arbitrary file in '/tmp' folder.
    int fd = open(TMP_FILE_PATH, O_RDWR | O_DIRECT | O_SYNC | O_EXCL | O_CREAT);
    if (fd == FILE_OPEN_FAILURE)
    {
        return closeUponFailure(fd, TMP_FILE_PATH, fileBuffer);
    }

    // Set the data required for the measurement process.
    timeval start, end;

    // Set the start timestamp.
    if (gettimeofday(&start, nullptr))
    {
        // In case of failure of 'gettimeofday()', return failure.
        return closeUponFailure(fd, TMP_FILE_PATH, fileBuffer);
    }

    // Run the measurement iterations.
    unsigned int i = START_ITERATION_INDEX;
    for ( ; i < iterations; ++i)
    {
        write(fd, fileBuffer, BLOCK_SIZE);
    }

    // Set the end timestamp.
    if (gettimeofday(&end, nullptr))
    {
        // In case of failure of 'gettimeofday()', return failure.
        return closeUponFailure(fd, TMP_FILE_PATH, fileBuffer);
    }

    if (errno != SUCCESS_ERRNO)
    {
        // If write operation failed.
        return closeUponFailure(fd, TMP_FILE_PATH, fileBuffer);
    }

    closeUponSuccess(fd, TMP_FILE_PATH, fileBuffer);  // Close streams.

    // Calculate the measurement with the actual number of operations performed.
    return calculateTime(start, end, i);
}

/**
 * @brief Sets the machine name for the given timeMeasurmentStructure.
 * @param tms The given struct to set.
 */
void setMachineName(timeMeasurmentStructure& tms)
{
    if (gMachineName == nullptr)
    {
        tms.machineName = (char *) EMPTY_MACHINE_NAME;
    }
    else
    {
        tms.machineName = gMachineName;
    }
}

/**
 * @brief Gets the proper ratio of the given arguments.
 *        If at least one of the arguments is -1 we return -1.
 *        If the second argument is zero we return -1.
 * @param first The first argument in the ratio.
 * @param second The second argument in the ratio.
 * @return The ratio between first and second, or -1 if one of them is -1
 *         or if we try to divide by zero.
 */
double getRatio(const double &first, const double &second)
{
    if ((first == FAILURE_STATE) || (second == FAILURE_STATE))
    {
        return FAILURE_STATE;
    }

    return (first / second);
}

/**
 * @brief A function that measures all of the 4 different operations.
 * @param operation_iterations The number of iterations to perform in the
 *                             measurement for the simple instruction.
 * @param function_iterations The number of iterations to perform in the
 *                            measurement for the empty function call.
 * @param syscall_iterations The number of iterations to perform in the
 *                           measurement for the trap.
 * @param disk_iterations The number of iterations to perform in the
 *                        measurement for the disk access.
 * @return A struct containing all the data of the operations, in nano-seconds.
 */
timeMeasurmentStructure measureTimes(unsigned int operation_iterations,
                                     unsigned int function_iterations,
                                     unsigned int syscall_iterations,
                                     unsigned int disk_iterations)
{
    timeMeasurmentStructure tms;
    setMachineName(tms);
    tms.instructionTimeNanoSecond = osm_operation_time(operation_iterations);
    tms.functionTimeNanoSecond = osm_function_time(function_iterations);
    tms.trapTimeNanoSecond = osm_syscall_time(syscall_iterations);
    tms.diskTimeNanoSecond = osm_disk_time(disk_iterations);
    tms.functionInstructionRatio = getRatio(tms.functionTimeNanoSecond,
                                            tms.instructionTimeNanoSecond);
    tms.trapInstructionRatio = getRatio(tms.trapTimeNanoSecond,
                                        tms.instructionTimeNanoSecond);
    tms.diskInstructionRatio = getRatio(tms.diskTimeNanoSecond,
                                        tms.instructionTimeNanoSecond);
    return tms;
}
