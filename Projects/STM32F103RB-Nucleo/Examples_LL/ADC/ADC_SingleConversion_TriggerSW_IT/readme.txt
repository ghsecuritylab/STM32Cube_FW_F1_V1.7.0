/**
  @page ADC_SingleConversion_TriggerSW_IT ADC example
  
  @verbatim
  ******************** (C) COPYRIGHT 2016 STMicroelectronics *******************
  * @file    Examples_LL/ADC/ADC_SingleConversion_TriggerSW_IT/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    14-April-2017
  * @brief   Description of the ADC_SingleConversion_TriggerSW_IT example.
  ******************************************************************************
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
  @endverbatim

@par Example Description

How to use an ADC peripheral to perform a single ADC conversion on a channel, 
at each software start. This example uses the interrupt programming model 
(for polling or DMA programming models, please refer to other examples).
This example is based on the STM32F1xx ADC LL API.
The peripheral initialization is done using LL unitary service functions 
for optimization purposes (performance and size).

Example configuration:
ADC is configured to convert a single channel, in single conversion mode,
from SW trigger.
ADC interruption enabled: EOC (end of conversion of ADC group regular).

Example execution:
At each press on User Button, the ADC performs 1 conversion of the selected channel.
When conversion is completed, ADC interruption occurs.
IRQ handler callback function reads conversion data from ADC data register
and stores it into a variable, LED2 is turned on.

For debug: variables to monitor with debugger watch window:
 - "uhADCxConvertedData": ADC group regular conversion data
 - "uhADCxConvertedData_Voltage_mVolt": ADC conversion data computation to physical values

Connection needed:
Use an external power supply, adjust supply voltage and connect it to analog input pin (cf pin below).

Other peripherals used:
  1 GPIO for User Button
  1 GPIO for LED2
  1 GPIO for analog input: PA.04 (Arduino connector CN8 pin A2, Morpho connector CN7 pin 32)

@par Directory contents 

  - ADC/ADC_SingleConversion_TriggerSW_IT/Inc/stm32f1xx_it.h          Interrupt handlers header file
  - ADC/ADC_SingleConversion_TriggerSW_IT/Inc/main.h                  Header for main.c module
  - ADC/ADC_SingleConversion_TriggerSW_IT/Inc/stm32_assert.h          Template file to include assert_failed function
  - ADC/ADC_SingleConversion_TriggerSW_IT/Src/stm32f1xx_it.c          Interrupt handlers
  - ADC/ADC_SingleConversion_TriggerSW_IT/Src/main.c                  Main program
  - ADC/ADC_SingleConversion_TriggerSW_IT/Src/system_stm32f1xx.c      STM32F1xx system source file


@par Hardware and Software environment

  - This example runs on STM32F103xB devices.
    
  - This example has been tested with STM32F103RB-Nucleo board and can be
    easily tailored to any other supported device and development board.


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
