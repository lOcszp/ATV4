/*
 * app.h
 *
 *  Created on: Feb 10, 2022
 *      Author: lukaz
 */

#ifndef APP_H_
#define APP_H_
#include <stdbool.h>

void app_init(void);
void app_loop(void);
void app_tick_1ms(void);
void app_switch_interrupt(bool switch_port);

#endif /* APP_H_ */
