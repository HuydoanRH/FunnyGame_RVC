/*============================================================================*/
/* Project      = 39-G Training Course                                        */
/* File name    = FunnyGame.h                                            */
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
#ifndef FUNNYGAME_H
#define FUNNYGAME_H

/* Number question and answer*/
#define NUM_QUESTION        (10)
/* Max length of question, answer, hint*/
#define MAX_LENGTH          (500)
/*length of input when player choose mode1*/
#define NUM_LETTER          (1)
/*Default point of player*/
#define DEFAULT_POINTS      (100)
/*Player continue game*/
#define CONTINUE_GAME       TRUE
/*Player quit game*/
#define QUIT_GAME           FALSE
/*Debug Mode ON*/
#define DEBUG_ON            TRUE
/*Debug Mode OFF*/
#define DEBUG_OFF           FALSE
/*ASCII Upper Letter Min Code*/
#define ASCII_UPPER_MIN     (65)
/*ASCII Upper Letter Max Code*/
#define ASCII_UPPER_MAX     (90)
/*ASCII Space Code*/
#define ASCII_SPACE         (32)
/*Player point min*/
#define POINTS_MIN          (0)

/* Terminal of win10 not support display color by ANSI, only turn on it on terminal of VScode */
// char ANSI_PREFIX[] = "[34mFUNNY GAME";
// char ANSI_ERROR[] = "[0m | [1;91mERROR[0m | [1;91m";
// char ANSI_WARNING[] = "[0m | [1;90mWARNING[0m | [33m";
// char ANSI_INFO[] = "[0m | [1;90mINFO[0m | [1;36m";
// char ANSI_POSFIX[] = "[0m";

/* Make log color section */
char ANSI_PREFIX[] = "";
char ANSI_ERROR[] = "**ERROR**";
char ANSI_WARNING[] = "**WARNING**";
char ANSI_INFO[] = "**INFO**";
char ANSI_POSFIX[] = "";
/* End make log color section */

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
#include "Game_Types.h"
/***********************************************************************************************************************
**                                                  Global Symbols                                                    **
***********************************************************************************************************************/
/* Enumeration for player answer */
typedef enum GameData_PlayerAnswerState
{
  MODE1_OK = 0x00,
  MODE1_NG = 0x01,
  MODE2_OK = 0x02,
  MODE2_NG = 0x03
} PlayerAnswerState;

typedef struct GameData_QuestionAndAnswer
{
  //Attribute
  /*Question ID */
  uint8 ucID;
  /*Question content */
  uint8 ucQuestion[MAX_LENGTH];
  /*Answer content */
  uint8 ucAnswer[MAX_LENGTH];
  /*Hint content */
  uint8 ucAnswerHint[MAX_LENGTH];
  /*Number Words of answer*/
  uint8 ucNumWordOfAnswer;
  /*Answer length include space*/
  uint16 usLengthOfAnswer;
  /*Answer length show for hint*/
  uint16 usLengthOfAnswerForHint;
} Question_Answer;

typedef struct GameData_Users
{
  //Attribute
  /*Answer of question i of player*/
  uint8 ucID;
  /*Num letter correct*/
  uint8 ucNumLetterCorrected;
  /*Points of player*/
  sint16 ssUserPoints;
  /*Mode choosed by player*/
  uint8 ucModeID;
  /*Letter input by player */
  uint8 ucAnswerLetter;
  /*Answer input by player */
  uint8 ucPlayerAnswer[MAX_LENGTH];
  /*Answer of answer length*/
  uint16 usLengthOfPlayerAnswer;
} Users;

#endif /* FUNNYGAME_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
