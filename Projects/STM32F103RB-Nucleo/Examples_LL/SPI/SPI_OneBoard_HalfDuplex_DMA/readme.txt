/**
  @page SPI_OneBoard_HalfDuplex_DMA SPI example
  
  @verbatim
  ******************** (C) COPYRIGHT 2016 STMicroelectronics *******************
  * @file    Examples_LL/SPI/SPI_OneBoard_HalfDuplex_DMA/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    14-April-2017
  * @brief   Description of the SPI_OneBoard_HalfDuplex_DMA example.
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

Configuration of GPIO and SPI peripherals to transmit
bytes from an SPI Master device to an SPI Slave device in DMA mode. This example
is based on the STM32F1xx SPI LL API. The peripheral initialization uses 
LL unitary service functions for optimization purposes (performance and size).

This example works with only one STM32F103RB-Nucleo.

SPI1 Peripheral is configured in Master mode Half-Duplex Tx.
SPI2 Peripheral is configured in Slave mode Half-Duplex Rx.
GPIO associated to User push-button is linked with EXTI. 

Example execution:

LED2 is blinking Fast (200ms) and wait User push-button action.
Press User push-button on BOARD start a Half-Duplex communication through DMA.
On MASTER side (SPI1), Clock will be generated on SCK line, Transmission done on MOSI Line.
On SLAVE side (SPI2) reception is done through the MISO Line.

LED2 is On if data is well received.

In case of errors, LED2 is blinking Slowly (1s).
@note You need to perform a reset on the board,then press the User button on 
       board to have the correct behaviour of this example.

@note Since some SPI1 pins (PB3/PB4) are mapped onto some pins used by the JTAG,
      a remap of SPI1 pins and disable of the JTAG are performed.

@par Directory contents 

  - SPI/SPI_OneBoard_HalfDuplex_DMA/Inc/stm32f1xx_it.h          Interrupt handlers header file
  - SPI/SPI_OneBoard_HalfDuplex_DMA/Inc/main.h                  Header for main.c module
  - SPI/SPI_OneBoard_HalfDuplex_DMA/Inc/stm32_assert.h          Template file to include assert_failed function
  - SPI/SPI_OneBoard_HalfDuplex_DMA/Src/stm32f1xx_it.c          Interrupt handlers
  - SPI/SPI_OneBoard_HalfDuplex_DMA/Src/main.c                  Main program
  - SPI/SPI_OneBoard_HalfDuplex_DMA/Src/system_stm32f1xx.c      STM32F1xx system source file

@par Hardware and Software environment

  - This example runs on STM32F103xB devices.

  - This example has been tested with STM32F103RB-Nucleo board and can be
    easily tailored to any other supported device and development board.

  - STM32F103RB-Nucleo Set-up
    - Connect Master SCK  PB3 to Slave SCK  PB13
    - Connect Master MOSI PB5 to Slave MISO PB14

Relation with Board connector:
  PB3  is connected to pin 31 of CN10 connector
  PB5  is connected to pin 29 of CN10 connector
  PB13 is connected to pin 30 of CN10 connector
  PB14 is connected to pin 28 of CN10 connector

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
