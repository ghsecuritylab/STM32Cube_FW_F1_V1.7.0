/** 
  ******************************************************************************
  * @file    Examples_LL/I2C/I2C_TwoBoards_MasterRx_SlaveTx_IT/Src/stm32f1xx_it.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    14-April-2017
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_it.h"

/** @addtogroup STM32F1xx_LL_Examples
  * @{
  */

/** @addtogroup I2C_TwoBoards_MasterRx_SlaveTx_IT
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern __IO uint8_t ubNbDataToTransmit;
extern __IO uint8_t ubNbDataToReceive;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F1xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f1xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles external lines 10 to 15 interrupt request.
  * @param  None
  * @retval None
  */
void USER_BUTTON_IRQHANDLER(void)
{
  /* Manage Flags */
  if(LL_EXTI_IsActiveFlag_0_31(USER_BUTTON_EXTI_LINE) != RESET)
  {
    LL_EXTI_ClearFlag_0_31(USER_BUTTON_EXTI_LINE);

    /* Manage code in main.c.*/
    UserButton_Callback(); 
  }
}

#ifdef SLAVE_BOARD
/**
  * Brief   This function handles I2C1 (Slave) event interrupt request.
  * Param   None
  * Retval  None
  */
void I2C1_EV_IRQHandler(void)
{
  /* Check ADDR flag value in ISR register */
  if(LL_I2C_IsActiveFlag_ADDR(I2C1))
  {
    /* Verify the slave transfer direction, a write direction, Slave enters transmitter mode */
    if(LL_I2C_GetTransferDirection(I2C1) == LL_I2C_DIRECTION_WRITE)
    {
      /* Enable Buffer Interrupts */
      LL_I2C_EnableIT_BUF(I2C1);

      /* Clear ADDR flag value in ISR register */
      LL_I2C_ClearFlag_ADDR(I2C1);
    }
    else
    {
      /* Clear ADDR flag value in ISR register */
      LL_I2C_ClearFlag_ADDR(I2C1);

      /* Call Error function */
      Error_Callback();
    }
  }
  /* Check TXE flag value in ISR register */
  else if(LL_I2C_IsActiveFlag_TXE(I2C1))
  {
    /* Call function Slave Ready to Transmit Callback */
    Slave_Ready_To_Transmit_Callback();
  }
  /* Check BTF flag value in ISR register */
  else if(LL_I2C_IsActiveFlag_BTF(I2C1))
  {
    /* Send the next byte */
    /* Call function Slave Ready to Transmit Callback */
    Slave_Ready_To_Transmit_Callback();
  }
}

/**
  * Brief   This function handles I2C1 (Slave) error interrupt request.
  * Param   None
  * Retval  None
  */
void I2C1_ER_IRQHandler(void)
{
  /* Normal use case, if all bytes are sent and Acknowledge failure appears */
  /* This correspond to the end of communication */
  if((ubNbDataToTransmit == 0) && (LL_I2C_IsActiveFlag_AF(I2C1)))
  {
    /* Clear AF flag value in ISR register */
    LL_I2C_ClearFlag_AF(I2C1);

    /* Call function Slave Complete Callback */
    Slave_Complete_Callback();
  }
  else
  {
    /* Call Error function */
    Error_Callback();
  }
}

#else /* MASTER_BOARD */

/**
  * Brief   This function handles I2C1 (Master) interrupt request.
  * Param   None
  * Retval  None
  */
void I2C1_EV_IRQHandler(void)
{
  /* Check SB flag value in ISR register */
  if(LL_I2C_IsActiveFlag_SB(I2C1))
  {
    /* Send Slave address with a 7-Bit SLAVE_OWN_ADDRESS for a read request */
    LL_I2C_TransmitData8(I2C1, SLAVE_OWN_ADDRESS | I2C_REQUEST_READ);
  }
  /* Check ADDR flag value in ISR register */
  else if(LL_I2C_IsActiveFlag_ADDR(I2C1))
  {
    if(ubNbDataToReceive == 1)
    {
      /* Prepare the generation of a Non ACKnowledge condition after next received byte */
      LL_I2C_AcknowledgeNextData(I2C1, LL_I2C_NACK);
      
      /* Enable Buffer Interrupts */
      LL_I2C_EnableIT_BUF(I2C1);
    }
    else if(ubNbDataToReceive == 2)
    {
      /* Prepare the generation of a Non ACKnowledge condition after next received byte */
      LL_I2C_AcknowledgeNextData(I2C1, LL_I2C_NACK);
      
      /* Enable Pos */
      LL_I2C_EnableBitPOS(I2C1);
    }
    else
    {
      /* Enable Buffer Interrupts */
      LL_I2C_EnableIT_BUF(I2C1);
    }

    /* Clear ADDR flag value in ISR register */
    LL_I2C_ClearFlag_ADDR(I2C1);
  }
  /* Check BTF flag value in ISR register */
  else if(LL_I2C_IsActiveFlag_BTF(I2C1))
  {
    /* Call function Master Complete Callback */
    Master_Complete_Callback();
  }
  /* Check RXNE flag value in ISR register */
  else if(LL_I2C_IsActiveFlag_RXNE(I2C1))
  {
    /* Call function Master Reception Callback */
    Master_Reception_Callback();
  }
}

/**
  * Brief   This function handles I2C1 (Master) error interrupt request.
  * Param   None
  * Retval  None
  */
void I2C1_ER_IRQHandler(void)
{
  /* Call Error function */
  Error_Callback();
}
#endif /* SLAVE_BOARD */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
