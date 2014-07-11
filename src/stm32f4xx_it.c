/**
 * @file stm32f4xx_it.c Interrupt handler routines.
 * @author Thomas Reidemeister <thomas@labforge.ca>
 * @addtogroup INTERRUPTS
 * @{
 */

#include "stm32f4xx_it.h"
#include "stm32f4xx_conf.h"

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

///******************************************************************************/
///*                 STM32F4xx Peripherals Interrupt Handlers                   */
///*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
///*  available peripheral interrupt handler's name please refer to the startup */
///*  file (startup_stm32f4xx.s).                                               */
///******************************************************************************/
//
//#ifdef USE_USB_OTG_FS
//void OTG_FS_WKUP_IRQHandler(void)
//{
//  if(USB_OTG_dev.cfg.low_power)
//  {
//    *(uint32_t *)(0xE000ED10) &= 0xFFFFFFF9 ;
//    SystemInit();
//    USB_OTG_UngateClock(&USB_OTG_dev);
//  }
//  EXTI_ClearITPendingBit(EXTI_Line18);
//}
//#endif
//
///**
//  * @brief  This function handles OTG_HS Handler.
//  * @param  None
//  * @retval None
//  */
//void OTG_FS_IRQHandler(void)
//{
//  USBD_OTG_ISR_Handler (&USB_OTG_dev);
//}

/** @{ */
