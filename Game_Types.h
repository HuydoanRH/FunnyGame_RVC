/*============================================================================*/
/* Project      = 39-G Training Course                                        */
/* File name    = Game_Types.h                                            */
/* Author       = Huy Doan                                                    */
/* ID           = 3482                                                        */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* Copyright(c) 2024 Renesas Electronics Corporation. All rights reserved.    */
/*============================================================================*/
/* Purpose:                                                                   */
/* Provision for platform and compiler dependent types                        */
/*                                                                            */
/*============================================================================*/
/*                                                                            */
/* Unless otherwise agreed upon in writing between your company and           */
/* Renesas Electronics Corporation the following shall apply!                 */
/*                                                                            */
/* Warranty Disclaimer                                                        */
/*                                                                            */
/* There is no warranty of any kind whatsoever granted by Renesas. Any        */
/* warranty is expressly disclaimed and excluded by Renesas, either expressed */
/* or implied, including but not limited to those for non-infringement of     */
/* intellectual property, merchantability and/or fitness for the particular   */
/* purpose.                                                                   */
/*                                                                            */
/* Renesas shall not have any obligation to maintain, service or provide bug  */
/* fixes for the supplied Product(s) and/or the Application.                  */
/*                                                                            */
/* Each User is solely responsible for determining the appropriateness of     */
/* using the Product(s) and assumes all risks associated with its exercise    */
/* of rights under this Agreement, including, but not limited to the risks    */
/* and costs of program errors, compliance with applicable laws, damage to    */
/* or loss of data, programs or equipment, and unavailability or              */
/* interruption of operations.                                                */
/*                                                                            */
/* Limitation of Liability                                                    */
/*                                                                            */
/* In no event shall Renesas be liable to the User for any incidental,        */
/* consequential, indirect, or punitive damage (including but not limited     */
/* to lost profits) regardless of whether such liability is based on breach   */
/* of contract, tort, strict liability, breach of warranties, failure of      */
/* essential purpose or otherwise and even if advised of the possibility of   */
/* such damages. Renesas shall not be liable for any services or products     */
/* provided by third party vendors, developers or consultants identified or   */
/* referred to the User by Renesas in connection with the Product(s) and/or   */
/* the Application.                                                           */
/*                                                                            */

/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/
/*
 * 1.0.0:  27/03/2024  : Initial Version
 */
/******************************************************************************/
#ifndef GAME_TYPES_H
#define GAME_TYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include <stdbool.h>
#include <stdio.h>
#include "conio.h"
#include <string.h>
#include <stdlib.h>

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/*
 * Game integer data types
 */
typedef unsigned char       uint8;          /*           0 .. 255            */
#define UINT8_MIN           0
#ifdef UINT8_MAX
  #undef UINT8_MAX
#endif
#define UINT8_MAX           255

typedef signed short        sint16;         /*      -32768 .. +32767         */
#define SINT16_MIN          -32768
#define SINT16_MAX          32767

typedef unsigned short      uint16;         /*           0 .. 65535          */
#define UINT16_MIN          0
#ifdef UINT16_MAX
  #undef UINT16_MAX
#endif
#define UINT16_MAX          65535

typedef unsigned long       uint32;         /*           0 .. 4294967295     */
#define UINT32_MIN          0
#ifdef UINT32_MAX
  #undef UINT32_MAX
#endif
#define UINT32_MAX          4294967295

typedef _Bool               boolean;
#define true        1
#ifndef TRUE                                /* conditional check */
  #define TRUE      true
#endif

#define false       0
#ifndef FALSE                               /* conditional check */
  #define FALSE     false
#endif

#endif /* GAME_TYPES_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
