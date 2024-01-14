/*
 * motorControltask.hpp
 *
 *  Created on: Oct 23, 2023
 *      Author: burge
 */

#ifndef SRC_CONTROL_TASK_HPP_
#define SRC_CONTROL_TASK_HPP_

#define CONTROL_TASK_PERIOD 10

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void controlTask(void *argument);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* SRC_MOTORCONTROL_TASK_HPP_ */
