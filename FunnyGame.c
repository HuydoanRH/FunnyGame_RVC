/*============================================================================*/
/* Project      = 39-G Training Course                                        */
/* File name    = FunnyGame.c                                            */
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

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
#include "FunnyGame.h"
/***********************************************************************************************************************
**                                                Global Data Declaretion                                             **
***********************************************************************************************************************/
Question_Answer stQuestion_Answer_Data[NUM_QUESTION];
Users stUser[NUM_QUESTION];
PlayerAnswerState enPlayerAnswerState;
uint8 QuestionPresent;
boolean blIsTheLoser;

/***********************************************************************************************************************
**                                                Function Declaretions                                               **
***********************************************************************************************************************/
void ShowAnswer();
void ShowAnswerOfDebugMode();
void ShowInforLoser();
uint8 CountWord(uint8* ucAnswer, uint16* usLengthOfAnswerForHint);
void SetDefaultHint(uint8* ucAnswerHint, uint16 usLengthOfAnswer);
void CheckAndShowAnswer();
void CheckAndUpdateHint();
void ShowHint(uint8 ucNumLetterCorrect);
void SetUserInputMode(uint8* ucModeID, uint8 ucLenOfInputMode);
void SetUserAnswerFull(uint8* ucPlayerAnswer, uint8 ucLenOfInputAnswer);
void GetInfoFromUserInputMode();
void GetInfoFromUserInputLetter();
void GetInfoFromUserInputAnswer();
void FirstScreenInformation();
void UpdateUserPoints(PlayerAnswerState enPlayerAnswerState);
void SetUserAction();
void SetDebugMode();

/***********************************************************************************************************************
**                                                Initial Database                                                    **
***********************************************************************************************************************/
void initialise_database()
{
  /* Initial 10 question*/
  uint8 Question_Database[NUM_QUESTION][MAX_LENGTH];
  strcpy(Question_Database[0], "There is a sentence: \"youth is just like a cup of tea\". Do you know what kind of tea here is?");
  strcpy(Question_Database[1], "What is one thing you can never eat for breakfast and lunch?");
  strcpy(Question_Database[2], "What is always coming but never arrives?");
  strcpy(Question_Database[3], "What gets wetter the more it dries? ");
  strcpy(Question_Database[4], "What can be broken but never held?");
  strcpy(Question_Database[5], "What word is spelled incorrectly in every single dictionary?");
  strcpy(Question_Database[6], "What is it that lives if it is fed, and dies if you give it a drink?");
  strcpy(Question_Database[7], "What never asks a question but gets answered all the time?");
  strcpy(Question_Database[8], "What goes up but never ever comes down?");
  strcpy(Question_Database[9], "What will you actually find at the end of every rainbow?");

  /* Initial 10 Answers correcspond 10 questions*/
  uint8 Answer_Database[NUM_QUESTION][MAX_LENGTH];
  strcpy(Answer_Database[0], "GREEN TEA");
  strcpy(Answer_Database[1], "DINNER");
  strcpy(Answer_Database[2], "TOMORROW");
  strcpy(Answer_Database[3], "TOWEL");
  strcpy(Answer_Database[4], "PROMISE");
  strcpy(Answer_Database[5], "INCORRECTLY");
  strcpy(Answer_Database[6], "FIRE");
  strcpy(Answer_Database[7], "CELLPHONE");
  strcpy(Answer_Database[8], "AGE");
  strcpy(Answer_Database[9], "W");

  for (uint8 i = 0; i < NUM_QUESTION; i++)
  {
    /* init stQuestion_Answer_Data */
    stQuestion_Answer_Data[i].ucID = i;
    strcpy(stQuestion_Answer_Data[i].ucQuestion, Question_Database[i]);
    strcpy(stQuestion_Answer_Data[i].ucAnswer, Answer_Database[i]);
    strcpy(stQuestion_Answer_Data[i].ucAnswerHint, Answer_Database[i]);
    stQuestion_Answer_Data[i].usLengthOfAnswer = strlen(stQuestion_Answer_Data[i].ucAnswer);
    stQuestion_Answer_Data[i].usLengthOfAnswerForHint = stQuestion_Answer_Data[i].usLengthOfAnswer;
    /* Set default for hint: ---- -----*/
    SetDefaultHint(stQuestion_Answer_Data[i].ucAnswerHint, stQuestion_Answer_Data[i].usLengthOfAnswer);
    /* Count number word of answer*/
    stQuestion_Answer_Data[i].ucNumWordOfAnswer = CountWord(stQuestion_Answer_Data[i].ucAnswer, &stQuestion_Answer_Data[i].usLengthOfAnswerForHint);
    
    /* init stUsers */
    stUser[i].ucID = i;
    stUser[i].ucNumLetterCorrected = 0;
    stUser[i].ssUserPoints = DEFAULT_POINTS;
  }

  /* Set the first question for player*/
  QuestionPresent = 0;
  blIsTheLoser = FALSE;
}

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
** Function Name             : ShowAnswerOfDebugMode
**
** Description               : 
**
***********************************************************************************************************************/
void ShowAnswerOfDebugMode()
{
  printf("%s%s Answer of question %d is \"%s\"%s\n", ANSI_PREFIX, ANSI_INFO, QuestionPresent + 1, \
                stQuestion_Answer_Data[QuestionPresent].ucAnswer, ANSI_POSFIX);
} /* End of ShowAnswerOfDebugMode */

/***********************************************************************************************************************
** Function Name             : ShowAnswer
**
** Description               : 
**
***********************************************************************************************************************/
void ShowAnswer()
{
    printf("%s%s Correct !!! Answer is \"%s\"%s\n", ANSI_PREFIX, ANSI_INFO, \
                stQuestion_Answer_Data[QuestionPresent].ucAnswer, ANSI_POSFIX);
    printf("%s%s FANTASTIC, WONDERFUL, SIGNIFICANT, MAGNIFICENT, OUTSTANDING, CLASS OF TITANS, WORLD-CLASS !!! YOU ARE THE WINNER WITH %d POINTS.%s\n",\
            ANSI_PREFIX, ANSI_INFO, stUser[QuestionPresent].ssUserPoints, ANSI_POSFIX);
} /* End of ShowAnswer */

/***********************************************************************************************************************
** Function Name             : ShowInforLoser
**
** Description               : 
**
***********************************************************************************************************************/
void ShowInforLoser()
{
    printf("%s%s :( SO SAD, YOUR POINTS IS <= 0 NOW, YOU ARE NOT WIN QUESTION %d %s\n",\
            ANSI_PREFIX, ANSI_INFO, QuestionPresent, ANSI_POSFIX);
    SetUserAction();
} /* End of ShowInforLoser */

/***********************************************************************************************************************
** Function Name             : CountWord
**
** Description               : 
**
***********************************************************************************************************************/
uint8 CountWord(uint8* ucAnswer, uint16* usLengthOfAnswerForHint)
{
  uint8 numberOfWorld = 1;
  for(uint8 i = 0; i < *usLengthOfAnswerForHint; i++)
  {
    if(ucAnswer[i] == ' ')
    {
      numberOfWorld++;
      *usLengthOfAnswerForHint = *usLengthOfAnswerForHint - 1;
    }
    else
    {
      //do nothing
    }
  }
  return numberOfWorld;
} /* End of CountWord *

/***********************************************************************************************************************
** Function Name             : SetDefaultHint
**
** Description               : 
**
***********************************************************************************************************************/
void SetDefaultHint(uint8* ucAnswerHint, uint16 usLengthOfAnswer)
{
  for (uint8 i = 0; i < usLengthOfAnswer; i++)
  {
    if (ucAnswerHint[i] == ' ')
    {
      //do nothing
    }
    else
    {
      ucAnswerHint[i] = '_';
    }
  }
} /* End of SetDefaultHint */

/***********************************************************************************************************************
** Function Name             : CheckAndShowAnswer
**
** Description               : 
**
***********************************************************************************************************************/
void CheckAndShowAnswer()
{
  /* Compare answer. Same return 0, else return !=0*/
  uint8 ucCheckAnswerResult = strcmp(stQuestion_Answer_Data[QuestionPresent].ucAnswer, stUser[QuestionPresent].ucPlayerAnswer);

  if (ucCheckAnswerResult == 0)
  {
    ShowAnswer();
    /* Check what player want to continue play or cook */
    SetUserAction();  
  }
  else
  {
    UpdateUserPoints(MODE2_NG);
    printf("%s%s Not correct! Answer is \"%s\"%s\n", ANSI_PREFIX, ANSI_INFO,\
               stQuestion_Answer_Data[QuestionPresent].ucAnswerHint, ANSI_POSFIX);
    printf("%s%s Your point now = %d%s\n", ANSI_PREFIX, ANSI_INFO,\
          stUser[QuestionPresent].ssUserPoints, ANSI_POSFIX);
    /*check point if < 0*/
    if (!blIsTheLoser)
    {
      GetInfoFromUserInputMode();
    }
    else
    {
      ShowInforLoser();
    }
  }
  
} /* End of CheckAndShowAnswer */

/***********************************************************************************************************************
** Function Name             : UpdateHint
**
** Description               : 
**
***********************************************************************************************************************/
void CheckAndUpdateHint()
{
  uint8 ucNumLetterCorrect = 0;
  boolean blWasInputLetter = FALSE;
  for (uint8 i = 0; i < stQuestion_Answer_Data[QuestionPresent].usLengthOfAnswer; i++)
  {
    if((stUser[QuestionPresent].ucAnswerLetter == stQuestion_Answer_Data[QuestionPresent].ucAnswer[i]) && stUser[QuestionPresent].ucAnswerLetter != ' ')
    {
      if (stQuestion_Answer_Data[QuestionPresent].ucAnswerHint[i] == '_')
      {
        stQuestion_Answer_Data[QuestionPresent].ucAnswerHint[i] = stUser[QuestionPresent].ucAnswerLetter;
        ucNumLetterCorrect++;
      }
      else
      {
        blWasInputLetter = TRUE;
        break;
      }
    }
    else
    {
      //do nothing
    }
  }
  if (blWasInputLetter)
  {
    // show the letter was input, don't input again.
    printf("%s%s THIS LETTER WAS INPUT AND EXIST. TYPE AGAIN!!!!%s\n", ANSI_PREFIX, ANSI_INFO, ANSI_POSFIX);
    GetInfoFromUserInputLetter();
  }
  else
  {
    ShowHint(ucNumLetterCorrect);
  }
} /* End of UpdateHint */

/***********************************************************************************************************************
** Function Name             : ShowHint
**
** Description               : 
**
***********************************************************************************************************************/
void ShowHint(uint8 ucNumLetterCorrect)
{
  stUser[QuestionPresent].ucNumLetterCorrected =  stUser[QuestionPresent].ucNumLetterCorrected + ucNumLetterCorrect;
  if (ucNumLetterCorrect == 0)
  {
    UpdateUserPoints(MODE1_NG);
    printf("%s%s Not correct! There is %d \"%c\"%s\n", ANSI_PREFIX, ANSI_INFO, ucNumLetterCorrect,\
               stUser[QuestionPresent].ucAnswerLetter, ANSI_POSFIX);
    printf("%s%s Answer is \"%s\"%s\n", ANSI_PREFIX, ANSI_INFO,\
               stQuestion_Answer_Data[QuestionPresent].ucAnswerHint, ANSI_POSFIX);
    printf("%s%s Your point now = %d%s\n", ANSI_PREFIX, ANSI_INFO,\
          stUser[QuestionPresent].ssUserPoints, ANSI_POSFIX);
    /*check point if < 0*/
    if (!blIsTheLoser)
    {
      GetInfoFromUserInputMode();
    }
    else
    {
      ShowInforLoser();
    }
  }
  else
  {
    UpdateUserPoints(MODE1_OK);
    if (stUser[QuestionPresent].ucNumLetterCorrected == stQuestion_Answer_Data[QuestionPresent].usLengthOfAnswerForHint)
    {
      /*check point if < 0*/
      if (!blIsTheLoser)
      {
        ShowAnswer();
        /* Check what player want to continue play or cook */
        SetUserAction();
      }
      else
      {
        ShowInforLoser();
      }
    }
    else
    {
      printf("%s%s Correct! There is %d \"%c\"%s\n", ANSI_PREFIX, ANSI_INFO, ucNumLetterCorrect,\
                stUser[QuestionPresent].ucAnswerLetter, ANSI_POSFIX);
      printf("%s%s Answer is \"%s\"%s\n", ANSI_PREFIX, ANSI_INFO,\
                stQuestion_Answer_Data[QuestionPresent].ucAnswerHint, ANSI_POSFIX);
      printf("%s%s Your point now = %d%s\n", ANSI_PREFIX, ANSI_INFO,\
            stUser[QuestionPresent].ssUserPoints, ANSI_POSFIX);   
      /*check point if < 0*/
      if (!blIsTheLoser)
      {
        GetInfoFromUserInputMode();
      }
      else
      {
        ShowInforLoser();
      }
    }
  }
} /* End of ShowHint */

/***********************************************************************************************************************
** Function Name             : SetUserInputMode
**
** Description               : 
**
***********************************************************************************************************************/
void SetUserInputMode(uint8* ucModeID, uint8 ucLenOfInputMode)
{
  /* Check input mode is valid */
  if (ucLenOfInputMode != 1 || ((*ucModeID != 49) && (*ucModeID != 50)))
  {
    printf("%s%s WRONG INPUT MODE: INPUT AGAIN, ONLY MODE1 OR MODE2 IS ACCEPTABLE. %s\n", ANSI_PREFIX, ANSI_ERROR,ANSI_POSFIX);
    GetInfoFromUserInputMode();
  }
  else
  {
    stUser[QuestionPresent].ucModeID = *ucModeID;
    //Check Mode
    if (stUser[QuestionPresent].ucModeID == 49)
    {
      GetInfoFromUserInputLetter();
    }
    else
    {
      GetInfoFromUserInputAnswer();
    }
  } 

} /* End of SetUserInputMode */

/***********************************************************************************************************************
** Function Name             : SetUserAnswerFull
**
** Description               : 
**
***********************************************************************************************************************/
void SetUserAnswerFull(uint8* ucPlayerAnswer, uint8 ucLenOfInputAnswer)
{
  /**/
  boolean blIsAnswerValid = TRUE;
  for (uint8 i = 0; i < ucLenOfInputAnswer; i++)
  {
    if ((ucPlayerAnswer[i] >= ASCII_UPPER_MIN && ucPlayerAnswer[i] <=  ASCII_UPPER_MAX) || ucPlayerAnswer[i] == ASCII_SPACE)
    {
      continue;
    }
    else
    {
      blIsAnswerValid = FALSE;
      break;
    }
  }
  
  /* Check input answer is valid */
  if ((ucLenOfInputAnswer != stQuestion_Answer_Data[QuestionPresent].usLengthOfAnswer) || (blIsAnswerValid == FALSE))
  {
    printf("%s%s WRONG INPUT ANSWER: INPUT ANSWER AGAIN, ONLY UPPER CASE AND HAVE TO ENOUGH LETTER INCLUDE SPACE.%s\n",\
               ANSI_PREFIX, ANSI_ERROR, ANSI_POSFIX);
    /* Require input letter again */
    GetInfoFromUserInputAnswer();
  }
  else
  {
    memcpy(stUser[QuestionPresent].ucPlayerAnswer, ucPlayerAnswer, ucLenOfInputAnswer);
    CheckAndShowAnswer();
  } 
}/* End of SetUserAnswerFull */

/***********************************************************************************************************************
** Function Name             : GetInfoFromUserInputMode
**
** Description               : 
**
***********************************************************************************************************************/
void GetInfoFromUserInputMode()
{
  uint8 ucTempMode[MAX_LENGTH];
  printf("%s%s ENTER YOUR MODE TO PLAY, PLEASE TYPE 1 OR 2 !!!!%s\n", ANSI_PREFIX, ANSI_INFO, ANSI_POSFIX);
  fgets(ucTempMode, sizeof(ucTempMode), stdin); 
  SetUserInputMode(ucTempMode, strlen(ucTempMode) - 1);
} /* End of GetInfoFromUserInputMode */

/***********************************************************************************************************************
** Function Name             : GetInfoFromUserInputLetter
**
** Description               : 
**
***********************************************************************************************************************/
void GetInfoFromUserInputLetter()
{
  uint8 ucTempLetterInputByPlayer[MAX_LENGTH];
  printf("%s%s YOUR MODE IS 1: PLEASE TYPE ONE LETTER IN UPPER-CASE !!!!%s\n", ANSI_PREFIX, ANSI_INFO, ANSI_POSFIX);
  fgets(ucTempLetterInputByPlayer, sizeof(ucTempLetterInputByPlayer), stdin);

  /* Check input letter is valid */
  if (((strlen(ucTempLetterInputByPlayer) - 1) != 1) || (ucTempLetterInputByPlayer[0] < ASCII_UPPER_MIN) || (ucTempLetterInputByPlayer[0] > ASCII_UPPER_MAX))
  {
    printf("%s%s WRONG INPUT LETTER: INPUT LETTER AGAIN, ONLY 1 LETTER AND UPPER CASE. %s\n", ANSI_PREFIX, ANSI_ERROR,ANSI_POSFIX);
    /* Require input letter again */
    GetInfoFromUserInputLetter();
  }
  else
  {
    stUser[QuestionPresent].ucAnswerLetter = ucTempLetterInputByPlayer[0];
    CheckAndUpdateHint();
  } 

} /* End of GetInfoFromUserInputLetter */

/***********************************************************************************************************************
** Function Name             : GetInfoFromUserInputAnswer
**
** Description               : 
**
***********************************************************************************************************************/
void GetInfoFromUserInputAnswer()
{
  uint8 ucFullAnswerInputByPlayer[MAX_LENGTH];
  printf("%s%s YOUR MODE IS 2: PLEASE TYPE FULL ANSWER !!!!%s\n", ANSI_PREFIX, ANSI_INFO, ANSI_POSFIX);
  fgets(ucFullAnswerInputByPlayer, sizeof(ucFullAnswerInputByPlayer), stdin);
  SetUserAnswerFull(ucFullAnswerInputByPlayer, strlen(ucFullAnswerInputByPlayer) - 1);
} /* End of GetInfoFromUserInputAnswer */

/***********************************************************************************************************************
** Function Name             : UpdateUserPoints
**
** Description               : 
**
***********************************************************************************************************************/
void UpdateUserPoints(PlayerAnswerState enPlayerAnswerState)
{
  switch (enPlayerAnswerState)
  {
  case MODE1_OK:
    stUser[QuestionPresent].ssUserPoints = stUser[QuestionPresent].ssUserPoints - 5;
    break;
  case MODE1_NG:
    stUser[QuestionPresent].ssUserPoints = stUser[QuestionPresent].ssUserPoints - 10;
    break;
  case MODE2_NG:
    stUser[QuestionPresent].ssUserPoints = stUser[QuestionPresent].ssUserPoints - 20;
    break;
  default:
    /* No action required */
    break;
  }
  /*check to user point <= 0*/
  if (stUser[QuestionPresent].ssUserPoints <= POINTS_MIN)
  {
    blIsTheLoser = TRUE;
  }
} /* End of UpdateUserPoints */

/***********************************************************************************************************************
** Function Name             : SetUserAction
**
** Description               : 
**
***********************************************************************************************************************/
void SetUserAction()
{
  uint8 ucReadAction;
  printf("%s%s NEXT QUESTION: 1   ||   QUIT GAME: 0%s\n", ANSI_PREFIX, ANSI_INFO, ANSI_POSFIX);
  scanf("%d", &ucReadAction);
  getchar(); // to remove \n in buffer
  if(ucReadAction == 1)
  {
    //next question
    QuestionPresent = QuestionPresent + 1;
    blIsTheLoser = FALSE;
    FirstScreenInformation();
  }
  else if (ucReadAction == 0)
  {
    SetDebugMode();
  }
  else
  {
    printf("%s%s WRONG INPUT ACTION: ONLY TYPE 1 OR 0.%s\n", ANSI_PREFIX, ANSI_ERROR, ANSI_POSFIX);
    SetUserAction();
  }
} /* End of SetUserAction */

/***********************************************************************************************************************
** Function Name             : SetDebugMode
**
** Description               : 
**
***********************************************************************************************************************/
void SetDebugMode()
{
  uint8 ucReadDebugMode;
  printf("%s%s BEFORE QUIT GAME, DO YOU WANT TO SET DUBUG MODE TO SEE ANSWER%s\n", ANSI_PREFIX, ANSI_INFO, ANSI_POSFIX);
  printf("%s%sDEBUG MODE ON: 1   ||   DEBUG MODE OFF: 0%s\n", ANSI_PREFIX, ANSI_INFO, ANSI_POSFIX);
  scanf("%d", &ucReadDebugMode);
  getchar(); // to remove \n in buffer
  if(ucReadDebugMode == 1)
  {
    //Show answer, then cook
    ShowAnswerOfDebugMode();
    //quit game.
    printf("============== BYE BYE, SEE YOU LATER :( ==============\n");
    exit(1);
  }
  else if (ucReadDebugMode == 0)
  {
    //quit game.
    printf("============== BYE BYE, SEE YOU LATER :( ==============\n");
    exit(1);
  }
  else
  {
    printf("%s%s WRONG INPUT ACTION: ONLY TYPE 1 OR 0.%s\n", ANSI_PREFIX, ANSI_ERROR, ANSI_POSFIX);
    SetDebugMode();
  }
} /* End of SetDebugMode */

/***********************************************************************************************************************
** Function Name             : FirstScreenInformation
**
** Description               : 
**
***********************************************************************************************************************/
void FirstScreenInformation()
{
  printf("%s\nQUESTION %d: %s %s\n", ANSI_PREFIX, QuestionPresent + 1, stQuestion_Answer_Data[QuestionPresent].ucQuestion,\
              ANSI_POSFIX);
  printf("%sHINT: ANSWER HAS %d WORD, %d LETTER: %s %s\n", ANSI_PREFIX,\
              stQuestion_Answer_Data[QuestionPresent].ucNumWordOfAnswer,\
              stQuestion_Answer_Data[QuestionPresent].usLengthOfAnswerForHint,\
              stQuestion_Answer_Data[QuestionPresent].ucAnswerHint, ANSI_POSFIX);
  printf("%sPLAYER POINT:%d %s\n", ANSI_PREFIX, stUser[QuestionPresent].ssUserPoints, ANSI_POSFIX);
  printf("\t\t\t\t%s\t\t\t\t\n", "$$$$$$$$$$ The Stage is Yours $$$$$$$$$$");
  /*Show mode for player to choose*/
  GetInfoFromUserInputMode();
}/* End of FirstScreenInformation */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/

int main(void)
{
  initialise_database();
  /*Introduce section*/
  printf("\n============================================== FUNNY GAME ==============================================\n");
  printf("This game is the assignment of 39-G C training course. The game has 10 funny questions. Each question\n\
  \rhas the hint, it shows the answer has how many words and letters. You will have default 100 points for\n\
  \reach question. Game has 2 modes for you to choose, MODE1 and MODE2. MODE1 - You will guess only one \n\
  \rletter, if the letter exists in the answer, the hint will show the position of that letter for you, and\n\
  \ryour point will be subtracted 5 points. if not, your point will be subtracted 10 points. MODE2 - You \n\
  \rwill guess the whole answer, if the answer is correct, you will be the winner of question and you will\n\
  \rchoose to move to next question or quit game. If not correct, your point will be subtracted 20 points \n\
  \rand you will continue answer the question. if your points less or equal 0, you will lose this answer.\n\
  \rYou can choose play next question or quit game. Before quit, you can choose DEBUG mode to see the answer.\n");
  printf("======================================== LET'S GO. JOIN THE GAME ========================================\n");
  FirstScreenInformation();
  return 0;
}
