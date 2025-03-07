/**
  @page RTC_Alarm_Init RTC example
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    Examples_LL/RTC/RTC_Alarm_Init/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    14-April-2017
  * @brief   Description of the RTC example.
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

Configuration of the RTC LL API to configure and generate an alarm using the RTC peripheral. The peripheral 
initialization uses the LL initialization function.

In this example, after start-up, SYSCLK is configured to the max frequency using the PLL with
HSI as clock source.

The RTC peripheral configuration is ensured by the Configure_RTC() function 
(configure of the needed RTC resources according to the used hardware CLOCK, 
PWR, RTC clock source and BackUp). You may update this function to change RTC configuration.

@note LSE oscillator clock is used as RTC clock source by default.
      The user can use also LSI or HSE_DIV128 as RTC clock source. The user uncomment the adequate 
      line on the main.c file.
      @code
         /* #define RTC_CLOCK_SOURCE_LSI */
         #define RTC_CLOCK_SOURCE_LSE
         /* #define RTC_CLOCK_SOURCE_HSE_DIV128 */
      @endcode
      LSI oscillator clock is delivered by a clock frequency around 40 kHz RC(between 30 kHz and 60 kHz).
      LSE (when available on board) is delivered by a 32.768 kHz crystal.
      HSE clock divided by 128 (on this Board HSE_DIV128 = 62.500 kHz).
      
@note The frequency dispersion of the Low Speed Internal RC (LSI) oscillator can be calibrated to
      have accurate RTC time base with an acceptable accuracy. 
      For more details, refer to LSI calibration procedure in the Reference Manual.

Configure_RTC_Alarm function is then called to initialize the 
time, date and alarm.

In this example, the Time is set to 11:59:55 and the Alarm must be generated after 
30 seconds on 12:00:25.

LED1 is turned ON when the RTC Alarm is generated correctly.
The current time and date are updated and displayed on the debugger in aShowTime 
and aShowDate variables (watch or live watch).

In case of error, LED1 is toggling.

@par Directory contents 

  - RTC/RTC_Alarm_Init/Inc/stm32f1xx_it.h          Interrupt handlers header file
  - RTC/RTC_Alarm_Init/Inc/main.h                  Header for main.c module
  - RTC/RTC_Alarm_Init/Inc/stm32_assert.h          Template file to include assert_failed function
  - RTC/RTC_Alarm_Init/Src/stm32f1xx_it.c          Interrupt handlers
  - RTC/RTC_Alarm_Init/Src/main.c                  Main program
  - RTC/RTC_Alarm_Init/Src/system_stm32f1xx.c      STM32f1xx system source file


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
