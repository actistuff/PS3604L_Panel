﻿/*!****************************************************************************
 * @file		OSinit.h
 * @author		d_el - Storozhenko Roman
 * @version		V1.0
 * @copyright	The MIT License (MIT). Copyright (c) 2017 Storozhenko Roman
 * @brief		Initialization operational system
 */

/*!****************************************************************************
 * Include
 */

/*!**** NAME ****************** priority [1 - configMAX_PRIORITIES] **********/
#define SYSTEM_TSK_PRIO			7
#define UART_TSK_PRIO			6
//#define NETIF_TSK_PRIO			5
//#define TCPIP_TSK_PRIO			4
#define HTTP_TSK_PRIO			3
#define OSMONITOR_TSK_PRIO		1
#define STARTUP_TSK_PRIO		1
#define BASE_TSK_PRIO			1
#define CHARG_TSK_PRIO			1
#define SETT_TSK_PRIO			1

/*!**** NAME ****************** size [4byte Word] ****************************/
#define SYSTEM_TSK_SZ_STACK		512
#define UART_TSK_SZ_STACK		512
//#define NETIF_SZ_STACK			512
//#define TCPIP_SZ_STACK			512
#define HTTP_TSK_SZ_STACK		512
#define STARTUP_TSK_SZ_STACK	512
#define BASE_TSK_SZ_STACK		512
#define CHARG_TSK_SZ_STACK		512
#define OSMONITOR_TSK_SZ_STACK	512
#define SETT_TSK_SZ_STACK		512

/*!****************************************************************************
 * Function declaration
 */
void OSinit(void);

/******************************** END OF FILE ********************************/
