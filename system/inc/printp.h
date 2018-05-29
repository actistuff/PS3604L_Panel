﻿/*!****************************************************************************
 * @file		printp.h
 * @author		d_el
 * @version		V1.0
 * @date		06.12.2017
 * @brief		System control task
 * @copyright	Copyright (C) 2017 Storozhenko Roman
 *				All rights reserved
 *				This software may be modified and distributed under the terms
 *				of the BSD license.	 See the LICENSE file for details
 */
#ifndef printp_H
#define printp_H

/*!****************************************************************************
 * Include
 */

/*!****************************************************************************
 * Define
 */

/*!****************************************************************************
 * Enumeration
 */

/*!****************************************************************************
 * Typedef
 */
typedef enum{
	stdOut_semihost,
	stdOut_rtt,
	stdOut_uart,
}stdOutInterface_type;

/*!****************************************************************************
 * Exported variables
 */

/*!****************************************************************************
 * Macro functions
 */

/*!****************************************************************************
 * Function declaration
 */
void print_init(stdOutInterface_type stdoi);
void l_print(const char *fmt, ...);

#endif //printp_H
/*************** LGPL ************** END OF FILE *********** D_EL ************/
