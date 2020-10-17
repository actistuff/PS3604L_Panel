﻿/*!****************************************************************************
 * @file		uniqueDeviceId.h
 * @author		d_el - Storozhenko Roman
 * @version		V1.0
 * @date		26.06.2017
 * @copyright	The MIT License (MIT). Copyright (c) 2017 Storozhenko Roman
 */
#ifndef uniqueDeviceId_H
#define uniqueDeviceId_H

/*!****************************************************************************
 * Include
 */
#include "stdint.h"

/*!****************************************************************************
 * Define
 */
#define UNIQDEVID_BASE	0x1FFF7A10

/*!****************************************************************************
 * Enumeration
 */

/*!****************************************************************************
 * Typedef
 */

/*!****************************************************************************
 * Exported variables
 */
extern const uint32_t *uniqDevId;

/*!****************************************************************************
 * Macro functions
 */
#define makeID(x)	(((((uint64_t)x) * ((x) - 68)) & 0xFFFFFFFF) ^ 0xAAAAAAAA)

/*!****************************************************************************
 * Function declaration
 */
uint32_t getDid(void);
uint8_t checkUniqDevId(void);

#endif //uniqueDeviceId_H
/******************************** END OF FILE ********************************/
