/**
  ******************************************************************************
  * @file    USB_Host/HID_RTOS/Src/menu.c 
  * @author  MCD Application Team
  * @version V1.6.0
  * @date    12-May-2017
  * @brief   This file implements Menu Functions
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright � 2016 STMicroelectronics International N.V. 
  * All rights reserved.</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------ */
#include "main.h"

/* Private typedef ----------------------------------------------------------- */
/* Private define ------------------------------------------------------------ */
/* Private macro ------------------------------------------------------------- */
/* Private variables --------------------------------------------------------- */
HID_DEMO_StateMachine hid_demo;
uint8_t prev_select = 0;
osSemaphoreId MenuEvent;

uint8_t *DEMO_KEYBOARD_menu[] = {
  (uint8_t *)
    "      1 - Start Keyboard / Clear                                            ",
  (uint8_t *)
    "      2 - Return                                                            ",
};

uint8_t *DEMO_MOUSE_menu[] = {
  (uint8_t *)
    "      1 - Start Mouse / Re-Initialize                                       ",
  (uint8_t *)
    "      2 - Return                                                            ",
};

uint8_t *DEMO_HID_menu[] = {
  (uint8_t *)
    "      1 - Start HID                                                         ",
  (uint8_t *)
    "      2 - Re-Enumerate                                                       ",
};

/* Private function prototypes ----------------------------------------------- */
static void HID_DEMO_ProbeKey(JOYState_TypeDef state);
static void USBH_MouseDemo(USBH_HandleTypeDef * phost);
static void USBH_KeybdDemo(USBH_HandleTypeDef * phost);
static void HID_MenuThread(void const *argument);

/* Private functions --------------------------------------------------------- */

/**
  * @brief  Demo state machine.
  * @param  None
  * @retval None
  */
void HID_MenuInit(void)
{
  /* Create Menu Semaphore */
  osSemaphoreDef(osSem);

  MenuEvent = osSemaphoreCreate(osSemaphore(osSem), 1);

  /* Force menu to show Item 0 by default */
  osSemaphoreRelease(MenuEvent);

  /* Menu task */
  osThreadDef(Menu_Thread, HID_MenuThread, osPriorityHigh, 0,
              8 * configMINIMAL_STACK_SIZE);
  osThreadCreate(osThread(Menu_Thread), NULL);

  BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
  BSP_LCD_DisplayStringAtLine(15,
                              (uint8_t *)
                              "Use [Joystick Left/Right] to scroll up/down");
  BSP_LCD_DisplayStringAtLine(16,
                              (uint8_t *)
                              "Use [Joystick Up/Down] to scroll HID menu");
}

/**
  * @brief  Updates the Menu. 
  * @param  None
  * @retval None
  */
void HID_UpdateMenu(void)
{
  /* Force menu to show Item 0 by default */
  hid_demo.state = HID_DEMO_IDLE;
  osSemaphoreRelease(MenuEvent);
}

/**
  * @brief  User task
  * @param  pvParameters not used
  * @retval None
  */
void HID_MenuThread(void const *argument)
{
  for (;;)
  {
    if (osSemaphoreWait(MenuEvent, osWaitForever) == osOK)
    {
      switch (hid_demo.state)
      {
      case HID_DEMO_IDLE:
        HID_SelectItem(DEMO_HID_menu, 0);
        hid_demo.state = HID_DEMO_WAIT;
        hid_demo.select = 0;
        osSemaphoreRelease(MenuEvent);
        break;

      case HID_DEMO_WAIT:
        if (hid_demo.select != prev_select)
        {
          prev_select = hid_demo.select;

          HID_SelectItem(DEMO_HID_menu, hid_demo.select & 0x7F);
          /* Handle select item */
          if (hid_demo.select & 0x80)
          {
            switch (hid_demo.select & 0x7F)
            {
            case 0:
              hid_demo.state = HID_DEMO_START;
              osSemaphoreRelease(MenuEvent);
              break;

            case 1:
              hid_demo.state = HID_DEMO_REENUMERATE;
              osSemaphoreRelease(MenuEvent);
              break;

            default:
              break;
            }
          }
        }
        break;

      case HID_DEMO_START:
        if (Appli_state == APPLICATION_READY)
        {
          if (USBH_HID_GetDeviceType(&hUSBHost) == HID_KEYBOARD)
          {
            hid_demo.keyboard_state = HID_KEYBOARD_IDLE;
            hid_demo.state = HID_DEMO_KEYBOARD;
          }
          else if (USBH_HID_GetDeviceType(&hUSBHost) == HID_MOUSE)
          {
            hid_demo.mouse_state = HID_MOUSE_IDLE;
            hid_demo.state = HID_DEMO_MOUSE;
          }
        }
        else
        {
          LCD_ErrLog("No supported HID device!\n");
          hid_demo.state = HID_DEMO_WAIT;
        }
        osSemaphoreRelease(MenuEvent);
        break;

      case HID_DEMO_REENUMERATE:
        /* Force MSC Device to re-enumerate */
        USBH_ReEnumerate(&hUSBHost);
        hid_demo.state = HID_DEMO_WAIT;
        osSemaphoreRelease(MenuEvent);
        break;

      case HID_DEMO_MOUSE:
        if (Appli_state == APPLICATION_READY)
        {
          HID_MouseMenuProcess();
          USBH_MouseDemo(&hUSBHost);
        }
        break;

      case HID_DEMO_KEYBOARD:
        if (Appli_state == APPLICATION_READY)
        {
          HID_KeyboardMenuProcess();
          USBH_KeybdDemo(&hUSBHost);
        }
        break;

      default:
        break;
      }

      if (Appli_state == APPLICATION_DISCONNECT)
      {
        Appli_state = APPLICATION_IDLE;
        LCD_LOG_ClearTextZone();
        LCD_ErrLog("HID device disconnected!\n");
        hid_demo.state = HID_DEMO_IDLE;
        hid_demo.select = 0;
      }
      hid_demo.select &= 0x7F;
    }
  }
}

/**
  * @brief  The function is a callback about HID Data events
  * @param  phost: Selected device
  * @retval None
  */
void USBH_HID_EventCallback(USBH_HandleTypeDef * phost)
{
  osSemaphoreRelease(MenuEvent);
}

/**
  * @brief  Manages the menu on the screen.
  * @param  menu: Menu table
  * @param  item: Selected item to be highlighted
  * @retval None
  */
void HID_SelectItem(uint8_t ** menu, uint8_t item)
{
  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);

  switch (item)
  {
  case 0:
    BSP_LCD_SetBackColor(LCD_COLOR_MAGENTA);
    BSP_LCD_DisplayStringAtLine(18, menu[0]);
    BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
    BSP_LCD_DisplayStringAtLine(19, menu[1]);
    break;

  case 1:
    BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
    BSP_LCD_DisplayStringAtLine(18, menu[0]);
    BSP_LCD_SetBackColor(LCD_COLOR_MAGENTA);
    BSP_LCD_DisplayStringAtLine(19, menu[1]);
    BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
    break;
  }
  BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
}

/**
  * @brief  Probes the HID joystick state.
  * @param  state: Joystick state
  * @retval None
  */
static void HID_DEMO_ProbeKey(JOYState_TypeDef state)
{
  /* Handle Menu inputs */
  if ((state == JOY_UP) && (hid_demo.select > 0))
  {
    hid_demo.select--;
  }
  else if ((state == JOY_DOWN) && (hid_demo.select < 1))
  {
    hid_demo.select++;
  }
  else if (state == JOY_SEL)
  {
    hid_demo.select |= 0x80;
  }
}

/**
  * @brief  EXTI line detection callbacks.
  * @param  GPIO_Pin: Specifies the pins connected EXTI line
  * @retval None
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  __IO JOYState_TypeDef JoyState = JOY_NONE;

  if (GPIO_Pin == GPIO_PIN_14)
  {
    /* Get the Joystick State */
    JoyState = BSP_JOY_GetState();

    HID_DEMO_ProbeKey(JoyState);

    switch (JoyState)
    {
    case JOY_LEFT:
      LCD_LOG_ScrollBack();
      break;

    case JOY_RIGHT:
      LCD_LOG_ScrollForward();
      break;

    default:
      break;
    }
    /* Clear joystick interrupt pending bits */
    BSP_IO_ITClear(JOY_ALL_PINS);
    osSemaphoreRelease(MenuEvent);
  }
}

/**
  * @brief  Main routine for Mouse application
  * @param  phost: Host handle
  * @retval None
  */
static void USBH_MouseDemo(USBH_HandleTypeDef * phost)
{
  HID_MOUSE_Info_TypeDef *m_pinfo;

  if (hid_demo.mouse_state != HID_MOUSE_START)
  {
    m_pinfo = USBH_HID_GetMouseInfo(phost);

    if (m_pinfo != NULL)
    {
      /* Handle Mouse data position */
      USR_MOUSE_ProcessData(&mouse_info);

      if (m_pinfo->buttons[0])
      {
        HID_MOUSE_ButtonPressed(0);
      }
      else
      {
        HID_MOUSE_ButtonReleased(0);
      }

      if (m_pinfo->buttons[1])
      {
        HID_MOUSE_ButtonPressed(2);
      }
      else
      {
        HID_MOUSE_ButtonReleased(2);
      }

      if (m_pinfo->buttons[2])
      {
        HID_MOUSE_ButtonPressed(1);
      }
      else
      {
        HID_MOUSE_ButtonReleased(1);
      }
    }
  }
}

/**
  * @brief  Main routine for Keyboard application
  * @param  phost: Host handle
  * @retval None
  */
static void USBH_KeybdDemo(USBH_HandleTypeDef * phost)
{
  HID_KEYBD_Info_TypeDef *k_pinfo;
  char c;

  if (hid_demo.keyboard_state != HID_KEYBOARD_START)
  {

    k_pinfo = USBH_HID_GetKeybdInfo(phost);

    if (k_pinfo != NULL)
    {
      c = USBH_HID_GetASCIICode(k_pinfo);
      if (c != 0)
      {
        USR_KEYBRD_ProcessData(c);
      }
    }
  }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
