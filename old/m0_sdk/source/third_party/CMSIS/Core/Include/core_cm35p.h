/**************************************************************************//**
 * @file     core_cm35p.h
 * @brief    CMSIS Cortex-M35P Core Peripheral Access Layer Header File
 * @version  V1.1.0
 * @date     27. March 2020
 ******************************************************************************/
/*
 * Copyright (c) 2018-2020 Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#if   defined ( __ICCARM__ )
  #pragma system_include                        /* treat file as system include file for MISRA check */
#elif defined (__clang__)
  #pragma clang system_header                   /* treat file as system include file */
#elif defined ( __GNUC__ )
  #pragma GCC diagnostic ignored "-Wpedantic"   /* disable pedantic warning due to unnamed structs/unions */
#endif

#ifndef __CORE_CM35P_H_GENERIC
#define __CORE_CM35P_H_GENERIC

#include <stdint.h>

#ifdef __cplusplus
 extern "C" {
#endif

/**
  \page CMSIS_MISRA_Exceptions  MISRA-C:2004 Compliance Exceptions
  CMSIS violates the following MISRA-C:2004 rules:

   \li Required Rule 8.5, object/function definition in header file.<br>
     Function definitions in header files are used to allow 'inlining'.

   \li Required Rule 18.4, declaration of union type or object of union type: '{...}'.<br>
     Unions are used for effective representation of core registers.

   \li Advisory Rule 19.7, Function-like macro defined.<br>
     Function-like macros are used to allow more efficient code.
 */


/*******************************************************************************
 *                 CMSIS definitions
 ******************************************************************************/
/**
  \ingroup Cortex_M35P
  @{
 */

#include "cmsis_version.h"

/*  CMSIS CM35P definitions */
#define __CM35P_CMSIS_VERSION_MAIN  (__CM_CMSIS_VERSION_MAIN)                  /*!< \deprecated [31:16] CMSIS HAL main version */
#define __CM35P_CMSIS_VERSION_SUB   (__CM_CMSIS_VERSION_SUB)                   /*!< \deprecated [15:0]  CMSIS HAL sub version */
#define __CM35P_CMSIS_VERSION       ((__CM35P_CMSIS_VERSION_MAIN << 16U) | \
                                      __CM35P_CMSIS_VERSION_SUB           )    /*!< \deprecated CMSIS HAL version number */

#define __CORTEX_M                 (35U)                                       /*!< Cortex-M Core */

/** __FPU_USED indicates whether an FPU is used or not.
    For this, __FPU_PRESENT has to be checked prior to making use of FPU specific registers and functions.
*/
#if defined ( __CC_ARM )
  #if defined (__TARGET_FPU_VFP)
    #if defined (__FPU_PRESENT) && (__FPU_PRESENT == 1U)
      #define __FPU_USED       1U
    #else
      #error "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)"
      #define __FPU_USED       0U
    #endif
  #else
    #define __FPU_USED         0U
  #endif

  #if defined (__ARM_FEATURE_DSP) && (__ARM_FEATURE_DSP == 1U)
    #if defined (__DSP_PRESENT) && (__DSP_PRESENT == 1U)
      #define __DSP_USED       1U
    #else
      #error "Compiler generates DSP (SIMD) instructions for a devices without DSP extensions (check __DSP_PRESENT)"
      #define __DSP_USED         0U
    #endif
  #else
    #define __DSP_USED         0U
  #endif

#elif defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #if defined (__ARM_FP)
    #if defined (__FPU_PRESENT) && (__FPU_PRESENT == 1U)
      #define __FPU_USED       1U
    #else
      #warning "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)"
      #define __FPU_USED       0U
    #endif
  #else
    #define __FPU_USED         0U
  #endif

  #if defined (__ARM_FEATURE_DSP) && (__ARM_FEATURE_DSP == 1U)
    #if defined (__DSP_PRESENT) && (__DSP_PRESENT == 1U)
      #define __DSP_USED       1U
    #else
      #error "Compiler generates DSP (SIMD) instructions for a devices without DSP extensions (check __DSP_PRESENT)"
      #define __DSP_USED         0U
    #endif
  #else
    #define __DSP_USED         0U
  #endif

#elif defined ( __GNUC__ )
  #if defined (__VFP_FP__) && !defined(__SOFTFP__)
    #if defined (__FPU_PRESENT) && (__FPU_PRESENT == 1U)
      #define __FPU_USED       1U
    #else
      #error "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)"
      #define __FPU_USED       0U
    #endif
  #else
    #define __FPU_USED         0U
  #endif

  #if defined (__ARM_FEATURE_DSP) && (__ARM_FEATURE_DSP == 1U)
    #if defined (__DSP_PRESENT) && (__DSP_PRESENT == 1U)
      #define __DSP_USED       1U
    #else
      #error "Compiler generates DSP (SIMD) instructions for a devices without DSP extensions (check __DSP_PRESENT)"
      #define __DSP_USED         0U
    #endif
  #else
    #define __DSP_USED         0U
  #endif

#elif defined ( __ICCARM__ )
  #if defined (__ARMVFP__)
    #if defined (__FPU_PRESENT) && (__FPU_PRESENT == 1U)
      #define __FPU_USED       1U
    #else
      #error "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)"
      #define __FPU_USED       0U
    #endif
  #else
    #define __FPU_USED         0U
  #endif

  #if defined (__ARM_FEATURE_DSP) && (__ARM_FEATURE_DSP == 1U)
    #if defined (__DSP_PRESENT) && (__DSP_PRESENT == 1U)
      #define __DSP_USED       1U
    #else
      #error "Compiler generates DSP (SIMD) instructions for a devices without DSP extensions (check __DSP_PRESENT)"
      #define __DSP_USED         0U
    #endif
  #else
    #define __DSP_USED         0U
  #endif

#elif defined ( __TI_ARM__ )
  #if defined (__TI_VFP_SUPPORT__)
    #if defined (__FPU_PRESENT) && (__FPU_PRESENT == 1U)
      #define __FPU_USED       1U
    #else
      #error "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)"
      #define __FPU_USED       0U
    #endif
  #else
    #define __FPU_USED         0U
  #endif

#elif defined ( __TASKING__ )
  #if defined (__FPU_VFP__)
    #if defined (__FPU_PRESENT) && (__FPU_PRESENT == 1U)
      #define __FPU_USED       1U
    #else
      #error "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)"
      #define __FPU_USED       0U
    #endif
  #else
    #define __FPU_USED         0U
  #endif

#elif defined ( __CSMC__ )
  #if ( __CSMC__ & 0x400U)
    #if defined (__FPU_PRESENT) && (__FPU_PRESENT == 1U)
      #define __FPU_USED       1U
    #else
      #error "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)"
      #define __FPU_USED       0U
    #endif
  #else
    #define __FPU_USED         0U
  #endif

#endif

#include "cmsis_compiler.h"               /* CMSIS compiler specific defines */


#ifdef __cplusplus
}
#endif

#endif /* __CORE_CM35P_H_GENERIC */

#ifndef __CMSIS_GENERIC

#ifndef __CORE_CM35P_H_DEPENDANT
#define __CORE_CM35P_H_DEPENDANT

#ifdef __cplusplus
 extern "C" {
#endif

/* check device defines and use defaults */
#if defined __CHECK_DEVICE_DEFINES
  #ifndef __CM35P_REV
    #define __CM35P_REV               0x0000U
    #warning "__CM35P_REV not defined in device header file; using default!"
  #endif

  #ifndef __FPU_PRESENT
    #define __FPU_PRESENT             0U
    #warning "__FPU_PRESENT not defined in device header file; using default!"
  #endif

  #ifndef __MPU_PRESENT
    #define __MPU_PRESENT             0U
    #warning "__MPU_PRESENT not defined in device header file; using default!"
  #endif

  #ifndef __SAUREGION_PRESENT
    #define __SAUREGION_PRESENT       0U
    #warning "__SAUREGION_PRESENT not defined in device header file; using default!"
  #endif

  #ifndef __DSP_PRESENT
    #define __DSP_PRESENT             0U
    #warning "__DSP_PRESENT not defined in device header file; using default!"
  #endif
  
  #ifndef __VTOR_PRESENT
    #define __VTOR_PRESENT             1U
    #warning "__VTOR_PRESENT not defined in device header file; using default!"
  #endif
  
  #ifndef __NVIC_PRIO_BITS
    #define __NVIC_PRIO_BITS          3U
    #warning "__NVIC_PRIO_BITS not defined in device header file; using default!"
  #endif

  #ifndef __Vendor_SysTickConfig
    #define __Vendor_SysTickConfig    0U
    #warning "__Vendor_SysTickConfig not defined in device header file; using default!"
  #endif
#endif

/* IO definitions (access restrictions to peripheral registers) */
/**
    \defgroup CMSIS_glob_defs CMSIS Global Defines

    <strong>IO Type Qualifiers</strong> are used
    \li to specify the access to peripheral variables.
    \li for automatic generation of peripheral register debug information.
*/
#ifdef __cplusplus
  #define   __I     volatile             /*!< Defines 'read only' permissions */
#else
  #define   __I     volatile const       /*!< Defines 'read only' permissions */
#endif
#define     __O     volatile             /*!< Defines 'write only' permissions */
#define     __IO    volatile             /*!< Defines 'read / write' permissions */

/* following defines should be used for structure members */
#define     __IM     volatile const      /*! Defines 'read only' structure member permissions */
#define     __OM     volatile            /*! Defines 'write only' structure member permissions */
#define     __IOM    volatile            /*! Defines 'read / write' structure member permissions */

/*@} end of group Cortex_M35P */



/*******************************************************************************
 *                 Register Abstraction
  Core Register contain:
  - Core Register
  - Core NVIC Register
  - Core SCB Register
  - Core SysTick Register
  - Core Debug Register
  - Core MPU Register
  - Core SAU Register
  - Core FPU Register
 ******************************************************************************/
/**
  \defgroup CMSIS_core_register Defines and Type Definitions
  \brief Type definitions and defines for Cortex-M processor based devices.
*/

/**
  \ingroup    CMSIS_core_register
  \defgroup   CMSIS_CORE  Status and Control Registers
  \brief      Core Register type definitions.
  @{
 */

/**
  \brief  Union type to access the Application Program Status Register (APSR).
 */
typedef union
{
  struct
  {
    uint32_t _reserved0:16;              /*!< bit:  0..15  Reserved */
    uint32_t GE:4;                       /*!< bit: 16..19  Greater than or Equal flags */
    uint32_t _reserved1:7;               /*!< bit: 20..26  Reserved */
    uint32_t Q:1;                        /*!< bit:     27  Saturation condition flag */
    uint32_t V:1;                        /*!< bit:     28  Overflow condition code flag */
    uint32_t C:1;                        /*!< bit:     29  Carry condition code flag */
    uint32_t Z:1;                        /*!< bit:     30  Zero condition code flag */
    uint32_t N:1;                        /*!< bit:     31  Negative condition code flag */
  } b;                                   /*!< Structure used for bit  access */
  uint32_t w;                            /*!< Type      used for word access */
} APSR_Type;

/* APSR Register Definitions */
#define APSR_N_Pos                         31U                                            /*!< APSR: N Position */
#define APSR_N_Msk                         (1UL << APSR_N_Pos)                            /*!< APSR: N Mask */

#define APSR_Z_Pos                         30U                                            /*!< APSR: Z Position */
#define APSR_Z_Msk                         (1UL << APSR_Z_Pos)                            /*!< APSR: Z Mask */

#define APSR_C_Pos                         29U                                            /*!< APSR: C Position */
#define APSR_C_Msk                         (1UL << APSR_C_Pos)                            /*!< APSR: C Mask */

#define APSR_V_Pos                         28U                                            /*!< APSR: V Position */
#define APSR_V_Msk                         (1UL << APSR_V_Pos)                            /*!< APSR: V Mask */

#define APSR_Q_Pos                         27U                                            /*!< APSR: Q Position */
#define APSR_Q_Msk                         (1UL << APSR_Q_Pos)                            /*!< APSR: Q Mask */

#define APSR_GE_Pos                        16U                                            /*!< APSR: GE Position */
#define APSR_GE_Msk                        (0xFUL << APSR_GE_Pos)                         /*!< APSR: GE Mask */


/**
  \brief  Union type to access the Interrupt Program Status Register (IPSR).
 */
typedef union
{
  struct
  {
    uint32_t ISR:9;                      /*!< bit:  0.. 8  Exception number */
    uint32_t _reserved0:23;              /*!< bit:  9..31  Reserved */
  } b;                                   /*!< Structure used for bit  access */
  uint32_t w;                            /*!< Type      used for word access */
} IPSR_Type;

/* IPSR Register Definitions */
#define IPSR_ISR_Pos                        0U                                            /*!< IPSR: ISR Position */
#define IPSR_ISR_Msk                       (0x1FFUL /*<< IPSR_ISR_Pos*/)                  /*!< IPSR: ISR Mask */


/**
  \brief  Union type to access the Special-Purpose Program Status Registers (xPSR).
 */
typedef union
{
  struct
  {
    uint32_t ISR:9;                      /*!< bit:  0.. 8  Exception number */
    uint32_t _reserved0:7;               /*!< bit:  9..15  Reserved */
    uint32_t GE:4;                       /*!< bit: 16..19  Greater than or Equal flags */
    uint32_t _reserved1:4;               /*!< bit: 20..23  Reserved */
    uint32_t T:1;                        /*!< bit:     24  Thumb bit        (read 0) */
    uint32_t IT:2;                       /*!< bit: 25..26  saved IT state   (read 0) */
    uint32_t Q:1;                        /*!< bit:     27  Saturation condition flag */
    uint32_t V:1;                        /*!< bit:     28  Overflow condition code flag */
    uint32_t C:1;                        /*!< bit:     29  Carry condition code flag */
    uint32_t Z:1;                        /*!< bit:     30  Zero condition code flag */
    uint32_t N:1;                        /*!< bit:     31  Negative condition code flag */
  } b;                                   /*!< Structure used for bit  access */
  uint32_t w;                            /*!< Type      used for word access */
} xPSR_Type;

/* xPSR Register Definitions */
#define xPSR_N_Pos                         31U                                            /*!< xPSR: N Position */
#define xPSR_N_Msk                         (1UL << xPSR_N_Pos)                            /*!< xPSR: N Mask */

#define xPSR_Z_Pos                         30U                                            /*!< xPSR: Z Position */
#define xPSR_Z_Msk                         (1UL << xPSR_Z_Pos)                            /*!< xPSR: Z Mask */

#define xPSR_C_Pos                         29U                                            /*!< xPSR: C Position */
#define xPSR_C_Msk                         (1UL << xPSR_C_Pos)                            /*!< xPSR: C Mask */

#define xPSR_V_Pos                         28U                                            /*!< xPSR: V Position */
#define xPSR_V_Msk                         (1UL << xPSR_V_Pos)                            /*!< xPSR: V Mask */

#define xPSR_Q_Pos                         27U                                            /*!< xPSR: Q Position */
#define xPSR_Q_Msk                         (1UL << xPSR_Q_Pos)                            /*!< xPSR: Q Mask */

#define xPSR_IT_Pos                        25U                                            /*!< xPSR: IT Position */
#define xPSR_IT_Msk                        (3UL << xPSR_IT_Pos)                           /*!< xPSR: IT Mask */

#define xPSR_T_Pos                         24U                                            /*!< xPSR: T Position */
#define xPSR_T_Msk                         (1UL << xPSR_T_Pos)                            /*!< xPSR: T Mask */

#define xPSR_GE_Pos                        16U                                            /*!< xPSR: GE Position */
#define xPSR_GE_Msk                        (0xFUL << xPSR_GE_Pos)                         /*!< xPSR: GE Mask */

#define xPSR_ISR_Pos                        0U                                            /*!< xPSR: ISR Position */
#define xPSR_ISR_Msk                       (0x1FFUL /*<< xPSR_ISR_Pos*/)                  /*!< xPSR: ISR Mask */


/**
  \brief  Union type to access the Control Registers (CONTROL).
 */
typedef union
{
  struct
  {
    uint32_t nPRIV:1;                    /*!< bit:      0  Execution privilege in Thread mode */
    uint32_t SPSEL:1;                    /*!< bit:      1  Stack-pointer select */
    uint32_t FPCA:1;                     /*!< bit:      2  Floating-point context active */
    uint32_t SFPA:1;                     /*!< bit:      3  Secure floating-point active */
    uint32_t _reserved1:28;              /*!< bit:  4..31  Reserved */
  } b;                                   /*!< Structure used for bit  access */
  uint32_t w;                            /*!< Type      used for word access */
} CONTROL_Type;

/* CONTROL Register Definitions */
#define CONTROL_SFPA_Pos                    3U                                            /*!< CONTROL: SFPA Position */
#define CONTROL_SFPA_Msk                   (1UL << CONTROL_SFPA_Pos)                      /*!< CONTROL: SFPA Mask */

#define CONTROL_FPCA_Pos                    2U                                            /*!< CONTROL: FPCA Position */
#define CONTROL_FPCA_Msk                   (1UL << CONTROL_FPCA_Pos)                      /*!< CONTROL: FPCA Mask */

#define CONTROL_SPSEL_Pos                   1U                                            /*!< CONTROL: SPSEL Position */
#define CONTROL_SPSEL_Msk                  (1UL << CONTROL_SPSEL_Pos)                     /*!< CONTROL: SPSEL Mask */

#define CONTROL_nPRIV_Pos                   0U                                            /*!< CONTROL: nPRIV Position */
#define CONTROL_nPRIV_Msk                  (1UL /*<< CONTROL_nPRIV_Pos*/)                 /*!< CONTROL: nPRIV Mask */

/*@} end of group CMSIS_CORE */


/**
  \ingroup    CMSIS_core_register
  \defgroup   CMSIS_NVIC  Nested Vectored Interrupt Controller (NVIC)
  \brief      Type definitions for the NVIC Registers
  @{
 */

/**
  \brief  Structure type to access the Nested Vectored Interrupt Controller (NVIC).
 */
typedef struct
{
  __IOM uint32_t ISER[16U];              /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register */
        uint32_t RESERVED0[16U];
  __IOM uint32_t ICER[16U];              /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register */
        uint32_t RSERVED1[16U];
  __IOM uint32_t ISPR[16U];              /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register */
        uint32_t RESERVED2[16U];
  __IOM uint32_t ICPR[16U];              /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register */
        uint32_t RESERVED3[16U];
  __IOM uint32_t IABR[16U];              /*!< Offset: 0x200 (R/W)  Interrupt Active bit Register */
        uint32_t RESERVED4[16U];
  __IOM uint32_t ITNS[16U];              /*!< Offset: 0x280 (R/W)  Interrupt Non-Secure State Register */
        uint32_t RESERVED5[16U];
  __IOM uint8_t  IPR[496U];              /*!< Offset: 0x300 (R/W)  Interrupt Priority Register (8Bit wide) */
        uint32_t RESERVED6[580U];
  __OM  uint32_t STIR;                   /*!< Offset: 0xE00 ( /W)  Software Trigger Interrupt Register */
}  NVIC_Type;

/* Software Triggered Interrupt Register Definitions */
#define NVIC_STIR_INTID_Pos                 0U                                         /*!< STIR: INTLINESNUM Position */
#define NVIC_STIR_INTID_Msk                (0x1FFUL /*<< NVIC_STIR_INTID_Pos*/)        /*!< STIR: INTLINESNUM Mask */

/*@} end of group CMSIS_NVIC */


/**
  \ingroup  CMSIS_core_register
  \defgroup CMSIS_SCB     System Control Block (SCB)
  \brief    Type definitions for the System Control Block Registers
  @{
 */

/**
  \brief  Structure type to access the System Control Block (SCB).
 */
typedef struct
{
  __IM  uint32_t CPUID;                  /*!< Offset: 0x000 (R/ )  CPUID Base Register */
  __IOM uint32_t ICSR;                   /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register */
  __IOM uint32_t VTOR;                   /*!< Offset: 0x008 (R/W)  Vector Table Offset Register */
  __IOM uint32_t AIRCR;                  /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register */
  __IOM uint32_t SCR;                    /*!< Offset: 0x010 (R/W)  System Control Register */
  __IOM uint32_t CCR;                    /*!< Offset: 0x014 (R/W)  Configuration Control Register */
  __IOM uint8_t  SHPR[12U];              /*!< Offset: 0x018 (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */
  __IOM uint32_t SHCSR;                  /*!< Offset: 0x024 (R/W)  System Handler Control and State Register */
  __IOM uint32_t CFSR;                   /*!< Offset: 0x028 (R/W)  Configurable Fault Status Register */
  __IOM uint32_t HFSR;                   /*!< Offset: 0x02C (R/W)  HardFault Status Register */
  __IOM uint32_t DFSR;                   /*!< Offset: 0x030 (R/W)  Debug Fault Status Register */
  __IOM uint32_t MMFAR;                  /*!< Offset: 0x034 (R/W)  MemManage Fault Address Register */
  __IOM uint32_t BFAR;                   /*!< Offset: 0x038 (R/W)  BusFault Address Register */
  __IOM uint32_t AFSR;                   /*!< Offset: 0x03C (R/W)  Auxiliary Fault Status Register */
  __IM  uint32_t ID_PFR[2U];             /*!< Offset: 0x040 (R/ )  Processor Feature Register */
  __IM  uint32_t ID_DFR;                 /*!< Offset: 0x048 (R/ )  Debug Feature Register */
  __IM  uint32_t ID_ADR;                 /*!< Offset: 0x04C (R/ )  Auxiliary Feature Register */
  __IM  uint32_t ID_MMFR[4U];            /*!< Offset: 0x050 (R/ )  Memory Model Feature Register */
  __IM  uint32_t ID_ISAR[6U];            /*!< Offset: 0x060 (R/ )  Instruction Set Attributes Register */
  __IM  uint32_t CLIDR;                  /*!< Offset: 0x078 (R/ )  Cache Level ID register */
  __IM  uint32_t CTR;                    /*!< Offset: 0x07C (R/ )  Cache Type register */
  __IM  uint32_t CCSIDR;                 /*!< Offset: 0x080 (R/ )  Cache Size ID Register */
  __IOM uint32_t CSSELR;                 /*!< Offset: 0x084 (R/W)  Cache Size Selection Register */
  __IOM uint32_t CPACR;                  /*!< Offset: 0x088 (R/W)  Coprocessor Access Control Register */
  __IOM uint32_t NSACR;                  /*!< Offset: 0x08C (R/W)  Non-Secure Access Control Register */
        uint32_t RESERVED3[92U];
  __OM  uint32_t STIR;                   /*!< Offset: 0x200 ( /W)  Software Triggered Interrupt Register */
        uint32_t RESERVED4[15U];
  __IM  uint32_t MVFR0;                  /*!< Offset: 0x240 (R/ )  Media and VFP Feature Register 0 */
  __IM  uint32_t MVFR1;                  /*!< Offset: 0x244 (R/ )  Media and VFP Feature Register 1 */
  __IM  uint32_t MVFR2;                  /*!< Offset: 0x248 (R/ )  Media and VFP Feature Register 2 */
        uint32_t RESERVED5[1U];
  __OM  uint32_t ICIALLU;                /*!< Offset: 0x250 ( /W)  I-Cache Invalidate All to PoU */
        uint32_t RESERVED6[1U];
  __OM  uint32_t ICIMVAU;                /*!< Offset: 0x258 ( /W)  I-Cache Invalidate by MVA to PoU */
  __OM  uint32_t DCIMVAC;                /*!< Offset: 0x25C ( /W)  D-Cache Invalidate by MVA to PoC */
  __OM  uint32_t DCISW;                  /*!< Offset: 0x260 ( /W)  D-Cache Invalidate by Set-way */
  __OM  uint32_t DCCMVAU;                /*!< Offset: 0x264 ( /W)  D-Cache Clean by MVA to PoU */
  __OM  uint32_t DCCMVAC;                /*!< Offset: 0x268 ( /W)  D-Cache Clean by MVA to PoC */
  __OM  uint32_t DCCSW;                  /*!< Offset: 0x26C ( /W)  D-Cache Clean by Set-way */
  __OM  uint32_t DCCIMVAC;               /*!< Offset: 0x270 ( /W)  D-Cache Clean and Invalidate by MVA to PoC */
  __OM  uint32_t DCCISW;                 /*!< Offset: 0x274 ( /W)  D-Cache Clean and Invalidate by Set-way */
} SCB_Type;

/* SCB CPUID Register Definitions */
#define SCB_CPUID_IMPLEMENTER_Pos          24U                                            /*!< SCB CPUID: IMPLEMENTER Position */
#define SCB_CPUID_IMPLEMENTER_Msk          (0xFFUL << SCB_CPUID_IMPLEMENTER_Pos)          /*!< SCB CPUID: IMPLEMENTER Mask */

#define SCB_CPUID_VARIANT_Pos              20U                                            /*!< SCB CPUID: VARIANT Position */
#define SCB_CPUID_VARIANT_Msk              (0xFUL << SCB_CPUID_VARIANT_Pos)               /*!< SCB CPUID: VARIANT Mask */

#define SCB_CPUID_ARCHITECTURE_Pos         16U                                            /*!< SCB CPUID: ARCHITECTURE Position */
#define SCB_CPUID_ARCHITECTURE_Msk         (0xFUL << SCB_CPUID_ARCHITECTURE_Pos)          /*!< SCB CPUID: ARCHITECTURE Mask */

#define SCB_CPUID_PARTNO_Pos                4U                                            /*!< SCB CPUID: PARTNO Position */
#define SCB_CPUID_PARTNO_Msk               (0xFFFUL << SCB_CPUID_PARTNO_Pos)              /*!< SCB CPUID: PARTNO Mask */

#define SCB_CPUID_REVISION_Pos              0U                                            /*!< SCB CPUID: REVISION Position */
#define SCB_CPUID_REVISION_Msk             (0xFUL /*<< SCB_CPUID_REVISION_Pos*/)          /*!< SCB CPUID: REVISION Mask */

/* SCB Interrupt Control State Register Definitions */
#define SCB_ICSR_PENDNMISET_Pos            31U                                            /*!< SCB ICSR: PENDNMISET Position */
#define SCB_ICSR_PENDNMISET_Msk            (1UL << SCB_ICSR_PENDNMISET_Pos)               /*!< SCB ICSR: PENDNMISET Mask */

#define SCB_ICSR_NMIPENDSET_Pos            SCB_ICSR_PENDNMISET_Pos                        /*!< SCB ICSR: NMIPENDSET Position, backward compatibility */
#define SCB_ICSR_NMIPENDSET_Msk            SCB_ICSR_PENDNMISET_Msk                        /*!< SCB ICSR: NMIPENDSET Mask, backward compatibility */

#define SCB_ICSR_PENDNMICLR_Pos            30U                                            /*!< SCB ICSR: PENDNMICLR Position */
#define SCB_ICSR_PENDNMICLR_Msk            (1UL << SCB_ICSR_PENDNMICLR_Pos)               /*!< SCB ICSR: PENDNMICLR Mask */

#define SCB_ICSR_PENDSVSET_Pos             28U                                            /*!< SCB ICSR: PENDSVSET Position */
#define SCB_ICSR_PENDSVSET_Msk             (1UL << SCB_ICSR_PENDSVSET_Pos)                /*!< SCB ICSR: PENDSVSET Mask */

#define SCB_ICSR_PENDSVCLR_Pos             27U                                            /*!< SCB ICSR: PENDSVCLR Position */
#define SCB_ICSR_PENDSVCLR_Msk             (1UL << SCB_ICSR_PENDSVCLR_Pos)                /*!< SCB ICSR: PENDSVCLR Mask */

#define SCB_ICSR_PENDSTSET_Pos             26U                                            /*!< SCB ICSR: PENDSTSET Position */
#define SCB_ICSR_PENDSTSET_Msk             (1UL << SCB_ICSR_PENDSTSET_Pos)                /*!< SCB ICSR: PENDSTSET Mask */

#define SCB_ICSR_PENDSTCLR_Pos             25U                                            /*!< SCB ICSR: PENDSTCLR Position */
#define SCB_ICSR_PENDSTCLR_Msk             (1UL << SCB_ICSR_PENDSTCLR_Pos)                /*!< SCB ICSR: PENDSTCLR Mask */

#define SCB_ICSR_STTNS_Pos                 24U                                            /*!< SCB ICSR: STTNS Position (Security Extension) */
#define SCB_ICSR_STTNS_Msk                 (1UL << SCB_ICSR_STTNS_Pos)                    /*!< SCB ICSR: STTNS Mask (Security Extension) */

#define SCB_ICSR_ISRPREEMPT_Pos            23U                                            /*!< SCB ICSR: ISRPREEMPT Position */
#define SCB_ICSR_ISRPREEMPT_Msk            (1UL << SCB_ICSR_ISRPREEMPT_Pos)               /*!< SCB ICSR: ISRPREEMPT Mask */

#define SCB_ICSR_ISRPENDING_Pos            22U                                            /*!< SCB ICSR: ISRPENDING Position */
#define SCB_ICSR_ISRPENDING_Msk            (1UL << SCB_ICSR_ISRPENDING_Pos)               /*!< SCB ICSR: ISRPENDING Mask */

#define SCB_ICSR_VECTPENDING_Pos           12U                                            /*!< SCB ICSR: VECTPENDING Position */
#define SCB_ICSR_VECTPENDING_Msk           (0x1FFUL << SCB_ICSR_VECTPENDING_Pos)          /*!< SCB ICSR: VECTPENDING Mask */

#define SCB_ICSR_RETTOBASE_Pos             11U                                            /*!< SCB ICSR: RETTOBASE Position */
#define SCB_ICSR_RETTOBASE_Msk             (1UL << SCB_ICSR_RETTOBASE_Pos)                /*!< SCB ICSR: RETTOBASE Mask */

#define SCB_ICSR_VECTACTIVE_Pos             0U                                            /*!< SCB ICSR: VECTACTIVE Position */
#define SCB_ICSR_VECTACTIVE_Msk            (0x1FFUL /*<< SCB_ICSR_VECTACTIVE_Pos*/)       /*!< SCB ICSR: VECTACTIVE Mask */

/* SCB Vector Table Offset Register Definitions */
#define SCB_VTOR_TBLOFF_Pos                 7U                                            /*!< SCB VTOR: TBLOFF Position */
#define SCB_VTOR_TBLOFF_Msk                (0x1FFFFFFUL << SCB_VTOR_TBLOFF_Pos)           /*!< SCB VTOR: TBLOFF Mask */

/* SCB Application Interrupt and Reset Control Register Definitions */
#define SCB_AIRCR_VECTKEY_Pos              16U                                            /*!< SCB AIRCR: VECTKEY Position */
#define SCB_AIRCR_VECTKEY_Msk              (0xFFFFUL << SCB_AIRCR_VECTKEY_Pos)            /*!< SCB AIRCR: VECTKEY Mask */

#define SCB_AIRCR_VECTKEYSTAT_Pos          16U                                            /*!< SCB AIRCR: VECTKEYSTAT Position */
#define SCB_AIRCR_VECTKEYSTAT_Msk          (0xFFFFUL << SCB_AIRCR_VECTKEYSTAT_Pos)        /*!< SCB AIRCR: VECTKEYSTAT Mask */

#define SCB_AIRCR_ENDIANESS_Pos            15U                                            /*!< SCB AIRCR: ENDIANESS Position */
#define SCB_AIRCR_ENDIANESS_Msk            (1UL << SCB_AIRCR_ENDIANESS_Pos)               /*!< SCB AIRCR: ENDIANESS Mask */

#define SCB_AIRCR_PRIS_Pos                 14U                                            /*!< SCB AIRCR: PRIS Position */
#define SCB_AIRCR_PRIS_Msk                 (1UL << SCB_AIRCR_PRIS_Pos)                    /*!< SCB AIRCR: PRIS Mask */

#define SCB_AIRCR_BFHFNMINS_Pos            13U                                            /*!< SCB AIRCR: BFHFNMINS Position */
#define SCB_AIRCR_BFHFNMINS_Msk            (1UL << SCB_AIRCR_BFHFNMINS_Pos)               /*!< SCB AIRCR: BFHFNMINS Mask */

#define SCB_AIRCR_PRIGROUP_Pos              8U                                            /*!< SCB AIRCR: PRIGROUP Position */
#define SCB_AIRCR_PRIGROUP_Msk             (7UL << SCB_AIRCR_PRIGROUP_Pos)                /*!< SCB AIRCR: PRIGROUP Mask */

#define SCB_AIRCR_SYSRESETREQS_Pos          3U                                            /*!< SCB AIRCR: SYSRESETREQS Position */
#define SCB_AIRCR_SYSRESETREQS_Msk         (1UL << SCB_AIRCR_SYSRESETREQS_Pos)            /*!< SCB AIRCR: SYSRESETREQS Mask */

#define SCB_AIRCR_SYSRESETREQ_Pos           2U                                            /*!< SCB AIRCR: SYSRESETREQ Position */
#define SCB_AIRCR_SYSRESETREQ_Msk          (1UL << SCB_AIRCR_SYSRESETREQ_Pos)             /*!< SCB AIRCR: SYSRESETREQ Mask */

#define SCB_AIRCR_VECTCLRACTIVE_Pos         1U                                            /*!< SCB AIRCR: VECTCLRACTIVE Position */
#define SCB_AIRCR_VECTCLRACTIVE_Msk        (1UL << SCB_AIRCR_VECTCLRACTIVE_Pos)           /*!< SCB AIRCR: VECTCLRACTIVE Mask */

/* SCB System Control Register Definitions */
#define SCB_SCR_SEVONPEND_Pos               4U                                            /*!< SCB SCR: SEVONPEND Position */
#define SCB_SCR_SEVONPEND_Msk              (1UL << SCB_SCR_SEVONPEND_Pos)                 /*!< SCB SCR: SEVONPEND Mask */

#define SCB_SCR_SLEEPDEEPS_Pos              3U                                            /*!< SCB SCR: SLEEPDEEPS Position */
#define SCB_SCR_SLEEPDEEPS_Msk             (1UL << SCB_SCR_SLEEPDEEPS_Pos)                /*!< SCB SCR: SLEEPDEEPS Mask */

#define SCB_SCR_SLEEPDEEP_Pos               2U                                            /*!< SCB SCR: SLEEPDEEP Position */
#define SCB_SCR_SLEEPDEEP_Msk              (1UL << SCB_SCR_SLEEPDEEP_Pos)                 /*!< SCB SCR: SLEEPDEEP Mask */

#define SCB_SCR_SLEEPONEXIT_Pos             1U                                            /*!< SCB SCR: SLEEPONEXIT Position */
#define SCB_SCR_SLEEPONEXIT_Msk            (1UL << SCB_SCR_SLEEPONEXIT_Pos)               /*!< SCB SCR: SLEEPONEXIT Mask */

/* SCB Configuration Control Register Definitions */
#define SCB_CCR_BP_Pos                     18U                                            /*!< SCB CCR: BP Position */
#define SCB_CCR_BP_Msk                     (1UL << SCB_CCR_BP_Pos)                        /*!< SCB CCR: BP Mask */

#define SCB_CCR_IC_Pos                     17U                                            /*!< SCB CCR: IC Position */
#define SCB_CCR_IC_Msk                     (1UL << SCB_CCR_IC_Pos)                        /*!< SCB CCR: IC Mask */

#define SCB_CCR_DC_Pos                     16U                                            /*!< SCB CCR: DC Position */
#define SCB_CCR_DC_Msk                     (1UL << SCB_CCR_DC_Pos)                        /*!< SCB CCR: DC Mask */

#define SCB_CCR_STKOFHFNMIGN_Pos           10U                                            /*!< SCB CCR: STKOFHFNMIGN Position */
#define SCB_CCR_STKOFHFNMIGN_Msk           (1UL << SCB_CCR_STKOFHFNMIGN_Pos)              /*!< SCB CCR: STKOFHFNMIGN Mask */

#define SCB_CCR_BFHFNMIGN_Pos               8U                                            /*!< SCB CCR: BFHFNMIGN Position */
#define SCB_CCR_BFHFNMIGN_Msk              (1UL << SCB_CCR_BFHFNMIGN_Pos)                 /*!< SCB CCR: BFHFNMIGN Mask */

#define SCB_CCR_DIV_0_TRP_Pos               4U                                            /*!< SCB CCR: DIV_0_TRP Position */
#define SCB_CCR_DIV_0_TRP_Msk              (1UL << SCB_CCR_DIV_0_TRP_Pos)                 /*!< SCB CCR: DIV_0_TRP Mask */

#define SCB_CCR_UNALIGN_TRP_Pos             3U                                            /*!< SCB CCR: UNALIGN_TRP Position */
#define SCB_CCR_UNALIGN_TRP_Msk            (1UL << SCB_CCR_UNALIGN_TRP_Pos)               /*!< SCB CCR: UNALIGN_TRP Mask */

#define SCB_CCR_USERSETMPEND_Pos            1U                                            /*!< SCB CCR: USERSETMPEND Position */
#define SCB_CCR_USERSETMPEND_Msk           (1UL << SCB_CCR_USERSETMPEND_Pos)              /*!< SCB CCR: USERSETMPEND Mask */

/* SCB System Handler Control and State Register Definitions */
#define SCB_SHCSR_HARDFAULTPENDED_Pos      21U                                            /*!< SCB SHCSR: HARDFAULTPENDED Position */
#define SCB_SHCSR_HARDFAULTPENDED_Msk      (1UL << SCB_SHCSR_HARDFAULTPENDED_Pos)         /*!< SCB SHCSR: HARDFAULTPENDED Mask */

#define SCB_SHCSR_SECUREFAULTPENDED_Pos    20U                                            /*!< SCB SHCSR: SECUREFAULTPENDED Position */
#define SCB_SHCSR_SECUREFAULTPENDED_Msk    (1UL << SCB_SHCSR_SECUREFAULTPENDED_Pos)       /*!< SCB SHCSR: SECUREFAULTPENDED Mask */

#define SCB_SHCSR_SECUREFAULTENA_Pos       19U                                            /*!< SCB SHCSR: SECUREFAULTENA Position */
#define SCB_SHCSR_SECUREFAULTENA_Msk       (1UL << SCB_SHCSR_SECUREFAULTENA_Pos)          /*!< SCB SHCSR: SECUREFAULTENA Mask */

#define SCB_SHCSR_USGFAULTENA_Pos          18U                                            /*!< SCB SHCSR: USGFAULTENA Position */
#define SCB_SHCSR_USGFAULTENA_Msk          (1UL << SCB_SHCSR_USGFAULTENA_Pos)             /*!< SCB SHCSR: USGFAULTENA Mask */

#define SCB_SHCSR_BUSFAULTENA_Pos          17U                                            /*!< SCB SHCSR: BUSFAULTENA Position */
#define SCB_SHCSR_BUSFAULTENA_Msk          (1UL << SCB_SHCSR_BUSFAULTENA_Pos)             /*!< SCB SHCSR: BUSFAULTENA Mask */

#define SCB_SHCSR_MEMFAULTENA_Pos          16U                                            /*!< SCB SHCSR: MEMFAULTENA Position */
#define SCB_SHCSR_MEMFAULTENA_Msk          (1UL << SCB_SHCSR_MEMFAULTENA_Pos)             /*!< SCB SHCSR: MEMFAULTENA Mask */

#define SCB_SHCSR_SVCALLPENDED_Pos         15U                                            /*!< SCB SHCSR: SVCALLPENDED Position */
#define SCB_SHCSR_SVCALLPENDED_Msk         (1UL << SCB_SHCSR_SVCALLPENDED_Pos)            /*!< SCB SHCSR: SVCALLPENDED Mask */

#define SCB_SHCSR_BUSFAULTPENDED_Pos       14U                                            /*!< SCB SHCSR: BUSFAULTPENDED Position */
#define SCB_SHCSR_BUSFAULTPENDED_Msk       (1UL << SCB_SHCSR_BUSFAULTPENDED_Pos)          /*!< SCB SHCSR: BUSFAULTPENDED Mask */

#define SCB_SHCSR_MEMFAULTPENDED_Pos       13U                                            /*!< SCB SHCSR: MEMFAULTPENDED Position */
#define SCB_SHCSR_MEMFAULTPENDED_Msk       (1UL << SCB_SHCSR_MEMFAULTPENDED_Pos)          /*!< SCB SHCSR: MEMFAULTPENDED Mask */

#define SCB_SHCSR_USGFAULTPENDED_Pos       12U                                            /*!< SCB SHCSR: USGFAULTPENDED Position */
#define SCB_SHCSR_USGFAULTPENDED_Msk       (1UL << SCB_SHCSR_USGFAULTPENDED_Pos)          /*!< SCB SHCSR: USGFAULTPENDED Mask */

#define SCB_SHCSR_SYSTICKACT_Pos           11U                                            /*!< SCB SHCSR: SYSTICKACT Position */
#define SCB_SHCSR_SYSTICKACT_Msk           (1UL << SCB_SHCSR_SYSTICKACT_Pos)              /*!< SCB SHCSR: SYSTICKACT Mask */

#define SCB_SHCSR_PENDSVACT_Pos            10U                                            /*!< SCB SHCSR: PENDSVACT Position */
#define SCB_SHCSR_PENDSVACT_Msk            (1UL << SCB_SHCSR_PENDSVACT_Pos)               /*!< SCB SHCSR: PENDSVACT Mask */

#define SCB_SHCSR_MONITORACT_Pos            8U                                            /*!< SCB SHCSR: MONITORACT Position */
#define SCB_SHCSR_MONITORACT_Msk           (1UL << SCB_SHCSR_MONITORACT_Pos)              /*!< SCB SHCSR: MONITORACT Mask */

#define SCB_SHCSR_SVCALLACT_Pos             7U                                            /*!< SCB SHCSR: SVCALLACT Position */
#define SCB_SHCSR_SVCALLACT_Msk            (1UL << SCB_SHCSR_SVCALLACT_Pos)               /*!< SCB SHCSR: SVCALLACT Mask */

#define SCB_SHCSR_NMIACT_Pos                5U                                            /*!< SCB SHCSR: NMIACT Position */
#define SCB_SHCSR_NMIACT_Msk               (1UL << SCB_SHCSR_NMIACT_Pos)                  /*!< SCB SHCSR: NMIACT Mask */

#define SCB_SHCSR_SECUREFAULTACT_Pos        4U                                            /*!< SCB SHCSR: SECUREFAULTACT Position */
#define SCB_SHCSR_SECUREFAULTACT_Msk       (1UL << SCB_SHCSR_SECUREFAULTACT_Pos)          /*!< SCB SHCSR: SECUREFAULTACT Mask */

#define SCB_SHCSR_USGFAULTACT_Pos           3U                                            /*!< SCB SHCSR: USGFAULTACT Position */
#define SCB_SHCSR_USGFAULTACT_Msk          (1UL << SCB_SHCSR_USGFAULTACT_Pos)             /*!< SCB SHCSR: USGFAULTACT Mask */

#define SCB_SHCSR_HARDFAULTACT_Pos          2U                                            /*!< SCB SHCSR: HARDFAULTACT Position */
#define SCB_SHCSR_HARDFAULTACT_Msk         (1UL << SCB_SHCSR_HARDFAULTACT_Pos)            /*!< SCB SHCSR: HARDFAULTACT Mask */

#define SCB_SHCSR_BUSFAULTACT_Pos           1U                                            /*!< SCB SHCSR: BUSFAULTACT Position */
#define SCB_SHCSR_BUSFAULTACT_Msk          (1UL << SCB_SHCSR_BUSFAULTACT_Pos)             /*!< SCB SHCSR: BUSFAULTACT Mask */

#define SCB_SHCSR_MEMFAULTACT_Pos           0U                                            /*!< SCB SHCSR: MEMFAULTACT Position */
#define SCB_SHCSR_MEMFAULTACT_Msk          (1UL /*<< SCB_SHCSR_MEMFAULTACT_Pos*/)         /*!< SCB SHCSR: MEMFAULTACT Mask */

/* SCB Configurable Fault Status Register Definitions */
#define SCB_CFSR_USGFAULTSR_Pos            16U                                            /*!< SCB CFSR: Usage Fault Status Register Position */
#define SCB_CFSR_USGFAULTSR_Msk            (0xFFFFUL << SCB_CFSR_USGFAULTSR_Pos)          /*!< SCB CFSR: Usage Fault Status Register Mask */

#define SCB_CFSR_BUSFAULTSR_Pos             8U                                            /*!< SCB CFSR: Bus Fault Status Register Position */
#define SCB_CFSR_BUSFAULTSR_Msk            (0xFFUL << SCB_CFSR_BUSFAULTSR_Pos)            /*!< SCB CFSR: Bus Fault Status Register Mask */

#define SCB_CFSR_MEMFAULTSR_Pos             0U                                            /*!< SCB CFSR: Memory Manage Fault Status Register Position */
#define SCB_CFSR_MEMFAULTSR_Msk            (0xFFUL /*<< SCB_CFSR_MEMFAULTSR_Pos*/)        /*!< SCB CFSR: Memory Manage Fault Status Register Mask */

/* MemManage Fault Status Register (part of SCB Configurable Fault Status Register) */
#define SCB_CFSR_MMARVALID_Pos             (SCB_SHCSR_MEMFAULTACT_Pos + 7U)               /*!< SCB CFSR (MMFSR): MMARVALID Position */
#define SCB_CFSR_MMARVALID_Msk             (1UL << SCB_CFSR_MMARVALID_Pos)                /*!< SCB CFSR (MMFSR): MMARVALID Mask */

#define SCB_CFSR_MLSPERR_Pos               (SCB_SHCSR_MEMFAULTACT_Pos + 5U)               /*!< SCB CFSR (MMFSR): MLSPERR Position */
#define SCB_CFSR_MLSPERR_Msk               (1UL << SCB_CFSR_MLSPERR_Pos)                  /*!< SCB CFSR (MMFSR): MLSPERR Mask */

#define SCB_CFSR_MSTKERR_Pos               (SCB_SHCSR_MEMFAULTACT_Pos + 4U)               /*!< SCB CFSR (MMFSR): MSTKERR Position */
#define SCB_CFSR_MSTKERR_Msk               (1UL << SCB_CFSR_MSTKERR_Pos)                  /*!< SCB CFSR (MMFSR): MSTKERR Mask */

#define SCB_CFSR_MUNSTKERR_Pos             (SCB_SHCSR_MEMFAULTACT_Pos + 3U)               /*!< SCB CFSR (MMFSR): MUNSTKERR Position */
#define SCB_CFSR_MUNSTKERR_Msk             (1UL << SCB_CFSR_MUNSTKERR_Pos)                /*!< SCB CFSR (MMFSR): MUNSTKERR Mask */

#define SCB_CFSR_DACCVIOL_Pos              (SCB_SHCSR_MEMFAULTACT_Pos + 1U)               /*!< SCB CFSR (MMFSR): DACCVIOL Position */
#define SCB_CFSR_DACCVIOL_Msk              (1UL << SCB_CFSR_DACCVIOL_Pos)                 /*!< SCB CFSR (MMFSR): DACCVIOL Mask */

#define SCB_CFSR_IACCVIOL_Pos              (SCB_SHCSR_MEMFAULTACT_Pos + 0U)               /*!< SCB CFSR (MMFSR): IACCVIOL Position */
#define SCB_CFSR_IACCVIOL_Msk              (1UL /*<< SCB_CFSR_IACCVIOL_Pos*/)             /*!< SCB CFSR (MMFSR): IACCVIOL Mask */

/* BusFault Status Register (part of SCB Configurable Fault Status Register) */
#define SCB_CFSR_BFARVALID_Pos            (SCB_CFSR_BUSFAULTSR_Pos + 7U)                  /*!< SCB CFSR (BFSR): BFARVALID Position */
#define SCB_CFSR_BFARVALID_Msk            (1UL << SCB_CFSR_BFARVALID_Pos)                 /*!< SCB CFSR (BFSR): BFARVALID Mask */

#define SCB_CFSR_LSPERR_Pos               (SCB_CFSR_BUSFAULTSR_Pos + 5U)                  /*!< SCB CFSR (BFSR): LSPERR Position */
#define SCB_CFSR_LSPERR_Msk               (1UL << SCB_CFSR_LSPERR_Pos)                    /*!< SCB CFSR (BFSR): LSPERR Mask */

#define SCB_CFSR_STKERR_Pos               (SCB_CFSR_BUSFAULTSR_Pos + 4U)                  /*!< SCB CFSR (BFSR): STKERR Position */
#define SCB_CFSR_STKERR_Msk               (1UL << SCB_CFSR_STKERR_Pos)                    /*!< SCB CFSR (BFSR): STKERR Mask */

#define SCB_CFSR_UNSTKERR_Pos             (SCB_CFSR_BUSFAULTSR_Pos + 3U)                  /*!< SCB CFSR (BFSR): UNSTKERR Position */
#define SCB_CFSR_UNSTKERR_Msk             (1UL << SCB_CFSR_UNSTKERR_Pos)                  /*!< SCB CFSR (BFSR): UNSTKERR Mask */

#define SCB_CFSR_IMPRECISERR_Pos          (SCB_CFSR_BUSFAULTSR_Pos + 2U)                  /*!< SCB CFSR (BFSR): IMPRECISERR Position */
#define SCB_CFSR_IMPRECISERR_Msk          (1UL << SCB_CFSR_IMPRECISERR_Pos)               /*!< SCB CFSR (BFSR): IMPRECISERR Mask */

#define SCB_CFSR_PRECISERR_Pos            (SCB_CFSR_BUSFAULTSR_Pos + 1U)                  /*!< SCB CFSR (BFSR): PRECISERR Position */
#define SCB_CFSR_PRECISERR_Msk            (1UL << SCB_CFSR_PRECISERR_Pos)                 /*!< SCB CFSR (BFSR): PRECISERR Mask */

#define SCB_CFSR_IBUSERR_Pos              (SCB_CFSR_BUSFAULTSR_Pos + 0U)                  /*!< SCB CFSR (BFSR): IBUSERR Position */
#define SCB_CFSR_IBUSERR_Msk              (1UL << SCB_CFSR_IBUSERR_Pos)                   /*!< SCB CFSR (BFSR): IBUSERR Mask */

/* UsageFault Status Register (part of SCB Configurable Fault Status Register) */
#define SCB_CFSR_DIVBYZERO_Pos            (SCB_CFSR_USGFAULTSR_Pos + 9U)                  /*!< SCB CFSR (UFSR): DIVBYZERO Position */
#define SCB_CFSR_DIVBYZERO_Msk            (1UL << SCB_CFSR_DIVBYZERO_Pos)                 /*!< SCB CFSR (UFSR): DIVBYZERO Mask */

#define SCB_CFSR_UNALIGNED_Pos            (SCB_CFSR_USGFAULTSR_Pos + 8U)                  /*!< SCB CFSR (UFSR): UNALIGNED Position */
#define SCB_CFSR_UNALIGNED_Msk            (1UL << SCB_CFSR_UNALIGNED_Pos)                 /*!< SCB CFSR (UFSR): UNALIGNED Mask */

#define SCB_CFSR_STKOF_Pos                (SCB_CFSR_USGFAULTSR_Pos + 4U)                  /*!< SCB CFSR (UFSR): STKOF Position */
#define SCB_CFSR_STKOF_Msk                (1UL << SCB_CFSR_STKOF_Pos)                     /*!< SCB CFSR (UFSR): STKOF Mask */

#define SCB_CFSR_NOCP_Pos                 (SCB_CFSR_USGFAULTSR_Pos + 3U)                  /*!< SCB CFSR (UFSR): NOCP Position */
#define SCB_CFSR_NOCP_Msk                 (1UL << SCB_CFSR_NOCP_Pos)                      /*!< SCB CFSR (UFSR): NOCP Mask */

#define SCB_CFSR_INVPC_Pos                (SCB_CFSR_USGFAULTSR_Pos + 2U)                  /*!< SCB CFSR (UFSR): INVPC Position */
#define SCB_CFSR_INVPC_Msk                (1UL << SCB_CFSR_INVPC_Pos)                     /*!< SCB CFSR (UFSR): INVPC Mask */

#define SCB_CFSR_INVSTATE_Pos             (SCB_CFSR_USGFAULTSR_Pos + 1U)                  /*!< SCB CFSR (UFSR): INVSTATE Position */
#define SCB_CFSR_INVSTATE_Msk             (1UL << SCB_CFSR_INVSTATE_Pos)                  /*!< SCB CFSR (UFSR): INVSTATE Mask */

#define SCB_CFSR_UNDEFINSTR_Pos           (SCB_CFSR_USGFAULTSR_Pos + 0U)                  /*!< SCB CFSR (UFSR): UNDEFINSTR Position */
#define SCB_CFSR_UNDEFINSTR_Msk           (1UL << SCB_CFSR_UNDEFINSTR_Pos)                /*!< SCB CFSR (UFSR): UNDEFINSTR Mask */

/* SCB Hard Fault Status Register Definitions */
#define SCB_HFSR_DEBUGEVT_Pos              31U                                            /*!< SCB HFSR: DEBUGEVT Position */
#define SCB_HFSR_DEBUGEVT_Msk              (1UL << SCB_HFSR_DEBUGEVT_Pos)                 /*!< SCB HFSR: DEBUGEVT Mask */

#define SCB_HFSR_FORCED_Pos                30U                                            /*!< SCB HFSR: FORCED Position */
#define SCB_HFSR_FORCED_Msk                (1UL << SCB_HFSR_FORCED_Pos)                   /*!< SCB HFSR: FORCED Mask */

#define SCB_HFSR_VECTTBL_Pos                1U                                            /*!< SCB HFSR: VECTTBL Position */
#define SCB_HFSR_VECTTBL_Msk               (1UL << SCB_HFSR_VECTTBL_Pos)                  /*!< SCB HFSR: VECTTBL Mask */

/* SCB Debug Fault Status Register Definitions */
#define SCB_DFSR_EXTERNAL_Pos               4U                                            /*!< SCB DFSR: EXTERNAL Position */
#define SCB_DFSR_EXTERNAL_Msk              (1UL << SCB_DFSR_EXTERNAL_Pos)                 /*!< SCB DFSR: EXTERNAL Mask */

#define SCB_DFSR_VCATCH_Pos                 3U                                            /*!< SCB DFSR: VCATCH Position */
#define SCB_DFSR_VCATCH_Msk                (1UL << SCB_DFSR_VCATCH_Pos)                   /*!< SCB DFSR: VCATCH Mask */

#define SCB_DFSR_DWTTRAP_Pos                2U                                            /*!< SCB DFSR: DWTTRAP Position */
#define SCB_DFSR_DWTTRAP_Msk               (1UL << SCB_DFSR_DWTTRAP_Pos)                  /*!< SCB DFSR: DWTTRAP Mask */

#define SCB_DFSR_BKPT_Pos                   1U                                            /*!< SCB DFSR: BKPT Position */
#define SCB_DFSR_BKPT_Msk                  (1UL << SCB_DFSR_BKPT_Pos)                     /*!< SCB DFSR: BKPT Mask */

#define SCB_DFSR_HALTED_Pos                 0U                                            /*!< SCB DFSR: HALTED Position */
#define SCB_DFSR_HALTED_Msk                (1UL /*<< SCB_DFSR_HALTED_Pos*/)               /*!< SCB DFSR: HALTED Mask */

/* SCB Non-Secure Access Control Register Definitions */
#define SCB_NSACR_CP11_Pos                 11U                                            /*!< SCB NSACR: CP11 Position */
#define SCB_NSACR_CP11_Msk                 (1UL << SCB_NSACR_CP11_Pos)                    /*!< SCB NSACR: CP11 Mask */

#define SCB_NSACR_CP10_Pos                 10U                                            /*!< SCB NSACR: CP10 Position */
#define SCB_NSACR_CP10_Msk                 (1UL << SCB_NSACR_CP10_Pos)                    /*!< SCB NSACR: CP10 Mask */

#define SCB_NSACR_CPn_Pos                   0U                                            /*!< SCB NSACR: CPn Position */
#define SCB_NSACR_CPn_Msk                  (1UL /*<< SCB_NSACR_CPn_Pos*/)                 /*!< SCB NSACR: CPn Mask */

/* SCB Cache Level ID Register Definitions */
#define SCB_CLIDR_LOUU_Pos                 27U                                            /*!< SCB CLIDR: LoUU Position */
#define SCB_CLIDR_LOUU_Msk                 (7UL << SCB_CLIDR_LOUU_Pos)                    /*!< SCB CLIDR: LoUU Mask */

#define SCB_CLIDR_LOC_Pos                  24U                                            /*!< SCB CLIDR: LoC Position */
#define SCB_CLIDR_LOC_Msk                  (7UL << SCB_CLIDR_LOC_Pos)                     /*!< SCB CLIDR: LoC Mask */

/* SCB Cache Type Register Definitions */
#define SCB_CTR_FORMAT_Pos                 29U                                            /*!< SCB CTR: Format Position */
#define SCB_CTR_FORMAT_Msk                 (7UL << SCB_CTR_FORMAT_Pos)                    /*!< SCB CTR: Format Mask */

#define SCB_CTR_CWG_Pos                    24U                                            /*!< SCB CTR: CWG Position */
#define SCB_CTR_CWG_Msk                    (0xFUL << SCB_CTR_CWG_Pos)                     /*!< SCB CTR: CWG Mask */

#define SCB_CTR_ERG_Pos                    20U                                            /*!< SCB CTR: ERG Position */
#define SCB_CTR_ERG_Msk                    (0xFUL << SCB_CTR_ERG_Pos)                     /*!< SCB CTR: ERG Mask */

#define SCB_CTR_DMINLINE_Pos               16U                                            /*!< SCB CTR: DminLine Position */
#define SCB_CTR_DMINLINE_Msk               (0xFUL << SCB_CTR_DMINLINE_Pos)                /*!< SCB CTR: DminLine Mask */

#define SCB_CTR_IMINLINE_Pos                0U                                            /*!< SCB CTR: ImInLine Position */
#define SCB_CTR_IMINLINE_Msk               (0xFUL /*<< SCB_CTR_IMINLINE_Pos*/)            /*!< SCB CTR: ImInLine Mask */

/* SCB Cache Size ID Register Definitions */
#define SCB_CCSIDR_WT_Pos                  31U                                            /*!< SCB CCSIDR: WT Position */
#define SCB_CCSIDR_WT_Msk                  (1UL << SCB_CCSIDR_WT_Pos)                     /*!< SCB CCSIDR: WT Mask */

#define SCB_CCSIDR_WB_Pos                  30U                                            /*!< SCB CCSIDR: WB Position */
#define SCB_CCSIDR_WB_Msk                  (1UL << SCB_CCSIDR_WB_Pos)                     /*!< SCB CCSIDR: WB Mask */

#define SCB_CCSIDR_RA_Pos                  29U                                            /*!< SCB CCSIDR: RA Position */
#define SCB_CCSIDR_RA_Msk                  (1UL << SCB_CCSIDR_RA_Pos)                     /*!< SCB CCSIDR: RA Mask */

#define SCB_CCSIDR_WA_Pos                  28U                                            /*!< SCB CCSIDR: WA Position */
#define SCB_CCSIDR_WA_Msk                  (1UL << SCB_CCSIDR_WA_Pos)                     /*!< SCB CCSIDR: WA Mask */

#define SCB_CCSIDR_NUMSETS_Pos             13U                                            /*!< SCB CCSIDR: NumSets Position */
#define SCB_CCSIDR_NUMSETS_Msk             (0x7FFFUL << SCB_CCSIDR_NUMSETS_Pos)           /*!< SCB CCSIDR: NumSets Mask */

#define SCB_CCSIDR_ASSOCIATIVITY_Pos        3U                                            /*!< SCB CCSIDR: Associativity Position */
#define SCB_CCSIDR_ASSOCIATIVITY_Msk       (0x3FFUL << SCB_CCSIDR_ASSOCIATIVITY_Pos)      /*!< SCB CCSIDR: Associativity Mask */

#define SCB_CCSIDR_LINESIZE_Pos             0U                                            /*!< SCB CCSIDR: LineSize Position */
#define SCB_CCSIDR_LINESIZE_Msk            (7UL /*<< SCB_CCSIDR_LINESIZE_Pos*/)           /*!< SCB CCSIDR: LineSize Mask */

/* SCB Cache Size Selection Register Definitions */
#define SCB_CSSELR_LEVEL_Pos                1U                                            /*!< SCB CSSELR: Level Position */
#define SCB_CSSELR_LEVEL_Msk               (7UL << SCB_CSSELR_LEVEL_Pos)                  /*!< SCB CSSELR: Level Mask */

#define SCB_CSSELR_IND_Pos                  0U                                            /*!< SCB CSSELR: InD Position */
#define SCB_CSSELR_IND_Msk                 (1UL /*<< SCB_CSSELR_IND_Pos*/)                /*!< SCB CSSELR: InD Mask */

/* SCB Software Triggered Interrupt Register Definitions */
#define SCB_STIR_INTID_Pos                  0U                                            /*!< SCB STIR: INTID Position */
#define SCB_STIR_INTID_Msk                 (0x1FFUL /*<< SCB_STIR_INTID_Pos*/)            /*!< SCB STIR: INTID Mask */

/* SCB D-Cache Invalidate by Set-way Register Definitions */
#define SCB_DCISW_WAY_Pos                  30U                                            /*!< SCB DCISW: Way Position */
#define SCB_DCISW_WAY_Msk                  (3UL << SCB_DCISW_WAY_Pos)                     /*!< SCB DCISW: Way Mask */

#define SCB_DCISW_SET_Pos                   5U                                            /*!< SCB DCISW: Set Position */
#define SCB_DCISW_SET_Msk                  (0x1FFUL << SCB_DCISW_SET_Pos)                 /*!< SCB DCISW: Set Mask */

/* SCB D-Cache Clean by Set-way Register Definitions */
#define SCB_DCCSW_WAY_Pos                  30U                                            /*!< SCB DCCSW: Way Position */
#define SCB_DCCSW_WAY_Msk                  (3UL << SCB_DCCSW_WAY_Pos)                     /*!< SCB DCCSW: Way Mask */

#define SCB_DCCSW_SET_Pos                   5U                                            /*!< SCB DCCSW: Set Position */
#define SCB_DCCSW_SET_Msk                  (0x1FFUL << SCB_DCCSW_SET_Pos)                 /*!< SCB DCCSW: Set Mask */

/* SCB D-Cache Clean and Invalidate by Set-way Register Definitions */
#define SCB_DCCISW_WAY_Pos                 30U                                            /*!< SCB DCCISW: Way Position */
#define SCB_DCCISW_WAY_Msk                 (3UL << SCB_DCCISW_WAY_Pos)                    /*!< SCB DCCISW: Way Mask */

#define SCB_DCCISW_SET_Pos                  5U                                            /*!< SCB DCCISW: Set Position */
#define SCB_DCCISW_SET_Msk                 (0x1FFUL << SCB_DCCISW_SET_Pos)                /*!< SCB DCCISW: Set Mask */

/*@} end of group CMSIS_SCB */


/**
  \ingroup  CMSIS_core_register
  \defgroup CMSIS_SCnSCB System Controls not in SCB (SCnSCB)
  \brief    Type definitions for the System Control and ID Register not in the SCB
  @{
 */

/**
  \brief  Structure type to access the System Control and ID Register not in the SCB.
 */
typedef struct
{
        uint32_t RESERVED0[1U];
  __IM  uint32_t ICTR;                   /*!< Offset: 0x004 (R/ )  Interrupt Controller Type Register */
  __IOM uint32_t ACTLR;                  /*!< Offset: 0x008 (R/W)  Auxiliary Control Register */
  __IOM uint32_t CPPWR;                  /*!< Offset: 0x00C (R/W)  Coprocessor Power Control  Register */
} SCnSCB_Type;

/* Interrupt Controller Type Register Definitions */
#define SCnSCB_ICTR_INTLINESNUM_Pos         0U                                         /*!< ICTR: INTLINESNUM Position */
#define SCnSCB_ICTR_INTLINESNUM_Msk        (0xFUL /*<< SCnSCB_ICTR_INTLINESNUM_Pos*/)  /*!< ICTR: INTLINESNUM Mask */

/*@} end of group CMSIS_SCnotSCB */


/**
  \ingroup  CMSIS_core_register
  \defgroup CMSIS_SysTick     System Tick Timer (SysTick)
  \brief    Type definitions for the System Timer Registers.
  @{
 */

/**
  \brief  Structure type to access the System Timer (SysTick).
 */
typedef struct
{
  __IOM uint32_t CTRL;                   /*!< Offset: 0x000 (R/W)  SysTick Control and Status Register */
  __IOM uint32_t LOAD;                   /*!< Offset: 0x004 (R/W)  SysTick Reload Value Register */
  __IOM uint32_t VAL;                    /*!< Offset: 0x008 (R/W)  SysTick Current Value Register */
  __IM  uint32_t CALIB;                  /*!< Offset: 0x00C (R/ )  SysTick Calibration Register */
} SysTick_Type;

/* SysTick Control / Status Register Definitions */
#define SysTick_CTRL_COUNTFLAG_Pos         16U                                            /*!< SysTick CTRL: COUNTFLAG Position */
#define SysTick_CTRL_COUNTFLAG_Msk         (1UL << SysTick_CTRL_COUNTFLAG_Pos)            /*!< SysTick CTRL: COUNTFLAG Mask */

#define SysTick_CTRL_CLKSOURCE_Pos          2U                                            /*!< SysTick CTRL: CLKSOURCE Position */
#define SysTick_CTRL_CLKSOURCE_Msk         (1UL << SysTick_CTRL_CLKSOURCE_Pos)            /*!< SysTick CTRL: CLKSOURCE Mask */

#define SysTick_CTRL_TICKINT_Pos            1U                                            /*!< SysTick CTRL: TICKINT Position */
#define SysTick_CTRL_TICKINT_Msk           (1UL << SysTick_CTRL_TICKINT_Pos)              /*!< SysTick CTRL: TICKINT Mask */

#define SysTick_CTRL_ENABLE_Pos             0U                                            /*!< SysTick CTRL: ENABLE Position */
#define SysTick_CTRL_ENABLE_Msk            (1UL /*<< SysTick_CTRL_ENABLE_Pos*/)           /*!< SysTick CTRL: ENABLE Mask */

/* SysTick Reload Register Definitions */
#define SysTick_LOAD_RELOAD_Pos             0U                                            /*!< SysTick LOAD: RELOAD Position */
#define SysTick_LOAD_RELOAD_Msk            (0xFFFFFFUL /*<< SysTick_LOAD_RELOAD_Pos*/)    /*!< SysTick LOAD: RELOAD Mask */

/* SysTick Current Register Definitions */
#define SysTick_VAL_CURRENT_Pos             0U                                            /*!< SysTick VAL: CURRENT Position */
#define SysTick_VAL_CURRENT_Msk            (0xFFFFFFUL /*<< SysTick_VAL_CURRENT_Pos*/)    /*!< SysTick VAL: CURRENT Mask */

/* SysTick Calibration Register Definitions */
#define SysTick_CALIB_NOREF_Pos            31U                                            /*!< SysTick CALIB: NOREF Position */
#define SysTick_CALIB_NOREF_Msk            (1UL << SysTick_CALIB_NOREF_Pos)               /*!< SysTick CALIB: NOREF Mask */

#define SysTick_CALIB_SKEW_Pos             30U                                            /*!< SysTick CALIB: SKEW Position */
#define SysTick_CALIB_SKEW_Msk             (1UL << SysTick_CALIB_SKEW_Pos)                /*!< SysTick CALIB: SKEW Mask */

#define SysTick_CALIB_TENMS_Pos             0U                                            /*!< SysTick CALIB: TENMS Position */
#define SysTick_CALIB_TENMS_Msk            (0xFFFFFFUL /*<< SysTick_CALIB_TENMS_Pos*/)    /*!< SysTick CALIB: TENMS Mask */

/*@} end of group CMSIS_SysTick */


/**
  \ingroup  CMSIS_core_register
  \defgroup CMSIS_ITM     Instrumentation Trace Macrocell (ITM)
  \brief    Type definitions for the Instrumentation Trace Macrocell (ITM)
  @{
 */

/**
  \brief  Structure type to access the Instrumentation Trace Macrocell Register (ITM).
 */
typedef struct
{
  __OM  union
  {
    __OM  uint8_t    u8;                 /*!< Offset: 0x000 ( /W)  ITM Stimulus Port 8-bit */
    __OM  uint16_t   u16;                /*!< Offset: 0x000 ( /W)  ITM Stimulus Port 16-bit */
    __OM  uint32_t   u32;                /*!< Offset: 0x000 ( /W)  ITM Stimulus Port 32-bit */
  }  PORT [32U];                         /*!< Offset: 0x000 ( /W)  ITM Stimulus Port Registers */
        uint32_t RESERVED0[864U];
  __IOM uint32_t TER;                    /*!< Offset: 0xE00 (R/W)  ITM Trace Enable Register */
        uint32_t RESERVED1[15U];
  __IOM uint32_t TPR;                    /*!< Offset: 0xE40 (R/W)  ITM Trace Privilege Register */
        uint32_t RESERVED2[15U];
  __IOM uint32_t TCR;                    /*!< Offset: 0xE80 (R/W)  ITM Trace Control Register */
        uint32_t RESERVED3[32U];
        uint32_t RESERVED4[43U];
  __OM  uint32_t LAR;                    /*!< Offset: 0xFB0 ( /W)  ITM Lock Access Register */
  __IM  uint32_t LSR;                    /*!< Offset: 0xFB4 (R/ )  ITM Lock Status Register */
        uint32_t RESERVED5[1U];
  __IM  uint32_t DEVARCH;                /*!< Offset: 0xFBC (R/ )  ITM Device Architecture Register */
        uint32_t RESERVED6[4U];
  __IM  uint32_t PID4;                   /*!< Offset: 0xFD0 (R/ )  ITM Peripheral Identification Register #4 */
  __IM  uint32_t PID5;                   /*!< Offset: 0xFD4 (R/ )  ITM Peripheral Identification Register #5 */
  __IM  uint32_t PID6;                   /*!< Offset: 0xFD8 (R/ )  ITM Peripheral Identification Register #6 */
  __IM  uint32_t PID7;                   /*!< Offset: 0xFDC (R/ )  ITM Peripheral Identification Register #7 */
  __IM  uint32_t PID0;                   /*!< Offset: 0xFE0 (R/ )  ITM Peripheral Identification Register #0 */
  __IM  uint32_t PID1;                   /*!< Offset: 0xFE4 (R/ )  ITM Peripheral Identification Register #1 */
  __IM  uint32_t PID2;                   /*!< Offset: 0xFE8 (R/ )  ITM Peripheral Identification Register #2 */
  __IM  uint32_t PID3;                   /*!< Offset: 0xFEC (R/ )  ITM Peripheral Identification Register #3 */
  __IM  uint32_t CID0;                   /*!< Offset: 0xFF0 (R/ )  ITM Component  Identification Register #0 */
  __IM  uint32_t CID1;                   /*!< Offset: 0xFF4 (R/ )  ITM Component  Identification Register #1 */
  __IM  uint32_t CID2;                   /*!< Offset: 0xFF8 (R/ )  ITM Component  Identification Register #2 */
  __IM  uint32_t CID3;                   /*!< Offset: 0xFFC (R/ )  ITM Component  Identification Register #3 */
} ITM_Type;

/* ITM Stimulus Port Register Definitions */
#define ITM_STIM_DISABLED_Pos               1U                                            /*!< ITM STIM: DISABLED Position */
#define ITM_STIM_DISABLED_Msk              (0x1UL << ITM_STIM_DISABLED_Pos)               /*!< ITM STIM: DISABLED Mask */

#define ITM_STIM_FIFOREADY_Pos              0U                                            /*!< ITM STIM: FIFOREADY Position */
#define ITM_STIM_FIFOREADY_Msk             (0x1UL /*<< ITM_STIM_FIFOREADY_Pos*/)          /*!< ITM STIM: FIFOREADY Mask */

/* ITM Trace Privilege Register Definitions */
#define ITM_TPR_PRIVMASK_Pos                0U                                            /*!< ITM TPR: PRIVMASK Position */
#define ITM_TPR_PRIVMASK_Msk               (0xFFFFFFFFUL /*<< ITM_TPR_PRIVMASK_Pos*/)     /*!< ITM TPR: PRIVMASK Mask */

/* ITM Trace Control Register Definitions */
#define ITM_TCR_BUSY_Pos                   23U                                            /*!< ITM TCR: BUSY Position */
#define ITM_TCR_BUSY_Msk                   (1UL << ITM_TCR_BUSY_Pos)                      /*!< ITM TCR: BUSY Mask */

#define ITM_TCR_TRACEBUSID_Pos             16U                                            /*!< ITM TCR: ATBID Position */
#define ITM_TCR_TRACEBUSID_Msk             (0x7FUL << ITM_TCR_TRACEBUSID_Pos)             /*!< ITM TCR: ATBID Mask */

#define ITM_TCR_GTSFREQ_Pos                10U                                            /*!< ITM TCR: Global timestamp frequency Position */
#define ITM_TCR_GTSFREQ_Msk                (3UL << ITM_TCR_GTSFREQ_Pos)                   /*!< ITM TCR: Global timestamp frequency Mask */

#define ITM_TCR_TSPRESCALE_Pos              8U                                            /*!< ITM TCR: TSPRESCALE Position */
#define ITM_TCR_TSPRESCALE_Msk             (3UL << ITM_TCR_TSPRESCALE_Pos)                /*!< ITM TCR: TSPRESCALE Mask */

#define ITM_TCR_STALLENA_Pos                5U                                            /*!< ITM TCR: STALLENA Position */
#define ITM_TCR_STALLENA_Msk               (1UL << ITM_TCR_STALLENA_Pos)                  /*!< ITM TCR: STALLENA Mask */

#define ITM_TCR_SWOENA_Pos                  4U                                            /*!< ITM TCR: SWOENA Position */
#define ITM_TCR_SWOENA_Msk                 (1UL << ITM_TCR_SWOENA_Pos)                    /*!< ITM TCR: SWOENA Mask */

#define ITM_TCR_DWTENA_Pos                  3U                                            /*!< ITM TCR: DWTENA Position */
#define ITM_TCR_DWTENA_Msk                 (1UL << ITM_TCR_DWTENA_Pos)                    /*!< ITM TCR: DWTENA Mask */

#define ITM_TCR_SYNCENA_Pos                 2U                                            /*!< ITM TCR: SYNCENA Position */
#define ITM_TCR_SYNCENA_Msk                (1UL << ITM_TCR_SYNCENA_Pos)                   /*!< ITM TCR: SYNCENA Mask */

#define ITM_TCR_TSENA_Pos                   1U                                            /*!< ITM TCR: TSENA Position */
#define ITM_TCR_TSENA_Msk                  (1UL << ITM_TCR_TSENA_Pos)                     /*!< ITM TCR: TSENA Mask */

#define ITM_TCR_ITMENA_Pos                  0U                                            /*!< ITM TCR: ITM Enable bit Position */
#define ITM_TCR_ITMENA_Msk                 (1UL /*<< ITM_TCR_ITMENA_Pos*/)                /*!< ITM TCR: ITM Enable bit Mask */

/* ITM Lock Status Register Definitions */
#define ITM_LSR_ByteAcc_Pos                 2U                                            /*!< ITM LSR: ByteAcc Position */
#define ITM_LSR_ByteAcc_Msk                (1UL << ITM_LSR_ByteAcc_Pos)                   /*!< ITM LSR: ByteAcc Mask */

#define ITM_LSR_Access_Pos                  1U                                            /*!< ITM LSR: Access Position */
#define ITM_LSR_Access_Msk                 (1UL << ITM_LSR_Access_Pos)                    /*!< ITM LSR: Access Mask */

#define ITM_LSR_Present_Pos                 0U                                            /*!< ITM LSR: Present Position */
#define ITM_LSR_Present_Msk                (1UL /*<< ITM_LSR_Present_Pos*/)               /*!< ITM LSR: Present Mask */

/*@}*/ /* end of group CMSIS_ITM */


/**
  \ingroup  CMSIS_core_register
  \defgroup CMSIS_DWT     Data Watchpoint and Trace (DWT)
  \brief    Type definitions for the Data Watchpoint and Trace (DWT)
  @{
 */

/**
  \brief  Structure type to access the Data Watchpoint and Trace Register (DWT).
 */
typedef struct
{
  __IOM uint32_t CTRL;                   /*!< Offset: 0x000 (R/W)  Control Register */
  __IOM uint32_t CYCCNT;                 /*!< Offset: 0x004 (R/W)  Cycle Count Register */
  __IOM uint32_t CPICNT;                 /*!< Offset: 0x008 (R/W)  CPI Count Register */
  __IOM uint32_t EXCCNT;                 /*!< Offset: 0x00C (R/W)  Exception Overhead Count Register */
  __IOM uint32_t SLEEPCNT;               /*!< Offset: 0x010 (R/W)  Sleep Count Register */
  __IOM uint32_t LSUCNT;                 /*!< Offset: 0x014 (R/W)  LSU Count Register */
  __IOM uint32_t FOLDCNT;                /*!< Offset: 0x018 (R/W)  Folded-instruction Count Register */
  __IM  uint32_t PCSR;                   /*!< Offset: 0x01C (R/ )  Program Counter Sample Register */
  __IOM uint32_t COMP0;                  /*!< Offset: 0x020 (R/W)  Comparator Register 0 */
        uint32_t RESERVED1[1U];
  __IOM uint32_t FUNCTION0;              /*!< Offset: 0x028 (R/W)  Function Register 0 */
        uint32_t RESERVED2[1U];
  __IOM uint32_t COMP1;                  /*!< Offset: 0x030 (R/W)  Comparator Register 1 */
        uint32_t RESERVED3[1U];
  __IOM uint32_t FUNCTION1;              /*!< Offset: 0x038 (R/W)  Function Register 1 */
        uint32_t RESERVED4[1U];
  __IOM uint32_t COMP2;                  /*!< Offset: 0x040 (R/W)  Comparator Register 2 */
        uint32_t RESERVED5[1U];
  __IOM uint32_t FUNCTION2;              /*!< Offset: 0x048 (R/W)  Function Register 2 */
        uint32_t RESERVED6[1U];
  __IOM uint32_t COMP3;                  /*!< Offset: 0x050 (R/W)  Comparator Register 3 */
        uint32_t RESERVED7[1U];
  __IOM uint32_t FUNCTION3;              /*!< Offset: 0x058 (R/W)  Function Register 3 */
        uint32_t RESERVED8[1U];
  __IOM uint32_t COMP4;                  /*!< Offset: 0x060 (R/W)  Comparator Register 4 */
        uint32_t RESERVED9[1U];
  __IOM uint32_t FUNCTION4;              /*!< Offset: 0x068 (R/W)  Function Register 4 */
        uint32_t RESERVED10[1U];
  __IOM uint32_t COMP5;                  /*!< Offset: 0x070 (R/W)  Comparator Register 5 */
        uint32_t RESERVED11[1U];
  __IOM uint32_t FUNCTION5;              /*!< Offset: 0x078 (R/W)  Function Register 5 */
        uint32_t RESERVED12[1U];
  __IOM uint32_t COMP6;                  /*!< Offset: 0x080 (R/W)  Comparator Register 6 */
        uint32_t RESERVED13[1U];
  __IOM uint32_t FUNCTION6;              /*!< Offset: 0x088 (R/W)  Function Register 6 */
        uint32_t RESERVED14[1U];
  __IOM uint32_t COMP7;                  /*!< Offset: 0x090 (R/W)  Comparator Register 7 */
        uint32_t RESERVED15[1U];
  __IOM uint32_t FUNCTION7;              /*!< Offset: 0x098 (R/W)  Function Register 7 */
        uint32_t RESERVED16[1U];
  __IOM uint32_t COMP8;                  /*!< Offset: 0x0A0 (R/W)  Comparator Register 8 */
        uint32_t RESERVED17[1U];
  __IOM uint32_t FUNCTION8;              /*!< Offset: 0x0A8 (R/W)  Function Register 8 */
        uint32_t RESERVED18[1U];
  __IOM uint32_t COMP9;                  /*!< Offset: 0x0B0 (R/W)  Comparator Register 9 */
        uint32_t RESERVED19[1U];
  __IOM uint32_t FUNCTION9;              /*!< Offset: 0x0B8 (R/W)  Function Register 9 */
        uint32_t RESERVED20[1U];
  __IOM uint32_t COMP10;                 /*!< Offset: 0x0C0 (R/W)  Comparator Register 10 */
        uint32_t RESERVED21[1U];
  __IOM uint32_t FUNCTION10;             /*!< Offset: 0x0C8 (R/W)  Function Register 10 */
        uint32_t RESERVED22[1U];
  __IOM uint32_t COMP11;                 /*!< Offset: 0x0D0 (R/W)  Comparator Register 11 */
        uint32_t RESERVED23[1U];
  __IOM uint32_t FUNCTION11;             /*!< Offset: 0x0D8 (R/W)  Function Register 11 */
        uint32_t RESERVED24[1U];
  __IOM uint32_t COMP12;                 /*!< Offset: 0x0E0 (R/W)  Comparator Register 12 */
        uint32_t RESERVED25[1U];
  __IOM uint32_t FUNCTION12;             /*!< Offset: 0x0E8 (R/W)  Function Register 12 */
        uint32_t RESERVED26[1U];
  __IOM uint32_t COMP13;                 /*!< Offset: 0x0F0 (R/W)  Comparator Register 13 */
        uint32_t RESERVED27[1U];
  __IOM uint32_t FUNCTION13;             /*!< Offset: 0x0F8 (R/W)  Function Register 13 */
        uint32_t RESERVED28[1U];
  __IOM uint32_t COMP14;                 /*!< Offset: 0x100 (R/W)  Comparator Register 14 */
        uint32_t RESERVED29[1U];
  __IOM uint32_t FUNCTION14;             /*!< Offset: 0x108 (R/W)  Function Register 14 */
        uint32_t RESERVED30[1U];
  __IOM uint32_t COMP15;                 /*!< Offset: 0x110 (R/W)  Comparator Register 15 */
        uint32_t RESERVED31[1U];
  __IOM uint32_t FUNCTION15;             /*!< Offset: 0x118 (R/W)  Function Register 15 */
        uint32_t RESERVED32[934U];
  __IM  uint32_t LSR;                    /*!< Offset: 0xFB4 (R  )  Lock Status Register */
        uint32_t RESERVED33[1U];
  __IM  uint32_t DEVARCH;                /*!< Offset: 0xFBC (R/ )  Device Architecture Register */
} DWT_Type;

/* DWT Control Register Definitions */
#define DWT_CTRL_NUMCOMP_Pos               28U                                         /*!< DWT CTRL: NUMCOMP Position */
#define DWT_CTRL_NUMCOMP_Msk               (0xFUL << DWT_CTRL_NUMCOMP_Pos)             /*!< DWT CTRL: NUMCOMP Mask */

#define DWT_CTRL_NOTRCPKT_Pos              27U                                         /*!< DWT CTRL: NOTRCPKT Position */
#define DWT_CTRL_NOTRCPKT_Msk              (0x1UL << DWT_CTRL_NOTRCPKT_Pos)            /*!< DWT CTRL: NOTRCPKT Mask */

#define DWT_CTRL_NOEXTTRIG_Pos             26U                                         /*!< DWT CTRL: NOEXTTRIG Position */
#define DWT_CTRL_NOEXTTRIG_Msk             (0x1UL << DWT_CTRL_NOEXTTRIG_Pos)           /*!< DWT CTRL: NOEXTTRIG Mask */

#define DWT_CTRL_NOCYCCNT_Pos              25U                                         /*!< DWT CTRL: NOCYCCNT Position */
#define DWT_CTRL_NOCYCCNT_Msk              (0x1UL << DWT_CTRL_NOCYCCNT_Pos)            /*!< DWT CTRL: NOCYCCNT Mask */

#define DWT_CTRL_NOPRFCNT_Pos              24U                                         /*!< DWT CTRL: NOPRFCNT Position */
#define DWT_CTRL_NOPRFCNT_Msk              (0x1UL << DWT_CTRL_NOPRFCNT_Pos)            /*!< DWT CTRL: NOPRFCNT Mask */

#define DWT_CTRL_CYCDISS_Pos               23U                                         /*!< DWT CTRL: CYCDISS Position */
#define DWT_CTRL_CYCDISS_Msk               (0x1UL << DWT_CTRL_CYCDISS_Pos)             /*!< DWT CTRL: CYCDISS Mask */

#define DWT_CTRL_CYCEVTENA_Pos             22U                                         /*!< DWT CTRL: CYCEVTENA Position */
#define DWT_CTRL_CYCEVTENA_Msk             (0x1UL << DWT_CTRL_CYCEVTENA_Pos)           /*!< DWT CTRL: CYCEVTENA Mask */

#define DWT_CTRL_FOLDEVTENA_Pos            21U                                         /*!< DWT CTRL: FOLDEVTENA Position */
#define DWT_CTRL_FOLDEVTENA_Msk            (0x1UL << DWT_CTRL_FOLDEVTENA_Pos)          /*!< DWT CTRL: FOLDEVTENA Mask */

#define DWT_CTRL_LSUEVTENA_Pos             20U                                         /*!< DWT CTRL: LSUEVTENA Position */
#define DWT_CTRL_LSUEVTENA_Msk             (0x1UL << DWT_CTRL_LSUEVTENA_Pos)           /*!< DWT CTRL: LSUEVTENA Mask */

#define DWT_CTRL_SLEEPEVTENA_Pos           19U                                         /*!< DWT CTRL: SLEEPEVTENA Position */
#define DWT_CTRL_SLEEPEVTENA_Msk           (0x1UL << DWT_CTRL_SLEEPEVTENA_Pos)         /*!< DWT CTRL: SLEEPEVTENA Mask */

#define DWT_CTRL_EXCEVTENA_Pos             18U                                         /*!< DWT CTRL: EXCEVTENA Position */
#define DWT_CTRL_EXCEVTENA_Msk             (0x1UL << DWT_CTRL_EXCEVTENA_Pos)           /*!< DWT CTRL: EXCEVTENA Mask */

#define DWT_CTRL_CPIEVTENA_Pos             17U                                         /*!< DWT CTRL: CPIEVTENA Position */
#define DWT_CTRL_CPIEVTENA_Msk             (0x1UL << DWT_CTRL_CPIEVTENA_Pos)           /*!< DWT CTRL: CPIEVTENA Mask */

#define DWT_CTRL_EXCTRCENA_Pos             16U                                         /*!< DWT CTRL: EXCTRCENA Position */
#define DWT_CTRL_EXCTRCENA_Msk             (0x1UL << DWT_CTRL_EXCTRCENA_Pos)           /*!< DWT CTRL: EXCTRCENA Mask */

#define DWT_CTRL_PCSAMPLENA_Pos            12U                                         /*!< DWT CTRL: PCSAMPLENA Position */
#define DWT_CTRL_PCSAMPLENA_Msk            (0x1UL << DWT_CTRL_PCSAMPLENA_Pos)          /*!< DWT CTRL: PCSAMPLENA Mask */

#define DWT_CTRL_SYNCTAP_Pos               10U                                         /*!< DWT CTRL: SYNCTAP Position */
#define DWT_CTRL_SYNCTAP_Msk               (0x3UL << DWT_CTRL_SYNCTAP_Pos)             /*!< DWT CTRL: SYNCTAP Mask */

#define DWT_CTRL_CYCTAP_Pos                 9U                                         /*!< DWT CTRL: CYCTAP Position */
#define DWT_CTRL_CYCTAP_Msk                (0x1UL << DWT_CTRL_CYCTAP_Pos)              /*!< DWT CTRL: CYCTAP Mask */

#define DWT_CTRL_POSTINIT_Pos               5U                                         /*!< DWT CTRL: POSTINIT Position */
#define DWT_CTRL_POSTINIT_Msk              (0xFUL << DWT_CTRL_POSTINIT_Pos)            /*!< DWT CTRL: POSTINIT Mask */

#define DWT_CTRL_POSTPRESET_Pos             1U                                         /*!< DWT CTRL: POSTPRESET Position */
#define DWT_CTRL_POSTPRESET_Msk            (0xFUL << DWT_CTRL_POSTPRESET_Pos)          /*!< DWT CTRL: POSTPRESET Mask */

#define DWT_CTRL_CYCCNTENA_Pos              0U                                         /*!< DWT CTRL: CYCCNTENA Position */
#define DWT_CTRL_CYCCNTENA_Msk             (0x1UL /*<< DWT_CTRL_CYCCNTENA_Pos*/)       /*!< DWT CTRL: CYCCNTENA Mask */

/* DWT CPI Count Register Definitions */
#define DWT_CPICNT_CPICNT_Pos               0U                                         /*!< DWT CPICNT: CPICNT Position */
#define DWT_CPICNT_CPICNT_Msk              (0xFFUL /*<< DWT_CPICNT_CPICNT_Pos*/)       /*!< DWT CPICNT: CPICNT Mask */

/* DWT Exception Overhead Count Register Definitions */
#define DWT_EXCCNT_EXCCNT_Pos               0U                                         /*!< DWT EXCCNT: EXCCNT Position */
#define DWT_EXCCNT_EXCCNT_Msk              (0xFFUL /*<< DWT_EXCCNT_EXCCNT_Pos*/)       /*!< DWT EXCCNT: EXCCNT Mask */

/* DWT Sleep Count Register Definitions */
#define DWT_SLEEPCNT_SLEEPCNT_Pos           0U                                         /*!< DWT SLEEPCNT: SLEEPCNT Position */
#define DWT_SLEEPCNT_SLEEPCNT_Msk          (0xFFUL /*<< DWT_SLEEPCNT_SLEEPCNT_Pos*/)   /*!< DWT SLEEPCNT: SLEEPCNT Mask */

/* DWT LSU Count Register Definitions */
#define DWT_LSUCNT_LSUCNT_Pos               0U                                         /*!< DWT LSUCNT: LSUCNT Position */
#define DWT_LSUCNT_LSUCNT_Msk              (0xFFUL /*<< DWT_LSUCNT_LSUCNT_Pos*/)       /*!< DWT LSUCNT: LSUCNT Mask */

/* DWT Folded-instruction Count Register Definitions */
#define DWT_FOLDCNT_FOLDCNT_Pos             0U                                         /*!< DWT FOLDCNT: FOLDCNT Position */
#define DWT_FOLDCNT_FOLDCNT_Msk            (0xFFUL /*<< DWT_FOLDCNT_FOLDCNT_Pos*/)     /*!< DWT FOLDCNT: FOLDCNT Mask */

/* DWT Comparator Function Register Definitions */
#define DWT_FUNCTION_ID_Pos                27U                                         /*!< DWT FUNCTION: ID Position */
#define DWT_FUNCTION_ID_Msk                (0x1FUL << DWT_FUNCTION_ID_Pos)             /*!< DWT FUNCTION: ID Mask */

#define DWT_FUNCTION_MATCHED_Pos           24U                                         /*!< DWT FUNCTION: MATCHED Position */
#define DWT_FUNCTION_MATCHED_Msk           (0x1UL << DWT_FUNCTION_MATCHED_Pos)         /*!< DWT FUNCTION: MATCHED Mask */

#define DWT_FUNCTION_DATAVSIZE_Pos         10U                                         /*!< DWT FUNCTION: DATAVSIZE Position */
#define DWT_FUNCTION_DATAVSIZE_Msk         (0x3UL << DWT_FUNCTION_DATAVSIZE_Pos)       /*!< DWT FUNCTION: DATAVSIZE Mask */

#define DWT_FUNCTION_ACTION_Pos             4U                                         /*!< DWT FUNCTION: ACTION Position */
#define DWT_FUNCTION_ACTION_Msk            (0x1UL << DWT_FUNCTION_ACTION_Pos)          /*!< DWT FUNCTION: ACTION Mask */

#define DWT_FUNCTION_MATCH_Pos              0U                                         /*!< DWT FUNCTION: MATCH Position */
#define DWT_FUNCTION_MATCH_Msk             (0xFUL /*<< DWT_FUNCTION_MATCH_Pos*/)       /*!< DWT FUNCTION: MATCH Mask */

/*@}*/ /* end of group CMSIS_DWT */


/**
  \ingroup  CMSIS_core_register
  \defgroup CMSIS_TPI     Trace Port Interface (TPI)
  \brief    Type definitions for the Trace Port Interface (TPI)
  @{
 */

/**
  \brief  Structure type to access the Trace Port Interface Register (TPI).
 */
typedef struct
{
  __IM  uint32_t SSPSR;                  /*!< Offset: 0x000 (R/ )  Supported Parallel Port Size Register */
  __IOM uint32_t CSPSR;                  /*!< Offset: 0x004 (R/W)  Current Parallel Port Size Register */
        uint32_t RESERVED0[2U];
  __IOM uint32_t ACPR;                   /*!< Offset: 0x010 (R/W)  Asynchronous Clock Prescaler Register */
        uint32_t RESERVED1[55U];
  __IOM uint32_t SPPR;                   /*!< Offset: 0x0F0 (R/W)  Selected Pin Protocol Register */
        uint32_t RESERVED2[131U];
  __IM  uint32_t FFSR;                   /*!< Offset: 0x300 (R/ )  Formatter and Flush Status Register */
  __IOM uint32_t FFCR;                   /*!< Offset: 0x304 (R/W)  Formatter and Flush Control Register */
  __IOM uint32_t PSCR;                   /*!< Offset: 0x308 (R/W)  Periodic Synchronization Control Register */
        uint32_t RESERVED3[759U];
  __IM  uint32_t TRIGGER;                /*!< Offset: 0xEE8 (R/ )  TRIGGER Register */
  __IM  uint32_t ITFTTD0;                /*!< Offset: 0xEEC (R/ )  Integration Test FIFO Test Data 0 Register */
  __IOM uint32_t ITATBCTR2;              /*!< Offset: 0xEF0 (R/W)  Integration Test ATB Control Register 2 */
        uint32_t RESERVED4[1U];
  __IM  uint32_t ITATBCTR0;              /*!< Offset: 0xEF8 (R/ )  Integration Test ATB Control Register 0 */
  __IM  uint32_t ITFTTD1;                /*!< Offset: 0xEFC (R/ )  Integration Test FIFO Test Data 1 Register */
  __IOM uint32_t ITCTRL;                 /*!< Offset: 0xF00 (R/W)  Integration Mode Control */
        uint32_t RESERVED5[39U];
  __IOM uint32_t CLAIMSET;               /*!< Offset: 0xFA0 (R/W)  Claim tag set */
  __IOM uint32_t CLAIMCLR;               /*!< Offset: 0xFA4 (R/W)  Claim tag clear */
        uint32_t RESERVED7[8U];
  __IM  uint32_t DEVID;                  /*!< Offset: 0xFC8 (R/ )  Device Configuration Register */
  __IM  uint32_t DEVTYPE;                /*!< Offset: 0xFCC (R/ )  Device Type Identifier Register */
} TPI_Type;

/* TPI Asynchronous Clock Prescaler Register Definitions */
#define TPI_ACPR_PRESCALER_Pos              0U                                         /*!< TPI ACPR: PRESCALER Position */
#define TPI_ACPR_PRESCALER_Msk             (0x1FFFUL /*<< TPI_ACPR_PRESCALER_Pos*/)    /*!< TPI ACPR: PRESCALER Mask */

/* TPI Selected Pin Protocol Register Definitions */
#define TPI_SPPR_TXMODE_Pos                 0U                                         /*!< TPI SPPR: TXMODE Position */
#define TPI_SPPR_TXMODE_Msk                (0x3UL /*<< TPI_SPPR_TXMODE_Pos*/)          /*!< TPI SPPR: TXMODE Mask */

/* TPI Formatter and Flush Status Register Definitions */
#define TPI_FFSR_FtNonStop_Pos              3U                                         /*!< TPI FFSR: FtNonStop Position */
#define TPI_FFSR_FtNonStop_Msk             (0x1UL << TPI_FFSR_FtNonStop_Pos)           /*!< TPI FFSR: FtNonStop Mask */

#define TPI_FFSR_TCPresent_Pos              2U                                         /*!< TPI FFSR: TCPresent Position */
#define TPI_FFSR_TCPresent_Msk             (0x1UL << TPI_FFSR_TCPresent_Pos)           /*!< TPI FFSR: TCPresent Mask */

#define TPI_FFSR_FtStopped_Pos              1U                                         /*!< TPI FFSR: FtStopped Position */
#define TPI_FFSR_FtStopped_Msk             (0x1UL << TPI_FFSR_FtStopped_Pos)           /*!< TPI FFSR: FtStopped Mask */

#define TPI_FFSR_FlInProg_Pos               0U                                         /*!< TPI FFSR: FlInProg Position */
#define TPI_FFSR_FlInProg_Msk              (0x1UL /*<< TPI_FFSR_FlInProg_Pos*/)        /*!< TPI FFSR: FlInProg Mask */

/* TPI Formatter and Flush Control Register Definitions */
#define TPI_FFCR_TrigIn_Pos                 8U                                         /*!< TPI FFCR: TrigIn Position */
#define TPI_FFCR_TrigIn_Msk                (0x1UL << TPI_FFCR_TrigIn_Pos)              /*!< TPI FFCR: TrigIn Mask */

#define TPI_FFCR_FOnMan_Pos                 6U                                         /*!< TPI FFCR: FOnMan Position */
#define TPI_FFCR_FOnMan_Msk                (0x1UL << TPI_FFCR_FOnMan_Pos)              /*!< TPI FFCR: FOnMan Mask */

#define TPI_FFCR_EnFCont_Pos                1U                                         /*!< TPI FFCR: EnFCont Position */
#define TPI_FFCR_EnFCont_Msk               (0x1UL << TPI_FFCR_EnFCont_Pos)             /*!< TPI FFCR: EnFCont Mask */

/* TPI TRIGGER Register Definitions */
#define TPI_TRIGGER_TRIGGER_Pos             0U                                         /*!< TPI TRIGGER: TRIGGER Position */
#define TPI_TRIGGER_TRIGGER_Msk            (0x1UL /*<< TPI_TRIGGER_TRIGGER_Pos*/)      /*!< TPI TRIGGER: TRIGGER Mask */

/* TPI Integration Test FIFO Test Data 0 Register Definitions */
#define TPI_ITFTTD0_ATB_IF2_ATVALID_Pos    29U                                         /*!< TPI ITFTTD0: ATB Interface 2 ATVALIDPosition */
#define TPI_ITFTTD0_ATB_IF2_ATVALID_Msk    (0x3UL << TPI_ITFTTD0_ATB_IF2_ATVALID_Pos)  /*!< TPI ITFTTD0: ATB Interface 2 ATVALID Mask */

#define TPI_ITFTTD0_ATB_IF2_bytecount_Pos  27U                                         /*!< TPI ITFTTD0: ATB Interface 2 byte count Position */
#define TPI_ITFTTD0_ATB_IF2_bytecount_Msk  (0x3UL << TPI_ITFTTD0_ATB_IF2_bytecount_Pos) /*!< TPI ITFTTD0: ATB Interface 2 byte count Mask */

#define TPI_ITFTTD0_ATB_IF1_ATVALID_Pos    26U                                         /*!< TPI ITFTTD0: ATB Interface 1 ATVALID Position */
#define TPI_ITFTTD0_ATB_IF1_ATVALID_Msk    (0x3UL << TPI_ITFTTD0_ATB_IF1_ATVALID_Pos)  /*!< TPI ITFTTD0: ATB Interface 1 ATVALID Mask */

#define TPI_ITFTTD0_ATB_IF1_bytecount_Pos  24U                                         /*!< TPI ITFTTD0: ATB Interface 1 byte count Position */
#define TPI_ITFTTD0_ATB_IF1_bytecount_Msk  (0x3UL << TPI_ITFTTD0_ATB_IF1_bytecount_Pos) /*!< TPI ITFTTD0: ATB Interface 1 byte countt Mask */

#define TPI_ITFTTD0_ATB_IF1_data2_Pos      16U                                         /*!< TPI ITFTTD0: ATB Interface 1 data2 Position */
#define TPI_ITFTTD0_ATB_IF1_data2_Msk      (0xFFUL << TPI_ITFTTD0_ATB_IF1_data1_Pos)   /*!< TPI ITFTTD0: ATB Interface 1 data2 Mask */

#define TPI_ITFTTD0_ATB_IF1_data1_Pos       8U                                         /*!< TPI ITFTTD0: ATB Interface 1 data1 Position */
#define TPI_ITFTTD0_ATB_IF1_data1_Msk      (0xFFUL << TPI_ITFTTD0_ATB_IF1_data1_Pos)   /*!< TPI ITFTTD0: ATB Interface 1 data1 Mask */

#define TPI_ITFTTD0_ATB_IF1_data0_Pos       0U                                          /*!< TPI ITFTTD0: ATB Interface 1 data0 Position */
#define TPI_ITFTTD0_ATB_IF1_data0_Msk      (0xFFUL /*<< TPI_ITFTTD0_ATB_IF1_data0_Pos*/) /*!< TPI ITFTTD0: ATB Interface 1 data0 Mask */

/* TPI Integration Test ATB Control Register 2 Register Definitions */
#define TPI_ITATBCTR2_AFVALID2S_Pos         1U                                         /*!< TPI ITATBCTR2: AFVALID2S Position */
#define TPI_ITATBCTR2_AFVALID2S_Msk        (0x1UL << TPI_ITATBCTR2_AFVALID2S_Pos)      /*!< TPI ITATBCTR2: AFVALID2SS Mask */

#define TPI_ITATBCTR2_AFVALID1S_Pos         1U                                         /*!< TPI ITATBCTR2: AFVALID1S Position */
#define TPI_ITATBCTR2_AFVALID1S_Msk        (0x1UL << TPI_ITATBCTR2_AFVALID1S_Pos)      /*!< TPI ITATBCTR2: AFVALID1SS Mask */

#define TPI_ITATBCTR2_ATREADY2S_Pos         0U                                         /*!< TPI ITATBCTR2: ATREADY2S Position */
#define TPI_ITATBCTR2_ATREADY2S_Msk        (0x1UL /*<< TPI_ITATBCTR2_ATREADY2S_Pos*/)  /*!< TPI ITATBCTR2: ATREADY2S Mask */

#define TPI_ITATBCTR2_ATREADY1S_Pos         0U                                         /*!< TPI ITATBCTR2: ATREADY1S Position */
#define TPI_ITATBCTR2_ATREADY1S_Msk        (0x1UL /*<< TPI_ITATBCTR2_ATREADY1S_Pos*/)  /*!< TPI ITATBCTR2: ATREADY1S Mask */

/* TPI Integration Test FIFO Test Data 1 Register Definitions */
#define TPI_ITFTTD1_ATB_IF2_ATVALID_Pos    29U                                         /*!< TPI ITFTTD1: ATB Interface 2 ATVALID Position */
#define TPI_ITFTTD1_ATB_IF2_ATVALID_Msk    (0x3UL << TPI_ITFTTD1_ATB_IF2_ATVALID_Pos)  /*!< TPI ITFTTD1: ATB Interface 2 ATVALID Mask */

#define TPI_ITFTTD1_ATB_IF2_bytecount_Pos  27U                                         /*!< TPI ITFTTD1: ATB Interface 2 byte count Position */
#define TPI_ITFTTD1_ATB_IF2_bytecount_Msk  (0x3UL << TPI_ITFTTD1_ATB_IF2_bytecount_Pos) /*!< TPI ITFTTD1: ATB Interface 2 byte count Mask */

#define TPI_ITFTTD1_ATB_IF1_ATVALID_Pos    26U                                         /*!< TPI ITFTTD1: ATB Interface 1 ATVALID Position */
#define TPI_ITFTTD1_ATB_IF1_ATVALID_Msk    (0x3UL << TPI_ITFTTD1_ATB_IF1_ATVALID_Pos)  /*!< TPI ITFTTD1: ATB Interface 1 ATVALID Mask */

#define TPI_ITFTTD1_ATB_IF1_bytecount_Pos  24U                                         /*!< TPI ITFTTD1: ATB Interface 1 byte count Position */
#define TPI_ITFTTD1_ATB_IF1_bytecount_Msk  (0x3UL << TPI_ITFTTD1_ATB_IF1_bytecount_Pos) /*!< TPI ITFTTD1: ATB Interface 1 byte countt Mask */

#define TPI_ITFTTD1_ATB_IF2_data2_Pos      16U                                         /*!< TPI ITFTTD1: ATB Interface 2 data2 Position */
#define TPI_ITFTTD1_ATB_IF2_data2_Msk      (0xFFUL << TPI_ITFTTD1_ATB_IF2_data1_Pos)   /*!< TPI ITFTTD1: ATB Interface 2 data2 Mask */

#define TPI_ITFTTD1_ATB_IF2_data1_Pos       8U                                         /*!< TPI ITFTTD1: ATB Interface 2 data1 Position */
#define TPI_ITFTTD1_ATB_IF2_data1_Msk      (0xFFUL << TPI_ITFTTD1_ATB_IF2_data1_Pos)   /*!< TPI ITFTTD1: ATB Interface 2 data1 Mask */

#define TPI_ITFTTD1_ATB_IF2_data0_Pos       0U                                          /*!< TPI ITFTTD1: ATB Interface 2 data0 Position */
#define TPI_ITFTTD1_ATB_IF2_data0_Msk      (0xFFUL /*<< TPI_ITFTTD1_ATB_IF2_data0_Pos*/) /*!< TPI ITFTTD1: ATB Interface 2 data0 Mask */

/* TPI Integration Test ATB Control Register 0 Definitions */
#define TPI_ITATBCTR0_AFVALID2S_Pos         1U                                         /*!< TPI ITATBCTR0: AFVALID2S Position */
#define TPI_ITATBCTR0_AFVALID2S_Msk        (0x1UL << TPI_ITATBCTR0_AFVALID2S_Pos)      /*!< TPI ITATBCTR0: AFVALID2SS Mask */

#define TPI_ITATBCTR0_AFVALID1S_Pos         1U                                         /*!< TPI ITATBCTR0: AFVALID1S Position */
#define TPI_ITATBCTR0_AFVALID1S_Msk        (0x1UL << TPI_ITATBCTR0_AFVALID1S_Pos)      /*!< TPI ITATBCTR0: AFVALID1SS Mask */

#define TPI_ITATBCTR0_ATREADY2S_Pos         0U                                         /*!< TPI ITATBCTR0: ATREADY2S Position */
#define TPI_ITATBCTR0_ATREADY2S_Msk        (0x1UL /*<< TPI_ITATBCTR0_ATREADY2S_Pos*/)  /*!< TPI ITATBCTR0: ATREADY2S Mask */

#define TPI_ITATBCTR0_ATREADY1S_Pos         0U                                         /*!< TPI ITATBCTR0: ATREADY1S Position */
#define TPI_ITATBCTR0_ATREADY1S_Msk        (0x1UL /*<< TPI_ITATBCTR0_ATREADY1S_Pos*/)  /*!< TPI ITATBCTR0: ATREADY1S Mask */

/* TPI Integration Mode Control Register Definitions */
#define TPI_ITCTRL_Mode_Pos                 0U                                         /*!< TPI ITCTRL: Mode Position */
#define TPI_ITCTRL_Mode_Msk                (0x3UL /*<< TPI_ITCTRL_Mode_Pos*/)          /*!< TPI ITCTRL: Mode Mask */

/* TPI DEVID Register Definitions */
#define TPI_DEVID_NRZVALID_Pos             11U                                         /*!< TPI DEVID: NRZVALID Position */
#define TPI_DEVID_NRZVALID_Msk             (0x1UL << TPI_DEVID_NRZVALID_Pos)           /*!< TPI DEVID: NRZVALID Mask */

#define TPI_DEVID_MANCVALID_Pos            10U                                         /*!< TPI DEVID: MANCVALID Position */
#define TPI_DEVID_MANCVALID_Msk            (0x1UL << TPI_DEVID_MANCVALID_Pos)          /*!< TPI DEVID: MANCVALID Mask */

#define TPI_DEVID_PTINVALID_Pos             9U                                         /*!< TPI DEVID: PTINVALID Position */
#define TPI_DEVID_PTINVALID_Msk            (0x1UL << TPI_DEVID_PTINVALID_Pos)          /*!< TPI DEVID: PTINVALID Mask */

#define TPI_DEVID_FIFOSZ_Pos                6U                                         /*!< TPI DEVID: FIFOSZ Position */
#define TPI_DEVID_FIFOSZ_Msk               (0x7UL << TPI_DEVID_FIFOSZ_Pos)             /*!< TPI DEVID: FIFOSZ Mask */

#define TPI_DEVID_NrTraceInput_Pos          0U                                         /*!< TPI DEVID: NrTraceInput Position */
#define TPI_DEVID_NrTraceInput_Msk         (0x3FUL /*<< TPI_DEVID_NrTraceInput_Pos*/)  /*!< TPI DEVID: NrTraceInput Mask */

/* TPI DEVTYPE Register Definitions */
#define TPI_DEVTYPE_SubType_Pos             4U                                         /*!< TPI DEVTYPE: SubType Position */
#define TPI_DEVTYPE_SubType_Msk            (0xFUL /*<< TPI_DEVTYPE_SubType_Pos*/)      /*!< TPI DEVTYPE: SubType Mask */

#define TPI_DEVTYPE_MajorType_Pos           0U                                         /*!< TPI DEVTYPE: MajorType Position */
#define TPI_DEVTYPE_MajorType_Msk          (0xFUL << TPI_DEVTYPE_MajorType_Pos)        /*!< TPI DEVTYPE: MajorType Mask */

/*@}*/ /* end of group CMSIS_TPI */


#if defined (__MPU_PRESENT) && (__MPU_PRESENT == 1U)
/**
  \ingroup  CMSIS_core_register
  \defgroup CMSIS_MPU     Memory Protection Unit (MPU)
  \brief    Type definitions for the Memory Protection Unit (MPU)
  @{
 */

/**
  \brief  Structure type to access the Memory Protection Unit (MPU).
 */
typedef struct
{
  __IM  uint32_t TYPE;                   /*!< Offset: 0x000 (R/ )  MPU Type Register */
  __IOM uint32_t CTRL;                   /*!< Offset: 0x004 (R/W)  MPU Control Register */
  __IOM uint32_t RNR;                    /*!< Offset: 0x008 (R/W)  MPU Region Number Register */
  __IOM uint32_t RBAR;                   /*!< Offset: 0x00C (R/W)  MPU Region Base Address Register */
  __IOM uint32_t RLAR;                   /*!< Offset: 0x010 (R/W)  MPU Region Limit Address Register */
  __IOM uint32_t RBAR_A1;                /*!< Offset: 0x014 (R/W)  MPU Region Base Address Register Alias 1 */
  __IOM uint32_t RLAR_A1;                /*!< Offset: 0x018 (R/W)  MPU Region Limit Address Register Alias 1 */
  __IOM uint32_t RBAR_A2;                /*!< Offset: 0x01C (R/W)  MPU Region Base Address Register Alias 2 */
  __IOM uint32_t RLAR_A2;                /*!< Offset: 0x020 (R/W)  MPU Region Limit Address Register Alias 2 */
  __IOM uint32_t RBAR_A3;                /*!< Offset: 0x024 (R/W)  MPU Region Base Address Register Alias 3 */
  __IOM uint32_t RLAR_A3;                /*!< Offset: 0x028 (R/W)  MPU Region Limit Address Register Alias 3 */
        uint32_t RESERVED0[1];
  union {
  __IOM uint32_t MAIR[2];
  struct {
  __IOM uint32_t MAIR0;                  /*!< Offset: 0x030 (R/W)  MPU Memory Attribute Indirection Register 0 */
  __IOM uint32_t MAIR1;                  /*!< Offset: 0x034 (R/W)  MPU Memory Attribute Indirection Register 1 */
  };
  };
} MPU_Type;

#define MPU_TYPE_RALIASES                  4U

/* MPU Type Register Definitions */
#define MPU_TYPE_IREGION_Pos               16U                                            /*!< MPU TYPE: IREGION Position */
#define MPU_TYPE_IREGION_Msk               (0xFFUL << MPU_TYPE_IREGION_Pos)               /*!< MPU TYPE: IREGION Mask */

#define MPU_TYPE_DREGION_Pos                8U                                            /*!< MPU TYPE: DREGION Position */
#define MPU_TYPE_DREGION_Msk               (0xFFUL << MPU_TYPE_DREGION_Pos)               /*!< MPU TYPE: DREGION Mask */

#define MPU_TYPE_SEPARATE_Pos               0U                                            /*!< MPU TYPE: SEPARATE Position */
#define MPU_TYPE_SEPARATE_Msk              (1UL /*<< MPU_TYPE_SEPARATE_Pos*/)             /*!< MPU TYPE: SEPARATE Mask */

/* MPU Control Register Definitions */
#define MPU_CTRL_PRIVDEFENA_Pos             2U                                            /*!< MPU CTRL: PRIVDEFENA Position */
#define MPU_CTRL_PRIVDEFENA_Msk            (1UL << MPU_CTRL_PRIVDEFENA_Pos)               /*!< MPU CTRL: PRIVDEFENA Mask */

#define MPU_CTRL_HFNMIENA_Pos               1U                                            /*!< MPU CTRL: HFNMIENA Position */
#define MPU_CTRL_HFNMIENA_Msk              (1UL << MPU_CTRL_HFNMIENA_Pos)                 /*!< MPU CTRL: HFNMIENA Mask */

#define MPU_CTRL_ENABLE_Pos                 0U                                            /*!< MPU CTRL: ENABLE Position */
#define MPU_CTRL_ENABLE_Msk                (1UL /*<< MPU_CTRL_ENABLE_Pos*/)               /*!< MPU CTRL: ENABLE Mask */

/* MPU Region Number Register Definitions */
#define MPU_RNR_REGION_Pos                  0U                                            /*!< MPU RNR: REGION Position */
#define MPU_RNR_REGION_Msk                 (0xFFUL /*<< MPU_RNR_REGION_Pos*/)             /*!< MPU RNR: REGION Mask */

/* MPU Region Base Address Register Definitions */
#define MPU_RBAR_BASE_Pos                   5U                                            /*!< MPU RBAR: BASE Position */
#define MPU_RBAR_BASE_Msk                  (0x7FFFFFFUL << MPU_RBAR_BASE_Pos)             /*!< MPU RBAR: BASE Mask */

#define MPU_RBAR_SH_Pos                     3U                                            /*!< MPU RBAR: SH Position */
#define MPU_RBAR_SH_Msk                    (0x3UL << MPU_RBAR_SH_Pos)                     /*!< MPU RBAR: SH Mask */

#define MPU_RBAR_AP_Pos                     1U                                            /*!< MPU RBAR: AP Position */
#define MPU_RBAR_AP_Msk                    (0x3UL << MPU_RBAR_AP_Pos)                     /*!< MPU RBAR: AP Mask */

#define MPU_RBAR_XN_Pos                     0U                                            /*!< MPU RBAR: XN Position */
#define MPU_RBAR_XN_Msk                    (01UL /*<< MPU_RBAR_XN_Pos*/)                  /*!< MPU RBAR: XN Mask */

/* MPU Region Limit Address Register Definitions */
#define MPU_RLAR_LIMIT_Pos                  5U                                            /*!< MPU RLAR: LIMIT Position */
#define MPU_RLAR_LIMIT_Msk                 (0x7FFFFFFUL << MPU_RLAR_LIMIT_Pos)            /*!< MPU RLAR: LIMIT Mask */

#define MPU_RLAR_AttrIndx_Pos               1U                                            /*!< MPU RLAR: AttrIndx Position */
#define MPU_RLAR_AttrIndx_Msk              (0x7UL << MPU_RLAR_AttrIndx_Pos)               /*!< MPU RLAR: AttrIndx Mask */

#define MPU_RLAR_EN_Pos                     0U                                            /*!< MPU RLAR: Region enable bit Position */
#define MPU_RLAR_EN_Msk                    (1UL /*<< MPU_RLAR_EN_Pos*/)                   /*!< MPU RLAR: Region enable bit Disable Mask */

/* MPU Memory Attribute Indirection Register 0 Definitions */
#define MPU_MAIR0_Attr3_Pos                24U                                            /*!< MPU MAIR0: Attr3 Position */
#define MPU_MAIR0_Attr3_Msk                (0xFFUL << MPU_MAIR0_Attr3_Pos)                /*!< MPU MAIR0: Attr3 Mask */

#define MPU_MAIR0_Attr2_Pos                16U                                            /*!< MPU MAIR0: Attr2 Position */
#define MPU_MAIR0_Attr2_Msk                (0xFFUL << MPU_MAIR0_Attr2_Pos)                /*!< MPU MAIR0: Attr2 Mask */

#define MPU_MAIR0_Attr1_Pos                 8U                                            /*!< MPU MAIR0: Attr1 Position */
#define MPU_MAIR0_Attr1_Msk                (0xFFUL << MPU_MAIR0_Attr1_Pos)                /*!< MPU MAIR0: Attr1 Mask */

#define MPU_MAIR0_Attr0_Pos                 0U                                            /*!< MPU MAIR0: Attr0 Position */
#define MPU_MAIR0_Attr0_Msk                (0xFFUL /*<< MPU_MAIR0_Attr0_Pos*/)            /*!< MPU MAIR0: Attr0 Mask */

/* MPU Memory Attribute Indirection Register 1 Definitions */
#define MPU_MAIR1_Attr7_Pos                24U                                            /*!< MPU MAIR1: Attr7 Position */
#define MPU_MAIR1_Attr7_Msk                (0xFFUL << MPU_MAIR1_Attr7_Pos)                /*!< MPU MAIR1: Attr7 Mask */

#define MPU_MAIR1_Attr6_Pos                16U                                            /*!< MPU MAIR1: Attr6 Position */
#define MPU_MAIR1_Attr6_Msk                (0xFFUL << MPU_MAIR1_Attr6_Pos)                /*!< MPU MAIR1: Attr6 Mask */

#define MPU_MAIR1_Attr5_Pos                 8U                                            /*!< MPU MAIR1: Attr5 Position */
#define MPU_MAIR1_Attr5_Msk                (0xFFUL << MPU_MAIR1_Attr5_Pos)                /*!< MPU MAIR1: Attr5 Mask */

#define MPU_MAIR1_Attr4_Pos                 0U                                            /*!< MPU MAIR1: Attr4 Position */
#define MPU_MAIR1_Attr4_Msk                (0xFFUL /*<< MPU_MAIR1_Attr4_Pos*/)            /*!< MPU MAIR1: Attr4 Mask */

/*@} end of group CMSIS_MPU */
#endif


#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  \ingroup  CMSIS_core_register
  \defgroup CMSIS_SAU     Security Attribution Unit (SAU)
  \brief    Type definitions for the Security Attribution Unit (SAU)
  @{
 */

/**
  \brief  Structure type to access the Security Attribution Unit (SAU).
 */
typedef struct
{
  __IOM uint32_t CTRL;                   /*!< Offset: 0x000 (R/W)  SAU Control Register */
  __IM  uint32_t TYPE;                   /*!< Offset: 0x004 (R/ )  SAU Type Register */
#if defined (__SAUREGION_PRESENT) && (__SAUREGION_PRESENT == 1U)
  __IOM uint32_t RNR;                    /*!< Offset: 0x008 (R/W)  SAU Region Number Register */
  __IOM uint32_t RBAR;                   /*!< Offset: 0x00C (R/W)  SAU Region Base Address Register */
  __IOM uint32_t RLAR;                   /*!< Offset: 0x010 (R/W)  SAU Region Limit Address Register */
#else
        uint32_t RESERVED0[3];
#endif
  __IOM uint32_t SFSR;                   /*!< Offset: 0x014 (R/W)  Secure Fault Status Register */
  __IOM uint32_t SFAR;                   /*!< Offset: 0x018 (R/W)  Secure Fault Address Register */
} SAU_Type;

/* SAU Control Register Definitions */
#define SAU_CTRL_ALLNS_Pos                  1U                                            /*!< SAU CTRL: ALLNS Position */
#define SAU_CTRL_ALLNS_Msk                 (1UL << SAU_CTRL_ALLNS_Pos)                    /*!< SAU CTRL: ALLNS Mask */

#define SAU_CTRL_ENABLE_Pos                 0U                                            /*!< SAU CTRL: ENABLE Position */
#define SAU_CTRL_ENABLE_Msk                (1UL /*<< SAU_CTRL_ENABLE_Pos*/)               /*!< SAU CTRL: ENABLE Mask */

/* SAU Type Register Definitions */
#define SAU_TYPE_SREGION_Pos                0U                                            /*!< SAU TYPE: SREGION Position */
#define SAU_TYPE_SREGION_Msk               (0xFFUL /*<< SAU_TYPE_SREGION_Pos*/)           /*!< SAU TYPE: SREGION Mask */

#if defined (__SAUREGION_PRESENT) && (__SAUREGION_PRESENT == 1U)
/* SAU Region Number Register Definitions */
#define SAU_RNR_REGION_Pos                  0U                                            /*!< SAU RNR: REGION Position */
#define SAU_RNR_REGION_Msk                 (0xFFUL /*<< SAU_RNR_REGION_Pos*/)             /*!< SAU RNR: REGION Mask */

/* SAU Region Base Address Register Definitions */
#define SAU_RBAR_BADDR_Pos                  5U                                            /*!< SAU RBAR: BADDR Position */
#define SAU_RBAR_BADDR_Msk                 (0x7FFFFFFUL << SAU_RBAR_BADDR_Pos)            /*!< SAU RBAR: BADDR Mask */

/* SAU Region Limit Address Register Definitions */
#define SAU_RLAR_LADDR_Pos                  5U                                            /*!< SAU RLAR: LADDR Position */
#define SAU_RLAR_LADDR_Msk                 (0x7FFFFFFUL << SAU_RLAR_LADDR_Pos)            /*!< SAU RLAR: LADDR Mask */

#define SAU_RLAR_NSC_Pos                    1U                                            /*!< SAU RLAR: NSC Position */
#define SAU_RLAR_NSC_Msk                   (1UL << SAU_RLAR_NSC_Pos)                      /*!< SAU RLAR: NSC Mask */

#define SAU_RLAR_ENABLE_Pos                 0U                                            /*!< SAU RLAR: ENABLE Position */
#define SAU_RLAR_ENABLE_Msk                (1UL /*<< SAU_RLAR_ENABLE_Pos*/)               /*!< SAU RLAR: ENABLE Mask */

#endif /* defined (__SAUREGION_PRESENT) && (__SAUREGION_PRESENT == 1U) */

/* Secure Fault Status Register Definitions */
#define SAU_SFSR_LSERR_Pos                  7U                                            /*!< SAU SFSR: LSERR Position */
#define SAU_SFSR_LSERR_Msk                 (1UL << SAU_SFSR_LSERR_Pos)                    /*!< SAU SFSR: LSERR Mask */

#define SAU_SFSR_SFARVALID_Pos              6U                                            /*!< SAU SFSR: SFARVALID Position */
#define SAU_SFSR_SFARVALID_Msk             (1UL << SAU_SFSR_SFARVALID_Pos)                /*!< SAU SFSR: SFARVALID Mask */

#define SAU_SFSR_LSPERR_Pos                 5U                                            /*!< SAU SFSR: LSPERR Position */
#define SAU_SFSR_LSPERR_Msk                (1UL << SAU_SFSR_LSPERR_Pos)                   /*!< SAU SFSR: LSPERR Mask */

#define SAU_SFSR_INVTRAN_Pos                4U                                            /*!< SAU SFSR: INVTRAN Position */
#define SAU_SFSR_INVTRAN_Msk               (1UL << SAU_SFSR_INVTRAN_Pos)                  /*!< SAU SFSR: INVTRAN Mask */

#define SAU_SFSR_AUVIOL_Pos                 3U                                            /*!< SAU SFSR: AUVIOL Position */
#define SAU_SFSR_AUVIOL_Msk                (1UL << SAU_SFSR_AUVIOL_Pos)                   /*!< SAU SFSR: AUVIOL Mask */

#define SAU_SFSR_INVER_Pos                  2U                                            /*!< SAU SFSR: INVER Position */
#define SAU_SFSR_INVER_Msk                 (1UL << SAU_SFSR_INVER_Pos)                    /*!< SAU SFSR: INVER Mask */

#define SAU_SFSR_INVIS_Pos                  1U                                            /*!< SAU SFSR: INVIS Position */
#define SAU_SFSR_INVIS_Msk                 (1UL << SAU_SFSR_INVIS_Pos)                    /*!< SAU SFSR: INVIS Mask */

#define SAU_SFSR_INVEP_Pos                  0U                                            /*!< SAU SFSR: INVEP Position */
#define SAU_SFSR_INVEP_Msk                 (1UL /*<< SAU_SFSR_INVEP_Pos*/)                /*!< SAU SFSR: INVEP Mask */

/*@} end of group CMSIS_SAU */
#endif /* defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */


/**
  \ingroup  CMSIS_core_register
  \defgroup CMSIS_FPU     Floating Point Unit (FPU)
  \brief    Type definitions for the Floating Point Unit (FPU)
  @{
 */

/**
  \brief  Structure type to access the Floating Point Unit (FPU).
 */
typedef struct
{
        uint32_t RESERVED0[1U];
  __IOM uint32_t FPCCR;                  /*!< Offset: 0x004 (R/W)  Floating-Point Context Control Register */
  __IOM uint32_t FPCAR;                  /*!< Offset: 0x008 (R/W)  Floating-Point Context Address Register */
  __IOM uint32_t FPDSCR;                 /*!< Offset: 0x00C (R/W)  Floating-Point Default Status Control Register */
  __IM  uint32_t MVFR0;                  /*!< Offset: 0x010 (R/ )  Media and VFP Feature Register 0 */
  __IM  uint32_t MVFR1;                  /*!< Offset: 0x014 (R/ )  Media and VFP Feature Register 1 */
  __IM  uint32_t MVFR2;                  /*!< Offset: 0x018 (R/ )  Media and VFP Feature Register 2 */
} FPU_Type;

/* Floating-Point Context Control Register Definitions */
#define FPU_FPCCR_ASPEN_Pos                31U                                            /*!< FPCCR: ASPEN bit Position */
#define FPU_FPCCR_ASPEN_Msk                (1UL << FPU_FPCCR_ASPEN_Pos)                   /*!< FPCCR: ASPEN bit Mask */

#define FPU_FPCCR_LSPEN_Pos                30U                                            /*!< FPCCR: LSPEN Position */
#define FPU_FPCCR_LSPEN_Msk                (1UL << FPU_FPCCR_LSPEN_Pos)                   /*!< FPCCR: LSPEN bit Mask */

#define FPU_FPCCR_LSPENS_Pos               29U                                            /*!< FPCCR: LSPENS Position */
#define FPU_FPCCR_LSPENS_Msk               (1UL << FPU_FPCCR_LSPENS_Pos)                  /*!< FPCCR: LSPENS bit Mask */

#define FPU_FPCCR_CLRONRET_Pos             28U                                            /*!< FPCCR: CLRONRET Position */
#define FPU_FPCCR_CLRONRET_Msk             (1UL << FPU_FPCCR_CLRONRET_Pos)                /*!< FPCCR: CLRONRET bit Mask */

#define FPU_FPCCR_CLRONRETS_Pos            27U                                            /*!< FPCCR: CLRONRETS Position */
#define FPU_FPCCR_CLRONRETS_Msk            (1UL << FPU_FPCCR_CLRONRETS_Pos)               /*!< FPCCR: CLRONRETS bit Mask */

#define FPU_FPCCR_TS_Pos                   26U                                            /*!< FPCCR: TS Position */
#define FPU_FPCCR_TS_Msk                   (1UL << FPU_FPCCR_TS_Pos)                      /*!< FPCCR: TS bit Mask */

#define FPU_FPCCR_UFRDY_Pos                10U                                            /*!< FPCCR: UFRDY Position */
#define FPU_FPCCR_UFRDY_Msk                (1UL << FPU_FPCCR_UFRDY_Pos)                   /*!< FPCCR: UFRDY bit Mask */

#define FPU_FPCCR_SPLIMVIOL_Pos             9U                                            /*!< FPCCR: SPLIMVIOL Position */
#define FPU_FPCCR_SPLIMVIOL_Msk            (1UL << FPU_FPCCR_SPLIMVIOL_Pos)               /*!< FPCCR: SPLIMVIOL bit Mask */

#define FPU_FPCCR_MONRDY_Pos                8U                                            /*!< FPCCR: MONRDY Position */
#define FPU_FPCCR_MONRDY_Msk               (1UL << FPU_FPCCR_MONRDY_Pos)                  /*!< FPCCR: MONRDY bit Mask */

#define FPU_FPCCR_SFRDY_Pos                 7U                                            /*!< FPCCR: SFRDY Position */
#define FPU_FPCCR_SFRDY_Msk                (1UL << FPU_FPCCR_SFRDY_Pos)                   /*!< FPCCR: SFRDY bit Mask */

#define FPU_FPCCR_BFRDY_Pos                 6U                                            /*!< FPCCR: BFRDY Position */
#define FPU_FPCCR_BFRDY_Msk                (1UL << FPU_FPCCR_BFRDY_Pos)                   /*!< FPCCR: BFRDY bit Mask */

#define FPU_FPCCR_MMRDY_Pos                 5U                                            /*!< FPCCR: MMRDY Position */
#define FPU_FPCCR_MMRDY_Msk                (1UL << FPU_FPCCR_MMRDY_Pos)                   /*!< FPCCR: MMRDY bit Mask */

#define FPU_FPCCR_HFRDY_Pos                 4U                                            /*!< FPCCR: HFRDY Position */
#define FPU_FPCCR_HFRDY_Msk                (1UL << FPU_FPCCR_HFRDY_Pos)                   /*!< FPCCR: HFRDY bit Mask */

#define FPU_FPCCR_THREAD_Pos                3U                                            /*!< FPCCR: processor mode bit Position */
#define FPU_FPCCR_THREAD_Msk               (1UL << FPU_FPCCR_THREAD_Pos)                  /*!< FPCCR: processor mode active bit Mask */

#define FPU_FPCCR_S_Pos                     2U                                            /*!< FPCCR: Security status of the FP context bit Position */
#define FPU_FPCCR_S_Msk                    (1UL << FPU_FPCCR_S_Pos)                       /*!< FPCCR: Security status of the FP context bit Mask */

#define FPU_FPCCR_USER_Pos                  1U                                            /*!< FPCCR: privilege level bit Position */
#define FPU_FPCCR_USER_Msk                 (1UL << FPU_FPCCR_USER_Pos)                    /*!< FPCCR: privilege level bit Mask */

#define FPU_FPCCR_LSPACT_Pos                0U                                            /*!< FPCCR: Lazy state preservation active bit Position */
#define FPU_FPCCR_LSPACT_Msk               (1UL /*<< FPU_FPCCR_LSPACT_Pos*/)              /*!< FPCCR: Lazy state preservation active bit Mask */

/* Floating-Point Context Address Register Definitions */
#define FPU_FPCAR_ADDRESS_Pos               3U                                            /*!< FPCAR: ADDRESS bit Position */
#define FPU_FPCAR_ADDRESS_Msk              (0x1FFFFFFFUL << FPU_FPCAR_ADDRESS_Pos)        /*!< FPCAR: ADDRESS bit Mask */

/* Floating-Point Default Status Control Register Definitions */
#define FPU_FPDSCR_AHP_Pos                 26U                                            /*!< FPDSCR: AHP bit Position */
#define FPU_FPDSCR_AHP_Msk                 (1UL << FPU_FPDSCR_AHP_Pos)                    /*!< FPDSCR: AHP bit Mask */

#define FPU_FPDSCR_DN_Pos                  25U                                            /*!< FPDSCR: DN bit Position */
#define FPU_FPDSCR_DN_Msk                  (1UL << FPU_FPDSCR_DN_Pos)                     /*!< FPDSCR: DN bit Mask */

#define FPU_FPDSCR_FZ_Pos                  24U                                            /*!< FPDSCR: FZ bit Position */
#define FPU_FPDSCR_FZ_Msk                  (1UL << FPU_FPDSCR_FZ_Pos)                     /*!< FPDSCR: FZ bit Mask */

#define FPU_FPDSCR_RMode_Pos               22U                                            /*!< FPDSCR: RMode bit Position */
#define FPU_FPDSCR_RMode_Msk               (3UL << FPU_FPDSCR_RMode_Pos)                  /*!< FPDSCR: RMode bit Mask */

/* Media and VFP Feature Register 0 Definitions */
#define FPU_MVFR0_FP_rounding_modes_Pos    28U                                            /*!< MVFR0: FP rounding modes bits Position */
#define FPU_MVFR0_FP_rounding_modes_Msk    (0xFUL << FPU_MVFR0_FP_rounding_modes_Pos)     /*!< MVFR0: FP rounding modes bits Mask */

#define FPU_MVFR0_Short_vectors_Pos        24U                                            /*!< MVFR0: Short vectors bits Position */
#define FPU_MVFR0_Short_vectors_Msk        (0xFUL << FPU_MVFR0_Short_vectors_Pos)         /*!< MVFR0: Short vectors bits Mask */

#define FPU_MVFR0_Square_root_Pos          20U                                            /*!< MVFR0: Square root bits Position */
#define FPU_MVFR0_Square_root_Msk          (0xFUL << FPU_MVFR0_Square_root_Pos)           /*!< MVFR0: Square root bits Mask */

#define FPU_MVFR0_Divide_Pos               16U                                            /*!< MVFR0: Divide bits Position */
#define FPU_MVFR0_Divide_Msk               (0xFUL << FPU_MVFR0_Divide_Pos)                /*!< MVFR0: Divide bits Mask */

#define FPU_MVFR0_FP_excep_trapping_Pos    12U                                            /*!< MVFR0: FP exception trapping bits Position */
#define FPU_MVFR0_FP_excep_trapping_Msk    (0xFUL << FPU_MVFR0_FP_excep_trapping_Pos)     /*!< MVFR0: FP exception trapping bits Mask */

#define FPU_MVFR0_Double_precision_Pos      8U                                            /*!< MVFR0: Double-precision bits Position */
#define FPU_MVFR0_Double_precision_Msk     (0xFUL << FPU_MVFR0_Double_precision_Pos)      /*!< MVFR0: Double-precision bits Mask */

#define FPU_MVFR0_Single_precision_Pos      4U                                            /*!< MVFR0: Single-precision bits Position */
#define FPU_MVFR0_Single_precision_Msk     (0xFUL << FPU_MVFR0_Single_precision_Pos)      /*!< MVFR0: Single-precision bits Mask */

#define FPU_MVFR0_A_SIMD_registers_Pos      0U                                            /*!< MVFR0: A_SIMD registers bits Position */
#define FPU_MVFR0_A_SIMD_registers_Msk     (0xFUL /*<< FPU_MVFR0_A_SIMD_registers_Pos*/)  /*!< MVFR0: A_SIMD registers bits Mask */

/* Media and VFP Feature Register 1 Definitions */
#define FPU_MVFR1_FP_fused_MAC_Pos         28U                                            /*!< MVFR1: FP fused MAC bits Position */
#define FPU_MVFR1_FP_fused_MAC_Msk         (0xFUL << FPU_MVFR1_FP_fused_MAC_Pos)          /*!< MVFR1: FP fused MAC bits Mask */

#define FPU_MVFR1_FP_HPFP_Pos              24U                                            /*!< MVFR1: FP HPFP bits Position */
#define FPU_MVFR1_FP_HPFP_Msk              (0xFUL << FPU_MVFR1_FP_HPFP_Pos)               /*!< MVFR1: FP HPFP bits Mask */

#define FPU_MVFR1_D_NaN_mode_Pos            4U                                            /*!< MVFR1: D_NaN mode bits Position */
#define FPU_MVFR1_D_NaN_mode_Msk           (0xFUL << FPU_MVFR1_D_NaN_mode_Pos)            /*!< MVFR1: D_NaN mode bits Mask */

#define FPU_MVFR1_FtZ_mode_Pos              0U                                            /*!< MVFR1: FtZ mode bits Position */
#define FPU_MVFR1_FtZ_mode_Msk             (0xFUL /*<< FPU_MVFR1_FtZ_mode_Pos*/)          /*!< MVFR1: FtZ mode bits Mask */

/* Media and VFP Feature Register 2 Definitions */
#define FPU_MVFR2_FPMisc_Pos                4U                                            /*!< MVFR2: FPMisc bits Position */
#define FPU_MVFR2_FPMisc_Msk               (0xFUL << FPU_MVFR2_FPMisc_Pos)                /*!< MVFR2: FPMisc bits Mask */

/*@} end of group CMSIS_FPU */

/* CoreDebug is deprecated. replaced by DCB (Debug Control Block) */
/**
  \ingroup  CMSIS_core_register
  \defgroup CMSIS_CoreDebug       Core Debug Registers (CoreDebug)
  \brief    Type definitions for the Core Debug Registers
  @{
 */

/**
  \brief  \deprecated Structure type to access the Core Debug Register (CoreDebug).
 */
typedef struct
{
  __IOM uint32_t DHCSR;                  /*!< Offset: 0x000 (R/W)  Debug Halting Control and Status Register */
  __OM  uint32_t DCRSR;                  /*!< Offset: 0x004 ( /W)  Debug Core Register Selector Register */
  __IOM uint32_t DCRDR;                  /*!< Offset: 0x008 (R/W)  Debug Core Register Data Register */
  __IOM uint32_t DEMCR;                  /*!< Offset: 0x00C (R/W)  Debug Exception and Monitor Control Register */
        uint32_t RESERVED0[1U];
  __IOM uint32_t DAUTHCTRL;              /*!< Offset: 0x014 (R/W)  Debug Authentication Control Register */
  __IOM uint32_t DSCSR;                  /*!< Offset: 0x018 (R/W)  Debug Security Control and Status Register */
} CoreDebug_Type;

/* Debug Halting Control and Status Register Definitions */
#define CoreDebug_DHCSR_DBGKEY_Pos         16U                                            /*!< \deprecated CoreDebug DHCSR: DBGKEY Position */
#define CoreDebug_DHCSR_DBGKEY_Msk         (0xFFFFUL << CoreDebug_DHCSR_DBGKEY_Pos)       /*!< \deprecated CoreDebug DHCSR: DBGKEY Mask */

#define CoreDebug_DHCSR_S_RESTART_ST_Pos   26U                                            /*!< \deprecated CoreDebug DHCSR: S_RESTART_ST Position */
#define CoreDebug_DHCSR_S_RESTART_ST_Msk   (1UL << CoreDebug_DHCSR_S_RESTART_ST_Pos)      /*!< \deprecated CoreDebug DHCSR: S_RESTART_ST Mask */

#define CoreDebug_DHCSR_S_RESET_ST_Pos     25U                                            /*!< \deprecated CoreDebug DHCSR: S_RESET_ST Position */
#define CoreDebug_DHCSR_S_RESET_ST_Msk     (1UL << CoreDebug_DHCSR_S_RESET_ST_Pos)        /*!< \deprecated CoreDebug DHCSR: S_RESET_ST Mask */

#define CoreDebug_DHCSR_S_RETIRE_ST_Pos    24U                                            /*!< \deprecated CoreDebug DHCSR: S_RETIRE_ST Position */
#define CoreDebug_DHCSR_S_RETIRE_ST_Msk    (1UL << CoreDebug_DHCSR_S_RETIRE_ST_Pos)       /*!< \deprecated CoreDebug DHCSR: S_RETIRE_ST Mask */

#define CoreDebug_DHCSR_S_LOCKUP_Pos       19U                                            /*!< \deprecated CoreDebug DHCSR: S_LOCKUP Position */
#define CoreDebug_DHCSR_S_LOCKUP_Msk       (1UL << CoreDebug_DHCSR_S_LOCKUP_Pos)          /*!< \deprecated CoreDebug DHCSR: S_LOCKUP Mask */

#define CoreDebug_DHCSR_S_SLEEP_Pos        18U                                            /*!< \deprecated CoreDebug DHCSR: S_SLEEP Position */
#define CoreDebug_DHCSR_S_SLEEP_Msk        (1UL << CoreDebug_DHCSR_S_SLEEP_Pos)           /*!< \deprecated CoreDebug DHCSR: S_SLEEP Mask */

#define CoreDebug_DHCSR_S_HALT_Pos         17U                                            /*!< \deprecated CoreDebug DHCSR: S_HALT Position */
#define CoreDebug_DHCSR_S_HALT_Msk         (1UL << CoreDebug_DHCSR_S_HALT_Pos)            /*!< \deprecated CoreDebug DHCSR: S_HALT Mask */

#define CoreDebug_DHCSR_S_REGRDY_Pos       16U                                            /*!< \deprecated CoreDebug DHCSR: S_REGRDY Position */
#define CoreDebug_DHCSR_S_REGRDY_Msk       (1UL << CoreDebug_DHCSR_S_REGRDY_Pos)          /*!< \deprecated CoreDebug DHCSR: S_REGRDY Mask */

#define CoreDebug_DHCSR_C_SNAPSTALL_Pos     5U                                            /*!< \deprecated CoreDebug DHCSR: C_SNAPSTALL Position */
#define CoreDebug_DHCSR_C_SNAPSTALL_Msk    (1UL << CoreDebug_DHCSR_C_SNAPSTALL_Pos)       /*!< \deprecated CoreDebug DHCSR: C_SNAPSTALL Mask */

#define CoreDebug_DHCSR_C_MASKINTS_Pos      3U                                            /*!< \deprecated CoreDebug DHCSR: C_MASKINTS Position */
#define CoreDebug_DHCSR_C_MASKINTS_Msk     (1UL << CoreDebug_DHCSR_C_MASKINTS_Pos)        /*!< \deprecated CoreDebug DHCSR: C_MASKINTS Mask */

#define CoreDebug_DHCSR_C_STEP_Pos          2U                                            /*!< \deprecated CoreDebug DHCSR: C_STEP Position */
#define CoreDebug_DHCSR_C_STEP_Msk         (1UL << CoreDebug_DHCSR_C_STEP_Pos)            /*!< \deprecated CoreDebug DHCSR: C_STEP Mask */

#define CoreDebug_DHCSR_C_HALT_Pos          1U                                            /*!< \deprecated CoreDebug DHCSR: C_HALT Position */
#define CoreDebug_DHCSR_C_HALT_Msk         (1UL << CoreDebug_DHCSR_C_HALT_Pos)            /*!< \deprecated CoreDebug DHCSR: C_HALT Mask */

#define CoreDebug_DHCSR_C_DEBUGEN_Pos       0U                                            /*!< \deprecated CoreDebug DHCSR: C_DEBUGEN Position */
#define CoreDebug_DHCSR_C_DEBUGEN_Msk      (1UL /*<< CoreDebug_DHCSR_C_DEBUGEN_Pos*/)     /*!< \deprecated CoreDebug DHCSR: C_DEBUGEN Mask */

/* Debug Core Register Selector Register Definitions */
#define CoreDebug_DCRSR_REGWnR_Pos         16U                                            /*!< \deprecated CoreDebug DCRSR: REGWnR Position */
#define CoreDebug_DCRSR_REGWnR_Msk         (1UL << CoreDebug_DCRSR_REGWnR_Pos)            /*!< \deprecated CoreDebug DCRSR: REGWnR Mask */

#define CoreDebug_DCRSR_REGSEL_Pos          0U                                            /*!< \deprecated CoreDebug DCRSR: REGSEL Position */
#define CoreDebug_DCRSR_REGSEL_Msk         (0x1FUL /*<< CoreDebug_DCRSR_REGSEL_Pos*/)     /*!< \deprecated CoreDebug DCRSR: REGSEL Mask */

/* Debug Exception and Monitor Control Register Definitions */
#define CoreDebug_DEMCR_TRCENA_Pos         24U                                            /*!< \deprecated CoreDebug DEMCR: TRCENA Position */
#define CoreDebug_DEMCR_TRCENA_Msk         (1UL << CoreDebug_DEMCR_TRCENA_Pos)            /*!< \deprecated CoreDebug DEMCR: TRCENA Mask */

#define CoreDebug_DEMCR_MON_REQ_Pos        19U                                            /*!< \deprecated CoreDebug DEMCR: MON_REQ Position */
#define CoreDebug_DEMCR_MON_REQ_Msk        (1UL << CoreDebug_DEMCR_MON_REQ_Pos)           /*!< \deprecated CoreDebug DEMCR: MON_REQ Mask */

#define CoreDebug_DEMCR_MON_STEP_Pos       18U                                            /*!< \deprecated CoreDebug DEMCR: MON_STEP Position */
#define CoreDebug_DEMCR_MON_STEP_Msk       (1UL << CoreDebug_DEMCR_MON_STEP_Pos)          /*!< \deprecated CoreDebug DEMCR: MON_STEP Mask */

#define CoreDebug_DEMCR_MON_PEND_Pos       17U                                            /*!< \deprecated CoreDebug DEMCR: MON_PEND Position */
#define CoreDebug_DEMCR_MON_PEND_Msk       (1UL << CoreDebug_DEMCR_MON_PEND_Pos)          /*!< \deprecated CoreDebug DEMCR: MON_PEND Mask */

#define CoreDebug_DEMCR_MON_EN_Pos         16U                                            /*!< \deprecated CoreDebug DEMCR: MON_EN Position */
#define CoreDebug_DEMCR_MON_EN_Msk         (1UL << CoreDebug_DEMCR_MON_EN_Pos)            /*!< \deprecated CoreDebug DEMCR: MON_EN Mask */

#define CoreDebug_DEMCR_VC_HARDERR_Pos     10U                                            /*!< \deprecated CoreDebug DEMCR: VC_HARDERR Position */
#define CoreDebug_DEMCR_VC_HARDERR_Msk     (1UL << CoreDebug_DEMCR_VC_HARDERR_Pos)        /*!< \deprecated CoreDebug DEMCR: VC_HARDERR Mask */

#define CoreDebug_DEMCR_VC_INTERR_Pos       9U                                            /*!< \deprecated CoreDebug DEMCR: VC_INTERR Position */
#define CoreDebug_DEMCR_VC_INTERR_Msk      (1UL << CoreDebug_DEMCR_VC_INTERR_Pos)         /*!< \deprecated CoreDebug DEMCR: VC_INTERR Mask */

#define CoreDebug_DEMCR_VC_BUSERR_Pos       8U                                            /*!< \deprecated CoreDebug DEMCR: VC_BUSERR Position */
#define CoreDebug_DEMCR_VC_BUSERR_Msk      (1UL << CoreDebug_DEMCR_VC_BUSERR_Pos)         /*!< \deprecated CoreDebug DEMCR: VC_BUSERR Mask */

#define CoreDebug_DEMCR_VC_STATERR_Pos      7U                                            /*!< \deprecated CoreDebug DEMCR: VC_STATERR Position */
#define CoreDebug_DEMCR_VC_STATERR_Msk     (1UL << CoreDebug_DEMCR_VC_STATERR_Pos)        /*!< \deprecated CoreDebug DEMCR: VC_STATERR Mask */

#define CoreDebug_DEMCR_VC_CHKERR_Pos       6U                                            /*!< \deprecated CoreDebug DEMCR: VC_CHKERR Position */
#define CoreDebug_DEMCR_VC_CHKERR_Msk      (1UL << CoreDebug_DEMCR_VC_CHKERR_Pos)         /*!< \deprecated CoreDebug DEMCR: VC_CHKERR Mask */

#define CoreDebug_DEMCR_VC_NOCPERR_Pos      5U                                            /*!< \deprecated CoreDebug DEMCR: VC_NOCPERR Position */
#define CoreDebug_DEMCR_VC_NOCPERR_Msk     (1UL << CoreDebug_DEMCR_VC_NOCPERR_Pos)        /*!< \deprecated CoreDebug DEMCR: VC_NOCPERR Mask */

#define CoreDebug_DEMCR_VC_MMERR_Pos        4U                                            /*!< \deprecated CoreDebug DEMCR: VC_MMERR Position */
#define CoreDebug_DEMCR_VC_MMERR_Msk       (1UL << CoreDebug_DEMCR_VC_MMERR_Pos)          /*!< \deprecated CoreDebug DEMCR: VC_MMERR Mask */

#define CoreDebug_DEMCR_VC_CORERESET_Pos    0U                                            /*!< \deprecated CoreDebug DEMCR: VC_CORERESET Position */
#define CoreDebug_DEMCR_VC_CORERESET_Msk   (1UL /*<< CoreDebug_DEMCR_VC_CORERESET_Pos*/)  /*!< \deprecated CoreDebug DEMCR: VC_CORERESET Mask */

/* Debug Authentication Control Register Definitions */
#define CoreDebug_DAUTHCTRL_INTSPNIDEN_Pos  3U                                            /*!< \deprecated CoreDebug DAUTHCTRL: INTSPNIDEN, Position */
#define CoreDebug_DAUTHCTRL_INTSPNIDEN_Msk (1UL << CoreDebug_DAUTHCTRL_INTSPNIDEN_Pos)    /*!< \deprecated CoreDebug DAUTHCTRL: INTSPNIDEN, Mask */

#define CoreDebug_DAUTHCTRL_SPNIDENSEL_Pos  2U                                            /*!< \deprecated CoreDebug DAUTHCTRL: SPNIDENSEL Position */
#define CoreDebug_DAUTHCTRL_SPNIDENSEL_Msk (1UL << CoreDebug_DAUTHCTRL_SPNIDENSEL_Pos)    /*!< \deprecated CoreDebug DAUTHCTRL: SPNIDENSEL Mask */

#define CoreDebug_DAUTHCTRL_INTSPIDEN_Pos   1U                                            /*!< \deprecated CoreDebug DAUTHCTRL: INTSPIDEN Position */
#define CoreDebug_DAUTHCTRL_INTSPIDEN_Msk  (1UL << CoreDebug_DAUTHCTRL_INTSPIDEN_Pos)     /*!< \deprecated CoreDebug DAUTHCTRL: INTSPIDEN Mask */

#define CoreDebug_DAUTHCTRL_SPIDENSEL_Pos   0U                                            /*!< \deprecated CoreDebug DAUTHCTRL: SPIDENSEL Position */
#define CoreDebug_DAUTHCTRL_SPIDENSEL_Msk  (1UL /*<< CoreDebug_DAUTHCTRL_SPIDENSEL_Pos*/) /*!< \deprecated CoreDebug DAUTHCTRL: SPIDENSEL Mask */

/* Debug Security Control and Status Register Definitions */
#define CoreDebug_DSCSR_CDS_Pos            16U                                            /*!< \deprecated CoreDebug DSCSR: CDS Position */
#define CoreDebug_DSCSR_CDS_Msk            (1UL << CoreDebug_DSCSR_CDS_Pos)               /*!< \deprecated CoreDebug DSCSR: CDS Mask */

#define CoreDebug_DSCSR_SBRSEL_Pos          1U                                            /*!< \deprecated CoreDebug DSCSR: SBRSEL Position */
#define CoreDebug_DSCSR_SBRSEL_Msk         (1UL << CoreDebug_DSCSR_SBRSEL_Pos)            /*!< \deprecated CoreDebug DSCSR: SBRSEL Mask */

#define CoreDebug_DSCSR_SBRSELEN_Pos        0U                                            /*!< \deprecated CoreDebug DSCSR: SBRSELEN Position */
#define CoreDebug_DSCSR_SBRSELEN_Msk       (1UL /*<< CoreDebug_DSCSR_SBRSELEN_Pos*/)      /*!< \deprecated CoreDebug DSCSR: SBRSELEN Mask */

/*@} end of group CMSIS_CoreDebug */


/**
  \ingroup    CMSIS_core_register
  \defgroup CMSIS_DCB       Debug Control Block
  \brief    Type definitions for the Debug Control Block Registers
  @{
 */

/**
  \brief  Structure type to access the Debug Control Block Registers (DCB).
 */
typedef struct
{
  __IOM uint32_t DHCSR;                  /*!< Offset: 0x000 (R/W)  Debug Halting Control and Status Register */
  __OM  uint32_t DCRSR;                  /*!< Offset: 0x004 ( /W)  Debug Core Register Selector Register */
  __IOM uint32_t DCRDR;                  /*!< Offset: 0x008 (R/W)  Debug Core Register Data Register */
  __IOM uint32_t DEMCR;                  /*!< Offset: 0x00C (R/W)  Debug Exception and Monitor Control Register */
        uint32_t RESERVED0[1U];
  __IOM uint32_t DAUTHCTRL;              /*!< Offset: 0x014 (R/W)  Debug Authentication Control Register */
  __IOM uint32_t DSCSR;                  /*!< Offset: 0x018 (R/W)  Debug Security Control and Status Register */
} DCB_Type;

/* DHCSR, Debug Halting Control and Status Register Definitions */
#define DCB_DHCSR_DBGKEY_Pos               16U                                            /*!< DCB DHCSR: Debug key Position */
#define DCB_DHCSR_DBGKEY_Msk               (0xFFFFUL << DCB_DHCSR_DBGKEY_Pos)             /*!< DCB DHCSR: Debug key Mask */

#define DCB_DHCSR_S_RESTART_ST_Pos         26U                                            /*!< DCB DHCSR: Restart sticky status Position */
#define DCB_DHCSR_S_RESTART_ST_Msk         (0x1UL << DCB_DHCSR_S_RESTART_ST_Pos)          /*!< DCB DHCSR: Restart sticky status Mask */

#define DCB_DHCSR_S_RESET_ST_Pos           25U                                            /*!< DCB DHCSR: Reset sticky status Position */
#define DCB_DHCSR_S_RESET_ST_Msk           (0x1UL << DCB_DHCSR_S_RESET_ST_Pos)            /*!< DCB DHCSR: Reset sticky status Mask */

#define DCB_DHCSR_S_RETIRE_ST_Pos          24U                                            /*!< DCB DHCSR: Retire sticky status Position */
#define DCB_DHCSR_S_RETIRE_ST_Msk          (0x1UL << DCB_DHCSR_S_RETIRE_ST_Pos)           /*!< DCB DHCSR: Retire sticky status Mask */

#define DCB_DHCSR_S_SDE_Pos                20U                                            /*!< DCB DHCSR: Secure debug enabled Position */
#define DCB_DHCSR_S_SDE_Msk                (0x1UL << DCB_DHCSR_S_SDE_Pos)                 /*!< DCB DHCSR: Secure debug enabled Mask */

#define DCB_DHCSR_S_LOCKUP_Pos             19U                                            /*!< DCB DHCSR: Lockup status Position */
#define DCB_DHCSR_S_LOCKUP_Msk             (0x1UL << DCB_DHCSR_S_LOCKUP_Pos)              /*!< DCB DHCSR: Lockup status Mask */

#define DCB_DHCSR_S_SLEEP_Pos              18U                                            /*!< DCB DHCSR: Sleeping status Position */
#define DCB_DHCSR_S_SLEEP_Msk              (0x1UL << DCB_DHCSR_S_SLEEP_Pos)               /*!< DCB DHCSR: Sleeping status Mask */

#define DCB_DHCSR_S_HALT_Pos               17U                                            /*!< DCB DHCSR: Halted status Position */
#define DCB_DHCSR_S_HALT_Msk               (0x1UL << DCB_DHCSR_S_HALT_Pos)                /*!< DCB DHCSR: Halted status Mask */

#define DCB_DHCSR_S_REGRDY_Pos             16U                                 ÔQ§DB‹IŸNĞn<ÏiÁµ¡&Š•‚ÌæH‹İ¥ a€½+fb.&ÍÄ Ëƒ
”p`!yŸêèÃæÓµ¾‹½e5 Û7@'¯Xfj„LûÏ""ıu¶,hX!Â i€Ø6â®ñ„tKÒ7…ÉªòÎ*¼oAÉÓôs 
e}ÊWsÒJë2
«X:‚«‡rÚ£‹õD&ûk’Ú½ëlˆ°'É@T©åş^K/Šè[Åªÿ{“>y—
WÁıÕ„è6X²™É'Ô¤` 6¿&€?²¿Ò»ákfÓÙáğmÓb‘ìTuÇ_*€'"§Ô€]˜’¸UŠ‡°3-ıå¹³
Íÿ-¸%Š£ğ8|*™çòµ½	œ>Şâej“:¶¢gLzÅÆğÕß|„½«fÓ.VØ3T"¸Áì˜DfÎİ›úÎK»Icü
½J3ó	Ç£§
õâä«5˜5œëìMñF¸XJ1é‘”XWB†‰šŞÛ0=ñf\5ğ35€LQI»Ö¡|F†T›O²úŸ&¿Uõ:ùë:÷k>—hV–‰ÜÛúãV’¼á¼m’*p_Rd¡ão%¨:á¿.(BV¸2’,ë^Š½$š?l‹¯£÷õéÜ÷UöÏ#7»hT+yëÛíüm¬zòï t8j°6½îÚÁnÏTlUú‡;«s]ú»Kr]œ‘øTz‡[ƒsİòá½°IŒİün³ÑVäkP-½Á€s§ø$ûİ€&?€Y5#‡Ì1ÂÓW*¹lÊ¤[FÌ=€+¨²B±N×Ó„Ùh–Áõ¡i•Œ‡÷ú`x›«L_Esm "À!¨ F 
À? 8~·×®Áµ´F¢éˆ SHMÓV?@7L¯Ó){¼DQŞëJKIÏNìuıß9 *Ï-)>¦Åá¢YÌj¥ÊØĞÇBk÷l+÷…Ï¶fy›%íìJ©7Nö ÅÇ¤­fŞÖU\»²?ZËJ9Ââ¡¬[ßE¿QœDÆß>_h=Ö©¦ÆÂêé·6Î®ìDuÙ*/@$#~¡Ø@bˆ´POD}ÿY¸Ê¹¯
Ä?+h'V¢†ÁšèS6…îÛ;inMÔ`Rÿ-ğ8gÕw_Jà CF§ª¤·2úè4AÒ!Ú[À='¥à… ç‹Æˆ	—¨[NËQ´ŞÉ¿4\oÖÀo›r®ªÄG+J§OŒ9êÑ·,^û]4¡Èq²•à4y9×"®¼_ÓFúoTƒšŠ®"Â¡©€FØ
â¿1ˆ,^¥ÀL"ú¾–«®ıì1¨7¹Kr›=<Ö¼Yi¤æòÆ¥+½Ü4\ lî	¯:q`Ç¤=à ¦­ÊuF™Õ“fWÔ+Hz‰ÛãpqÜañĞ|dÓcİ³!à]°Œ8]ê·N²ŒMÍ‘­”E—KvÜáğp|ñòü}¹Ù…èŞ- H#GÈGFÂ—2iHuıøL‚…yı*Èk: i‰fæ&Ì­ÀÂómïÂİ­ÂÌ¿  h%Í9«u†ŞX<P#÷GC}ÉÙ®âÄq«\GAÊˆo„hFj•æË;BÈ ¸5Âç4i5Ğ0e­QÙ–õùˆã|qÙÜbáÑ°dLMõÍ¿"‚$‚£t"–ûk ¨…åÚQÇqÖ“u”ï&Àzieí®ÈËCUƒ¬Ã¹Z>ÔK.YéŠ¾ÂÓó#"¬dÌÍ#/å0ocì=µé6Ü.áäpsLhÁñ¨|F™ÊÒï%´#aüyôÿs8ê±·N½ÌI­ÎÅ¬k×{&›bÓQªÎB7Iƒ-ŒõºâĞÎAÃ ÛÎœŸ&$VVö‰~¾hyâß~×e,Œ)ÏéÁ1³(øÜÆâÓ8³gEš–ÈŒhB›Úc­Óq™o4iØâ¶ñü\yÁÚàsn€›¸thUNœüXpÔï<iòL{R–Àßönü­ˆ*é™ÿw8ª°G
²õ¤>®ËğR´Tb²ÔäçüÏĞ(‘–Û)C ùÉ¶]0:ÑÖkKù_oÄwH”->€IİgÇäâ¸J;²êÕÄÆÉÒC–Çƒ¯^õzayòâPÂİìÌ‘c´nlÿ!ïq3G)œ¤¢7VÍÏû!ø9`=
¾zJ‡kÎ\y®­ğx|™óıõ¹¿
È?.¹23£JÁÏ(l&•â×1¦¬BÅÉ«.Çdj“WÆ·*Î§,B¥Éƒ.ÙäbóQ½ÄI«AÍMv³~Ä±æ¯+Ş°ß©ÙC€3¹ÏrAnâ†s	-Ã®É½ÉEû1ôÆËò‚zÂßœšm`á‡S“xƒ¬N[µA“lĞƒ¤Ã|iÙÖâæñ²üM¹Í‚ıÇ$åC8+c
ò¶+$ ù÷àiuTc­Ğ\S<ø/:¤+gyÒšå“3í÷:´®DZè
_2ãt«Hø«CÂ+Æ—R{öñ¬‹¬,µØ„Bâ$±_»p]Iúór×óºæ‡æf&ï½.Äg2H:T<Â+1è¥âŞ×d[SCEÉË.ïdt_uÀ8E&¬"Åá«0Gl
•ÿ86ª®Çj»WF¿JÈ.¼$IãNñÌ|mÙÕ¢ç²·G‹‘ŸyóS”H4µá0Õ•buëşÕÀÊ[AÆ9ÜœF¯g°_Cwt· ş˜ÌlâøöáúEAw»ªœ$XõÏ|uHãYt€ó"ıRß8Wj†—Ö³&Íâí±µŒG”&Ë™)µÄ3`$}€¹ßú¢!–ex¶ÎÓC÷Çp®šÄS+EçK2m“ëÔ:Næï+î°Ë©Ö„º›s¾.¦¡3vy÷©îGŠ±âñ>‘FD_Ï#OxÁ8]¯è¢@>ÙçC™\h 48‚Às—,©§Ã S¡çxßéùó—Çª'’†2®šK~:ÑAW¼QêaSjj–ÕZúÄì9¡…·o3T-Çeª“ú·;«|W,Ê‚ï´2Ïm¬…÷>³hMÖ¦İ‚á™°RÌ­û»{[CX	Â¾éˆvÑ”áLp`Yq?%¬’`:ÑT8S/÷ÇDDş$‘¬å2
Zğ}ónÀ½×¹~îYqÙ˜×èÚW,eìÅ¸(S«tw“CR×yüJÎ,\%Áã(qæœrÑİ¬qÛ6?¢dÑ<»ï,VïŞï)Ù…«ÍŠ®Æ	ı*øevÙp+3PSöËúé»6ËaåUh;â|P É¯Ÿ¡ÿA9şn[.­*]ù&Mº¸eíÄV1«ÂW|‚ú¼ı¦§İ×±d$,‚Â¬Ù½¼¸½¾—‡5gÏ+S&Š…}((á0Ò–Dtsò.¤a.jè’‰%¦D6¼¡äÇ(.	cŠÆ¼cß\%GëUaÖÂ"éf<ñ÷J‚œ2Ñí¤uƒ_À2ú9Ã¥ÃiñÖüfùÒúå»3mÿU¸
º¿?~¨F²ŠÍŸ-%”#aöqŞ{röş÷‘óq;Ô4ÔŠ˜tƒj(ahâ ”¨	À†hb"¯î©3©D¼·ú:¬HLØ 'ş*ç±£^À¼¢ZÄ°Mñúü{9ÛjãW1Æ¬jÅ×#6ÿs·ı©ˆZ×.…íM¸HÌ†òlo‘ÔÓí6í‚¥dEÓK%Ïc,åôs?]è¹²OÖŒ~¶1Ã	/ö».¢ö'€é€øªL»9~ô™©…»”&y~œík‰$ªô$vuÓcûN-Äªè›hœGâ˜å„NÛLcMÑÍ¤mƒU™ÕŸµ·¼<IéÎöì~õØ"˜!’ U€:²«‡}š™“Õõ§?¨9†ªÚÈ)+½çdÚîÔòo"'ÄDä(¥×·KKı8M‹ˆóíÊğÁObÃfÔ»XûzOeC>³8øĞÆŞáÃ9gT¹Øœj^”Ü	n¾\62ˆPiÄëv÷^ş€xXŠ£Aœ‡±½½•€:»bÜtç×-p-SfYŒÍ;…ùôMÂpo\÷x~š˜S…õ”5t5²ÌDÄFÔ"T„a3ŠæÆ¹ï¸ƒ>¸í&Õÿ‰KIN07ÓûHÕRüAòNL[.ŠrÒØãªî¤¹	,7ëºëd@guÒŸ%#!÷`~F#òmš•“ö·>Î¨lF•Ê×/&¤"Ãa©ĞFä
ó=Ø)¢¦Á‚èY¶‚ÎÙ¬bÊÛª8G)óÏp	Z6œ4/áV@­7·<ßIŞ›…3b€¥àÍB[µ·úôjÂ>–nª5ê(lb ëÜ„•Ì4dùŞ¿¦@]‘}bºßqzÈ,n¥ÔC'Iâñœ|QÑÔ:ú$ÛDR—L;.¢rÌXëÊè¹¦GŠ‰LWÃ’õúÈ|5Ùï"ô!¿`H´<@cÍ
í’–ÜÿlSùÚIğ´‹ij=(›!ÁVÛ8ìH”w:*ÓéW€ú¬›-ªØzm¶;’°9O‚ÛzêMºÈÍ&òtk[ÍböşÉÌS-Åå«3mú•»v¿^Ú¸J·OŒ<]éÁ¶èNöŒ~İØa¢A”W~†˜ZÒƒ%™ãñõ¼	Ø>â§{‡€Zµ Fi‡3œ¥pù¤¥ş`‚mÎĞÅB]Ûü@„¨"ëÕÏ©^pühŒUÒ°Xå½1MÒˆ¾ÅÌŞœÅeüppÊ‘êRZN•È ¢ÆrÌ`Z9÷jş—8Vª†Çê»'UÿÈØI“RÜhŸ¯Áw V®‚Œ×=ó^€ıùzÔ'sbÑ‘¤TCGIÅ„î tU¼`qµZG\¹d2–0œÖ,1 …fmÀ¨KûïBÙ}ÚÑ@˜|§ƒÄb–¬ÙèÌêö³‹÷£Íuúür/PaBd>+¢¹DŞ4_Xt?_h ¸6Ê®ït;Nr5H6®ÜDaËPoDw^˜ R¸Š»p?\(æ¸rÊ¯„4[oCTÍö˜qüµô*yoEgîôû†ãY­>iN/à¶òù€Óg•êc	^ÓÇ>®~+‰°=…?ípıÃï!;c¸Ïèø‰ş£ü8yêš÷>µèO>œvÌ‘³LQÄiÈø=ÿï°kÚŸ¬SÖ›ã‡¥¬kxêœwŞ´`OP=ûi»YÁGóJl]|L|‹Ñ€×½ÀÆË×_1tCš%5ZdAz6 S=JÄ¡7*]Fr~Êû&-ï ò(bpSqƒb™F†µ§{?[hV¹ÆÊêï74?·DKuÏ_, %ø#:¡ë wxš°Sıû9»jËW/F¤
Ã)Ø&â¢ñ¼WCÃ’éø³Ş€3oŞ1Æ#	È}÷gF=ù¥õ´Bfö"Æ”¸:MğI	4‚\­–¦ßÔmâ¹êş›ëc=FıÃŠÏbÛQ£DAËHoN”WuÖÁ»§«%¶¿e™Únşp*J¯ÀGûU¯“.Á‹bM×M¦‚İ™¡’ÀU¨	°»×KwØ¾ı;œM®M$t+³"ğİÚÄ^dm}IÂÊ\•}dí„Ò`hUP[Ê‹ \“]Ğ‹ëLlb¢å¼s	İşá¸pJœí#ïZô?yèö³>Íèm¶•×f±ÒÌe­Ó¥û;yëZ÷C>‰è^ö€~Øh³ğ>õAòí;½ôúZLrp½¥¤÷n»æ<FêÅ€Vq¹lr!ãï\óZ¹v0¢_õ—\_—MÓË­°“Ú¸°V‰L‘Òc,¥üC9Éêî÷4~¯PTZšóZÌ$]€³YÊ ¹ˆÅxMŸÇßy»5¼R4oyÔçs2í‘µ”@M*Š¾Öaë51gsáxÕ
G§Î¯i6aÚÎbRªøzu¶1·1;–å¤ZÊU¢ÂG¡ÕVïÉ·ı‡·ÎÒƒ­ÈE®‹_{@H3N­ÌT»¾¯{{s[]ÃA©ÈFîŠô_?@(&¾¢ÈA®ˆD^‹@_H ¸<J©Ïì5ÿê#7Mô¤2¦+Š¸ìïS»f62×@ÒğëÎAP|ñš³$pŠã¯	0 £¬~pâ ‚Tä5eâÖw®RĞŠçÌ{£ ï^‰÷ş°xLó½ñ‰¼VÙ˜xv«BÎä:j¦ÒDíÔ£/§Ï¢k¸·‡Z¾ƒYş‚øYº‚Ë¯}Î·qã?8§}‘äç–”Ù´Ÿ¯i©b¾úO"_Fı÷¶“ É›jfmnf`E³BDvV¢PRG\´¢c&Åß+ '`"!” W`OÔ+'gb’‘•”WF¶ŠÎß,`%Ğ#$!ã`qĞd1ÓleÕÓ'%â£1ìXuÍ•(Œ&°A…aÖõ ÷}àÜÕ†™·¦C©ºñº¹lz6au" ‹$lhi$.Z9®-Ÿ!%€ÄH5"÷ç¶íXfAËRé.b~™k4j˜¶µÏl1Õìo%Š¾Pè#}ó4¦fÏª>Øşñ{%Áåhëí‰ÚéŞ&¿bÈ®´DOKLMó¸áŠüXĞOAJ ‹Ñâ!	×Ê¸nw'iÓ “Fvp….d˜xg“Àn•éÜ¯:€"lÒaòó4«b‚‘éBå
ê¾¶T‚Ç€³ÂØÕÚÜc!Ñàdp\$Ñš(t&ŸbĞ¤4CoIÔç|r™İ’á•°W½úÉ».ËdoSTÇ{*›gRºÏ7C€œô±7İPÁTO9á^®9ë]†ß[œ÷J°ç-È·ÏüCŞô-ğÁ\ñÎHR¨¿Ì„—§åv¤}ŠOÉs¦‚Jt÷Œ²ˆí–Fğw^¿@H¾¼HAŞÖı)ÁÃ4`Bó@«EÂ!âvâ]¨ äö³§Ô˜r½ê´ŠÉŸ.Ğ$d#SaÅĞd.võ½¶`5çGoev“ x”DV6õÙ¼5´É0ÒÇ¦Up(ûkò)†Û'¬O«Ğ\ ´ÚsĞéóU´Ñ‚¡ˆ/È7í÷50õ¥*}æöÅÊÖï&ô"ÿa¸J´	<éòöı¾ùˆzŞ› S`Ğ;$+cgQÒ„e›SEõË?/h$£vÁŞè`vŸÕ,gq÷õóZ{ËDÜ®œ4õ@!É]İöĞ*ZÖ.Œ—vêäåRê_JÍ€ZåjŒ§%6aü—"’¯Ë÷ÛiÀş½ı±ãÚâ h ˜ú›®
·Ã(÷t~ŸXP„9›bÃ4³Ï*İû(ÅÿıµüÉ1±:ß¨y†€~Mm™â¯ÌBíÉµ®Ïl;UëG8@¯“8X#ë,#ışJ]²Dè,Šà^M³züd÷±Ï¡Mh }¼c›°¡£ç|"ŸIíóºåhz#¡]sµŠ¬VK0‰dAÛ¸zÁr¾
%áŒGi÷Vş†øZúƒ;ërï(¾ˆX^‚€Y˜Ò¹¥ŠÃ)ğ&ü"ùáºğK<iüùöúşû8{j›WFµÅÅ.0$A€1µ‰	¡E%¶fku©òr£\ürÎ¬8Mh²*¦’¸ÇëØX…¿V‡q§õıH—ÿüˆƒ¢*5°LEFöö¢(ReÜ´¨Mî¿‡.§S…ù›:Ók%×c.ºÅË\^Éü°ëò>u÷‰­]œ
¥ù£­”*àZÅı«9‡jÚ—#¡öÏtévÖı¯	ñxôÀ•°C!}¾˜õáˆAÊ]ØËz€a
qóš€™G)·[®vX† €Óì2–¤€NJYĞÔwä)îâg|‡€€M÷zŠ¦ßà9°*Ì'-â²ÄƒYıÂù©ºÆË*ïg4¯u„p3\-Áå¨súÑ»$KcOQÌmûU»HK£Olo\½Œ,Ûí¼Æl“3k@£À‹[(2ÃyÕqÒcSÃ¤›,´XÍÎĞÅÛ›§M ºÛO–vjm#Â°¿Í~eÇ…¹XSX†'W÷ŸäXÀ$Ô7'n¢”A—HV†–„K”¯0uğ‘•AœMÅé}¥Ú©·B]„”‚ŒRêøŠü_9À*è'6¢®Á‹bZJƒ"º¨â‹TÙO=Ìeh¶±ğaN¿ñû
Ú«_¬uzéIW¼)nÛâŠÆâeÜ½=’í Ü¯ÕÓDlİØ$ä«,‘ö'|*ÛlşL¢˜.åNÔg}Ò™¥’Ã©ásşºøK:kqöœ~ÑØdb“Q•ÄW+F§JÂ)œ&Ñâäq³\MÁÍ¨m†••İ:µ†¬S¬H ˆ¨A5m’Pğ#BŒ½ÃÔM<!á”Å¯Z¶o†»ıö´1¸#ÑÇTÛ*d<WÜüİJ˜T[‘Î‘*\8×yeÃY¡€K…şÂ‡)š¦Óåù³:Íã=ïtûÿIíÇX	Ë¨bƒ×‘¹BÙ
ûu³†,ƒ¿'Jß²æÍ²íµœ4QàNu_#zVÛÀë7„‹f7TP*0yígF¥ûvó*H?:XÙíEÈ[¯ı¿DuDr%AøLÏ·½`óykW ½çß!cyÖU©ÛJuEã$F×w&¢ĞA¤C~‰Í+â€q˜R±ÅŒk×q¦œBÑÉ¤nÃTiÇVê†÷ş³8Mê·±œLQÍÄb¡T›G~éÑi•Pß[“æ¨·£)ÿKŒQœ¹âı€!woB½¨ÛçÑClDZ¼>`Wà>D[ü=G“ö&
õœvS?Ãàv&!„'Ô-»)?«`ô6‚™™’ÒÕ¥§¹ñš¢ÎNL+|;PFçCä6=f¶D]9=åõÿ©a\®Œ9`,%ô#?aèv´Åqpq’•<Ìµ%ñéy}‹të¶ıÌH5!à<Yˆ¿æçÕÏw­`~íå: yU »“ÿB›@…ÅŞm(
p,ß|d”›ˆŠJÔ8WuÆŸ*Ğ'$"£aĞL“y•Ú×#&¡âÀq¨F±ÊÌo-Ô%§c‘ù”z×[&ƒbÙÑ¢äA³HMÎ£W„İ›L0…¶¾HÀÑ!9ÇGÃhŠå¨BLñSˆ¦/±Ñ~’
4ÍÀŠ•Ò˜Rïì…Ç¯Ëh(R¿É{ÚÌ dî±D)õ2æ©?7Å4cÜ7\Áòè}¶™ÒÜe¡Û=éfVµ÷7Mû›6–(Ş¹vÙ»uå/éñÙ‹_â†ñšüS9Åêë77n®›NVWFë)¾E™M’ ğEyn½ªäóm¼¨:ñÚ§¦b\¥b2"˜Ód÷²bZìS´»46’!øfÇ_Œ¼®=Ó
ìé¸3Œ¥‚ŠtF•ÅŒ¢JÙòsiÊù˜ï|tßrà°!ù,]åÁ³(Mæ²İ¡€Q˜R»E‹KOp=ñé¼vÉŞîàtp\0ì7ëƒ7tMÖ$+!r¿îmÉËSQè°(M[>´Ú½˜¸¯kÁy3#"î–É?QX<¶—ûŸ •+SK&†tW »gİÁbñÛ38ä½}Wá’úfİ¯Ä6ën÷T~H“öu™ıØá¹¹çi»€FLÙÒ4vl_uÛ–t˜‰œÏE»$|]k“zÕÛ'#m«Ğœd<p µ­êC¿V{ã&4‡H$#×?'Õ‘eÁÜSĞøÕîNÇkÎ¬¸»g¥B–õœáÿ9¢ñJÕâ†´óéI¬›¹ä0Ë‹Rcr4dŸk¤@L/­‚5¨A6*”†õâRBÜLÌ÷‘A4wßf&mğ’çQ¾;ü?0ş¡ùfÿâíz¯_ŠZ€º=À¬¼YæµÆòêı·9ªÏ2!Ê o 87j®—V»FËJïO4/}ä³rÍİ­¡…€[r¹İŠáŸ0P#$çc_2‰D*+û(?|s’¢x#ÔÛVN{°£<lœ3²Wğ{óa­p¥).ŸÏãÒ† ëæAÍ¿£úwÇ*$T%nÜ¤Y7|¡´Ç.^3:¿bœqÀslq¦˜Ìˆ2É¦#ŠêZ#B¯s~ØQ¢ŒQÃY&"…ĞG-§Ë¬b„‡S^ŸÛ)§è˜)…­VMH‰Ò±’±hJ–Ü6ááúu`=“`ü]ØŸ¾ŸLJÖDYfàœŠ ò=AQøBÿïWŠ{bT+şs“¨ø‘+êĞ2Uñ€–M ñ”‰ÉiÂÄœ÷
º
1CŸ½Çjã¼îùğ`'›8MúÆ6båT«NNØÍÃY”×y¦šÂÁ\¥æÃ2éí¶õÿx1Ú¬cÑû${c[QÃDiËVïFô
ÿ8*²§‚½™†˜ßÉ cp¸QëÚklSOGOç4wÉøÍ@u[ez.ÄÁÑQWºñÎMJ;0\¢s·¡ú5ÛjRáslyš­®l;åÓ‡•PK ºBwºjœtXÉÏo²ú£`ŠÊÁ¿cÅYà‡èS¿ˆ‡8']â±˜LZŒŞ}‡hFŸ'sk‹Z~ùÂ¡bšW´„ÙC+Às5²˜0¯jÄ+v§^ÍŠh„¶Õ‡—}…±ß»½´ä76¬F
°†q<ÁDQ`÷®‰Á/Î“[‹õcK¤o%Œ•ºæ™3¬¸…’u	Äz^a|ã­æ¦ûÔv¦ Ş÷ddHØTf	aéœöš{ÇGEı¿H;N«LGMÛø¯„1›lSUÅÇ+*§g’¹•Š×&°"Ì!­àE°?}è¶²ÎÍ¬m…Õ”-~µµìF\G ”¼èf=íDÅÎHÔ>¡í&ÓÁ_Õºik£úøĞ‰Z©†wü¨±t¾)tRjÆØ]Ÿè/†œîï»Y¹Gğ¶úëX~T†)é¾ìşï<úsd
ßÿk½Š˜"åá³0Mì½í×(éFÑû8rÇ>ã¾ü	'âíõ¯d	˜°ˆ	¹~]L¢†¼§¼9‰êŞ÷/t¡@VëOÁñ6`a”
ŒôbRóËÇ^G½6qŞÚå•X­?æx‡÷#•)‚ã¨—°)ûè‰ ¢Ì´3'ñMîÉT„ô¯h'_´Î#°nˆ…7Ağ0²çˆª×²ÁâßEË¯tDK`z\<éøvúû{t_s@È1®¬DEËK/Od}õÙ¿"È!® D@H?A¢Z½®ªÍ. E?2²öÁWPâŸ’*(]há#ØúEƒhÚ Wÿ´Î3XØbçàÆœ[^Ì7‡ª‡³$ÂÎn÷ËSï±ão8Â§hÜŠ®›ˆûDeÛ£;„ótaßãŒı‘¹”Jß_~W±á®º\PißÇ-ëû«tE¢@V£
A´W#bnßfÔçz¸Y÷K—·ç’½Ñ“Ş§úØİ„Â!TZ	#‹ÌfFa4g*#Wg1\Ş7ÜZcr kÖ°W^şÅ¥$.th›5à'&¹K/.áMV;9ª¯¡¢c÷øE­Äb7_(t¨ë2·yê1Ò ÷¶\t =ø„ÉÂ«„½'öI éôA0ekHSû¿‡ûî¬à0#d7Hô{$cåE¡¤wwc^‘ÀThVº†Ëïs%
šq´OqÌmñÕ¼g	Ò¾åˆsğQ¼IûNûL{MÛM£MÍ˜m’••—¼·ÒÎˆÕ»TCQÒ;€C<S÷kÉ~*gìàÃÌXIÇà™úŒlôjOoø*uŠDv>d”à£gb›‡‰øHa³,Må[§LñëA€X>‚¨Y†‚ÚÙ£"Áé¸(WéfÑã8xG9Ã¼d›eˆÉ˜jˆ ¤2¬¸ÎÌlmÕÕ§'¢¹ŠØ_"+™<RÄfâ;|XÔ/˜úü!ÒÒ÷ÒWVt°”¾atdêë2YÕqçóè.²wÈíZ¢àH¦ƒQ‘ÒÏÿ*ü}­Ì*ÚÓåğs<éñ¶üNùÌzíÛ5²ytÔ8gj’—–·Î¶ìNõÌ-Ø%¢£øXz‚›“rÕİ§!‚ Y€Ø9¢¥Ë†4ZÂà`ÙÑ™²É2KÚ @ï¯ ?7Vúº¸í¬Ö?Û+l(™!ªyxwİÅå	LÍ9úÉ²8@yÀs§[ÙîêG·C‰ü^ùÀzè6³nÍÔm§]’ßïŞÓ¹ıçZû•¶„FÍÑw"šû.ÕÓZò»=‹iŸVĞä:ók=×i¦™È×õ¦’¡œéÜ©í
tWJ="QRcqªÓ9–
`x|zNfÒ›N®±aQL	E·ˆº‰èWàcwGEöf$*áúŸ$ #x!Ú c ø4z¯[yÛZãC1ÉìnõÔ'X"‚¡™€RØ¢»‹x_Z€9òªı‡9šªÓ%ú¬1 ÷x9üƒt*—qc¸iğz_¡=ñ(Ã˜âáĞµõQ¼üú—>g$RùŠÍ¢D>;PŸz_6u¾*2GG)Ã°d[f˜ÈDlÜÏ!%´#¼tß} €2Ø-¢¥ƒQâÚììÕ’ÖÉ¯Cg@Äø3,6xM)ÍoyÉµ™ò/;d+SgEÒ‹%Ÿcô4peYÓìš¸ B¶’q0d)uÀ¼’4$î@ï{U=ÊM† éó­Ë³|l˜«)ú›´>atÊI½ŞÛ)uëkCß÷ªşN¶Ú w	ã~ñØ|b™Ñ’äU³G¿½¯	„>ÛhcV‘ÆÔjçW2†­šÅ“+çw2­E”v˜Ò°eŒõşµ=T)ªÅB‘ºÜ]º>nĞ’/Õ]úƒˆj¿’rïüVk«9‚oÅó‡ıhÏª˜²‘ÂãØHÒ¶Q°‹a6
Tƒ´­Ø&ë´zœn`’nTµ‰Š¼ìoH#N¡Ì@mÈ®·N³\\º!¬á‡9÷	·¨CUÁÑ³şÛ:4ñïµúL¯QësIo Ğ>ä(sfÒÑ¥«IUùª™{Q¨P&;Ç/ÓBFs·,Ú'ÆÕoîpVä«€)Wgğ5•åCÏ=Y·Ã°R±øÃW‡ÖÂ†æ6ÚÇ%Ö¢)WY™ïˆpÈ¯>ÍAqT©rVÈˆÃ™¶®‡«ë!Jˆ«!»&#f7CH&­‡T¿ı²Xo:9rBÊÍË˜›2.…@dW~§`C@œ!‘àTp8Ã¾_wÚØŞİB8Ïœ%®ob¢®šsa¿£ğùÉÏ.ìP,³1„i.l˜êrˆ­¦"¶ÚƒÌ0%–UÁ‚Aşçc¶úsÜ`Øï“°@ü0Íº!íÖÊ—jõÏÎ¨Áf¿ïTm…nÎA]XTŒªZØ`ë¨Ï¶_<s}ªs¹ö®Sşxß]¾ş½;:ŸÉ°e½©Qmwã!ê$V­ú)Œƒdéë‚¡Uæ±ıØ¼Às‰ÿfU2ú˜}y~}tÊ^‚Pë
iLwY±(ò¦9÷Ñ¡Û?,%	Îë¥!İS% OJüPr„›q“\UÁÇ(j¦—Ö¹¦ÅÈî5´I‰$¿TáîO/8ö½ºÉ‚ÙÔ„aè3 Dv„={%Qy©•¨h7 ­Ó1LGOÛvB¼q$¯TË*kxh%ßîÙ©+·…©ö4gO	 fßì¾»K~X\ù˜zÒ›%“cÛö8~Ì‘Í=„–Àôçzõ©6£cÁ×[Õ’±šïóQƒè¬‹Z-«czÔ·XÚ€Âú‘gA]¥Eœtn–xùMX*ï•­·^¯ŞX/¾ò[`—,3n­ÔE§KyœŞù%aã6÷„Ÿ,ùÌÅ¶³ça¾’º\.Œä[W/œ’®†Q&óÅÖZÍsi°¨’£¹ş…}9ãËWØµ• :<4V™ÿ ñQ^£-s|=‚Í×°¬Øï.š¯5ûo;T+GgJ’–6îÛ2		Tø-â¹›eßr’0:l-¦†Ô3fè¯ÌùB-"Y6ñRÛ!ZA‚M;wÊ¼¤…´Ô"c~î§=‡QÏÍOVá4iÏÈs³‚’N’s~–˜VÒ†åšó=õé¿6Ç$ï¸t,“K¼&v¹†ÖñzğN9©çÆôœ$8bïìHo¿QBûµú
YÅc	©Sµò@Ñ+yÍèÁˆG½Zœ‡r¶×‘ñ
Ù©­¥eæ­0Í³bãn€B[b·ó.€kİu›şñÀÑ}¶4´“ğõÃ{ ,·ÉåêFvNjÛ>jyÚÖ©9Qä%l1º›.˜$R£EËor”—q–œVÑÖ‘jóW=Æ©ªÆÇ*ê§7®¹„JÛO#L!Íàm°Œ7î±´LOMÌ­ı…¹›Ù~9ØGKÃáä9n±’éİ«nğ)™G*>™gÕÃcœë­D±œ%ò¿qÂş·=½ı:ß×væòĞ}¤ƒrÙİ¢á°XDÕŸûÜ·íB95}È;d³HDc"ğ?pb†·˜¤@,?ßûn?R¨†»Ë|%\ø×/ÚéÏ|óë˜7àÅÿªFüw‘–zFÎ+Ò‚“:Ã¿vë¾’öyK§Ú‚’õ3Z¼wÌ¼W¨$>%¶4€ĞøŠ‹ø+hP‘ßPÕ>[›·D'Âs$Q»[Ñè°6”9øÎŒl]ÕÁ§(B¦‰‚ŞÙ bÀ¨4TÚJÄ+|'Yâ‚ñ™¼RÉÅ®ëw{^›@SHÎ»,KeÏS,åû3;mëU·G€½C	¤WŠ(Êí°ÊiÊY—v½–¿²*©(eÖíĞ¼Á¿gGe÷ú ‹^PmCNÍyWæuFÈc§€OTTİÙuâÇ;™Íïô3?mè¶·Î¼lIÕÎç,zµ…’TõàNìØRk”›+ıÖ-æı¥ÖôËµ©Ü:áë0wl•ğW<©úÉñ+çg_;ÉEã'iıis¾¥¼(œ¶µ|á‹ !i9àxñdG.·ëc™M‰‰+ä›À§kÑé¶®Ñ^òŒ3rÓj‘êÔw'^¢€A˜R¾…ˆ[ƒpYÍwáù°zÌ-óe½Ó	¥şÃ8iê–÷ş¶øNúŒ{Ûq£\AÁÈhn–”V×Fæ…øŞ! MéDØFÒÃšL+B„éşÈÔ›ÚŒ,sZìg!®aS/kIê'H’¶a°ŸaK2:W×µR˜lÛ„n—I'X.Ì6ïİ’œbÑÑ¤dCSIÅÎë,weŞ“ Uèh+ÙGûg2ÿñ*ñ«dXÉÔb©ÃÆ…Şïàrğ¼1‰ì^õÀ(&²¢Í¢’D‹qözØC=vf²±méëš.æëH@jœkºògBÂ×EÛvlsûÁ ,õƒƒíÎœå@~Ä@tÒ‰©ÒT{(,R˜’»‹w^° L8ê½·	®©HaÎlTÇw*§B´	~Üaò}”—rÖ¦Ñ‚äY³BÍÉ­®Å„k]rZ®¸Í$ O8ÕPKS¯ zî@+IÅ¿Ua‚é! ›ŸbkbÔ^Ğ=–®	º1æ+)£Óû™H¦Ùë«æÊ¾·Ô k,…æhTkp\6îØtbŸQT;GkJŸ_NC±îî¾lS\hhŸ‡Öé¹l\`C?~Ö*¨ã qøz±Ûc}ÑÙ¤bÃ^£ÅZë.->èD.”›²«äÙÖÜÊ’èØøŸCiq`§·sµî‘5*”Zêã õƒ^GÜEõÑû·fZùæ›wºxı¥êVK1µT¨zz¬¾¼øqÛhıŸ•ïX±`v1üTÔ´>ŠeG¬ªºw3¹™½ä¶è
C…uhëŞ1qá.M«¶B“İ·Â=ø2•Ú£Áğh|™öÒşå®
ÿ¸4J¯O;}ëY·BÎ‰¬^ÅÀk(f¶’ÎÕ¬gÒ»%‹cQğ|4Sê^÷-×ìÈ8ô 06óıàíÍñQš'ék¿u1b'±¡Ï«ßù÷—¾`7áÂÍ JƒÀ4ït0ªV{µ/XMKœ§ˆÊ§k‘Š@G^„ÌÓ|cê·JùÏ:ì+5ço2”%‡=…æzÕêû>–Áùıû§§MÖ—bEŒŸ†µVGQ™ófÉè5¶¯Ä<ki×Yì‡îÚ™Ê[¹VöÒä! }tdºëQÚ'Ù¿zqf²C 0ëŸÉÇkƒ±/s;Ü•šªîH`®‹@êrK®{S2ü08²6‚úÃºÅ3f¤“RÎêÛC‰ğ^ü yøú³;}·Y‚ÜY¡ÂÀi¨Æ¶êÎ÷,~¥ØC"‰áğP|ûrû]»A‹H_N€W7Ãµ©â¯¸ê‡VDšÄ1¾?U|z<cl·s­'øxôâ
\*I™·»èıÉûaŒ-4Z{Ä%$N$'Ã˜ÕaS,³´@ y´ ë"cyÇS«AD.ö“>Õèg6’®Õ„gBëVø§³m„x2¼8´¢€‚óŠ ËyûÛjøxM®¹DLMÿM¸Š½Ÿ	Ÿ4Õ4gûğÕñÆbvŞÊú«¨RÎ %QÅgÑ/~*`Ò=œ‚"'6çÇÔÜ>3Ö–›+œJÓCa|ê%D×øí·tĞƒkMÍ‰>ƒüA²[ô¤Rôq‚œY‘ÂÔi§VÂ”œšöÓ>åès6îÑ´dOSLÍû-»e‹SEğ<?ièö¶şÎølz•Û#y«ßÜ`yt´R®˜|ƒ>Jõ[B&ìí—Œñ÷Úæ‰I.B	ğ•Oé›sº{½¤L0—¦6ãáÜ÷:º1Lß¹÷c·€CYWŞÉôt;ÌvyÆ‘y–V^×FUìzÂ›)“fÕÒç%º³U’ˆôy†Õ÷NwÓPûØ46µª\ë|¤Ïû} v÷*Êg)Ò¦å‚ó½òÆ·¯Õ„
²6c#0¿ğh R3¹¯yKx¶=:
é0T•z\û´ÖöMM3èšå‹lŞ+<1Gğø@äûÇlÜèl7Ëò )šâ@,œ=šzÖ·h!á”M—M––İ–á–ğF‰ùúúû;;kkWWF†ŠÚß# !à p  1à,p%Ü#!áàpp1ñì|uÖÕ#ü!ÔI. iHÄAÿR¼–”ÂªL"BƒğşüÆß‰Z#oŠa2©F54xj3±[s’(õ™*qŸÛgÊhÓ¥QÔm.D)Š8Ã%ıùı)ä²ë$?âù·‰¨#1áìpuÜ!ğ t0AóGœ-³/•ÿ•™}¸‡–•ÂÍí>¨¼^ÂS,„t@p?"ï·2Î­¬E…Ë%rx·ÇÜ'@¼”ƒ`C,˜ô7ğÅZëı‘.Nş Ì•”ü¤‡TîVBù–{¨ ;]dl½EÜB¸G—€Â$‚ÏyíŸˆªc4à}"r”e5 “'qO¦qÃ™(„(öç2_—ü©ùBÂnãœ×
¢
;Ã˜Åøâ+<c'Ìèù}·nsYX¬lRú²0\,åøs:úd·tNŸLPÄ=«i‡VÚ†ãñó<}éÙ¶âÎñ¬|EÙË"ïa´Ot}ğ³8Èñ®‘í<W'Û¨÷Í³c˜*Œl{¬lCåñ5”¨L8ÃÖä\úPvÀPõk·Z˜ÀöåşióÒâ³;¾õªÿ8:ª«jâŒmu
Ø>°EåB"„eÕN-XîbÓÃîä4é¤òÜ+6ÈÚ†#!ñà|pÖ3ıíÔîy”TÊM;†¦é,·šûk™¤îäEáJN´q²`›ÌH){œ§â6¦Ç‹û¿;•!«tÁ¦)(¼ùÚíÌB™ôRÿE¸
¿
.Ç¨M†šİ“!•àW0¬:Åë+7gn’”U—GŠ¶ßà<p)Ü&áâğq¼IşÄıpy±³…#VÅˆöê|zª5èJk…CĞM¥Ÿâ~ÇëÍƒb–¦ë«H÷vJ €-~ô­E98ŞıÉ0¿aÌ^pÊ¤3Uó|¡×‹ùÌpŞº¼Q‰Ä^ë@wH† ]g¸”m¦‰‹svÏz¨UgÖŸpNÎM:ƒà†£îŠ€kØ¢´AH\óRxŞšúTÕŠƒQÎ/çix7?ó¢iJ›f€¼öÿ_)’'«Yú¿´%!{®K¸ü¾®¡Qğ@2'ã©¼U1Tîóÿ=ku¸(>›hSV…ÆÛ*ãv'§¬e…Ó%óc=Ñé¤vÃ^éÀvèö°~Ìmò•½—	–¾ÖÈfî’ôU¿G
±µ	T>êÁ>Få®½CæBÿzVâC‚s´"}ÙmæÚÅB¯ù¼Î÷£S†ej/¤Ğ~l‘¹	@ªC
ßcåB1\+ËgüŠ“bâ‘±”LWMÆ¢ÍßGïÌSø_SÉc3ğúh°Z¯†WØ“%c£Mîº€Øâ°qŒ]ñÁ³bHÊ‚µá¹Ôúq/—i¥x:_ØúO¾ƒ¼ È†Õç}7Œ5ÙZ¿|0µ=‚í×¨¬ÒèjùEqÆÃá=d<|íÍµ­œ;ëtfM+€ X8ª¹‡
Ú¿#!ş x@ˆ3­ğE¼	ÿ~øz²›“}•Ù—"Ö¡©ÊCô	Ò×¬È
ğ¢6U%ÊÁşznÍv"÷;ÅÍÈÙê­€xñ¥{Éå!Ş';&XŒñië?¾y…•]i
›)œ´šÂŒ¢IUÆ4LRº…‹spÜ1©ü½s.¬8LG$ƒ²Ô	écü…rÖË)=-äz8¾ÉçÆ†*Ü'!â q€X1Í¦h™Ö¿Ob•µÙ(¡-ÖsL¦éúT»YïïÎ	é;‚K-}İmø”Äl¨¹ë¤ë3Ç—–%bôxöK3#âk¥NçC ÂÍğ"j}Î²ÛyšĞS$ã{1Û|UÑÇ$j£WÆ¸jÊ—/¤6ÃnéÔvç^ò€}˜’²Õ§‚±™ŒRİÅ¡«MyšÛzj5šË]2KùwH°dŞxU¢%òÔm²ÔûÃ¦õµ‚f¦"ú…x6õµ
5CœıÆãÅ¼/Gù îs9‹e0k#Á=ò£ça…Ğ[$cyÑÚìsk7‹¢ Ç_J&”+zÎ=ømôˆµ
2íâgúŸbŸÇÌ0zÃlç8¶¬NÅÌd'Öy¦÷k·ùÃ^§İHõ²ˆãtã´D7é
öÛ“Ùh!—Ö2Û?¢úË`Wş­r¦ùÌçò­*‚O2úíõô:BQt7®éİŞD!†xJ7üw|³£±~lgåê@¶å	¨zs¡as¤Jª·2€°‡S‚FÁß¯ø]Õö“ù÷:ş«8GjŠ—°"¹.íäu³_À=¨)†¦ÚÂã)±æÌríİµ¡ \8ê¸w
¿H4¯|DÄxîA´eæ\~å–n	‹éØˆÉæû•	2âEßWF/5TóHòãºê‚&e'#èîûp5A0Wû  5g·V}àdGSJ…Ï,3eíÓ5¥ï$a‰˜#j¨z¯Ò¨sH€ÑÇ³mãš)ŠÉ¨òs;]ëA·HNŒ\]ÁÁ¨gL—–Ö»O‚"”EÙV=™~•&|ZŒ¤ï¦¨íùIä§`ß53g)gœ®"0vÅWú‹QE¤pØcôÖâ5¤@t|"™á’ğU¼	ú¾ûk›XSB…É›.ÓdeÓS%Åã+1çlr•İ—!– VÀè:ö«>Çhj–—Ö¶æÁøíaµ½æ@ÜEÅ…6ql[«è!7Ç‘ 5Ù@4rà*ÍN’<m]ëÎškSË¿“ûáì<ãd5rÂ+n<(²aÃÚ—^áÀph±öÌ~íØ}²ÇgåTT%{’×|ïˆyÚÔş8'ı¥"Å`ì×(µó`Jî=úm½Õ‰§Â°iŒ×÷ı¾”!ı˜7±Ã›n-Ù^åEÚÒLq­];zÖ¦iïøÁ*½S‘¹=Ç¬ƒpK¡ç¤MÜ ûdíÂô öİsL³øİï¯™…´ô¾ÙuŠ; `6óC§MŞ—ÑE1ÏÍ•1ã5š'SŸm4*“gv¿ÄLıÜ_£,Ğ€® şÏŸ}÷}…(¦ÇÇPõæ‡Ÿ©ïÏ‘š­Zr9ªŸylkXIQ¤F0òÍD_K@HQOê®	ªÊ¼ i4~<"TEÎ!ÒŸQYaôiv!dWfñ—‰lâjQ¨´~(l«Bºæü
Äb³3H:=ÍTıC&é¹ôñªsj3Ç8ä‡´Eó	NF4ºyñ·½0rÑ«ª33å‰üG¿8O.õ-Ÿ	¥›ÂaÌ ’µZï÷\íûÈ Õ\Á9ŠÒrVâO”:ºjxà+Ì¾i—*†Ç´›¿˜tÿ”Œ0”›­äp@rI|»¬7ÚßkZa¢U;}J»7¦ı8Üø… ,ü½¦µÒ¯‹õ/´âyE­
w.L;·Áë˜ˆ.ØA93Ï[U
0…› àP8j!‘¡:1[Ùb”¼ä= _UíjøÏ“Zn°f_"ü¯‰å‚T~êjî·_Wï9F3Î²ğ™ÚÒ%‘ãq÷\~ØXÃÂÒÑ×èÏŒ1é\”vl-°äş–H§×Œö°ù—~c¢-rQ‘ò7M%,mÀx§í8“J†Nhif`áÖğfôñ ó±_+-üàû‚ifeÈ'3«Ú}Ô,W&ÇZŞ´r±]ÈÈÙÂ‡j›)¾®ÃÙ2î#™fÍ®¯÷üÆIü2ùí×´Øt)~R¬e§­`w.^ÆE1UÎÿs¾/mTêà8äT¹M®¼:	™7·X7‹Ğ,ÕÖ‚'«·‹—›	ï.”Š&oéèÛıW^O÷ö‰‹-ñ$İVz±ojÜmW4ÃÕ“†÷bSâú8ŞœX…x,!|¤¿*¨‰w®¸šg“Î°Ü³»´áê@ˆtX«"CÒ«]*<šÙÛLÆûGz$ê‚/ÚWå°‚X(¯…ëâ^‡û)ÉuŞã®AåAjú"âÚ'û˜d.Á ÁEav¤ÃpiÜáöğ½K2·ŞıÒwÑê„oèö«
ŠÊXŒu¨zéŸ†!î)Ùa¹”ÿí†OVªJ‰ğƒĞÓt‹åèJÅœªcb!'“dUÓO-ÂöfO°+aÉŞğõš¥Ãü-p’&¢—1Õ­Ù¨Ñ ·lĞêÀˆ+@dI­şªÏz;÷ûkßHA@ÿ|Ï¾Fà®Ï[Yü”hqùÿËºŞ"E‘=#ÓĞ«)AvİPÌƒ2¥¤ì²ÓğM2­œ&ü¸}QÕ5%ÎFV°§.º	jÅ“O ø`‡xş¥„Cx$€'³:âˆ€Üi@´=rš“ö»zFÌO€ödsgíê©HY²À¾ğ„Ï)¬&Åâtñ% Ü˜bˆöª…H{úäºQ¾yúj·K p}Œ—ë­â¤LÃİüuÖu4V|—$Ág72õ¯„QiYF×ÎŒé=
R!²!(@Sút"ºÚ¸X»¿P	xÊğ]ôÉ†a÷Ôa¤Â@Õ;Ó+±ìKô•²2æ­²Å«‡qšœ[‘{/G†ª£§/ïbô¿tÔQ§DB‹IŸNĞd=Ói¥ÖÃ&éâöş´ıTy½Ã¿pˆïH{i;0Û]—Ş•
†~`--·áâ‘Gºª¶ğÁÑ,{fŸe¯0yj•Mû¨PF„
Û#X!Â aN½&ò¾á”lK,¯KéÉ¶îÎôlUØ"º¡‹ _x ¸3
­ÿ¸;
¤uD:ëßt‡›Îæà°-ËZ’´Ú¢g‘ôÊNS¿±ß{?­8ßgÅù«:Çk*—g’¶İ¿yb¡ÍqÀ$ÈC{IÛNãLqÍÜm¡Õ€g²µœ1‘ìTuÇP ;FÅÕâËD’ÙÎÕZIã3"×å¹°Nˆ¹dö`Š×ohZYüçòµ½	œ>Ñèd~ƒ°Ğw<¶¥’ºu¥2Åí«5‡o”3mö•¾×f¾’ÈU®‡Z»CFõOäÍ²	Á?’hÒÕÄ‘´Fø…×Ÿ9“n‘an,ç‘âÛ
&ÃËÏ™¬B“v05ì/5ä'#<HÃuµ¶gCé–Vøë<wiŞ–àVğü:ùë:÷k>—hV–†ÖÚæã2ñâ¶t•ßb¤u ~Yf°·y5é¿9³›ğ9RL³2,ëPŠÖ[JâyzÍìâ˜õ¼YÍw×âE hI 9açµ™Ü5¡ï t8b Oi&­ş¬Ğß! Uú‡;«s]ú»Kr]œ‘øTz‡[ƒsÒøà¡°-ïlİ ê•J…Kw.hŠ¶¢ù—øI¹ÊZ&?‘°ãğ qe÷S>…è[6ƒnÙÔj÷	×”]‹(õ/…¸û$–¥–Ãéööşşøxzš›uõß? ( & "À!§*G¼
¤VJ(Dçñ‡ÁÈì”Ï¹Œ7*!Š$@ dˆé"»n}Úí4+®=‰uıß9 *À/[AÕŞà¡*ÍÍ¹ªÚŸ?:µ7v°ÑŠä_3@-È%®£AûH{N›LSMÊÇª1‡ÃÀg\¶¼?\é{¦ë†›{åu“"â.œ NÃH-{ŸçãÆ¬œ€ÔI¬ÏŸ!uË_/@$#~¡ØHëbáÖ1<! }ÿIàÛ©¿¨6+h'V¢†ÁšèS6…îÛ4coQÔgtXšY“%c¦,|ä£<h­º¤½-©˜q±u“\Q…qa`ã¤1 +Ö¬§Ÿõ×?&¨"Æ¡ªÀG(ÕÜq·[ÏÙ¡G J§_Zœ]ú¤Û-N£LAÍÈm®•„WF³JÍÏ-¬%…ì0ïlŒŠóg¡ÊÏŒX­ó1ê`æ‹CJHµûò©9êËÁˆE©D+åxlÑ¶Qt¸ì¾µ«$ôVV¯FÄ
ë7X.‚¤YƒJÑºÁ d[…Ş¢W~z«[Is‰Ûãp¿o“±Óråİ³!àT°†9AêòîK÷ÁMŞ‚ßùÆ
ÛKdÊ1•Mµµ"|RV¥òµ3¹ªé€ß;¯@%Ëgkç­6Hn­Ó¬LEÍË-¯e„uó_=À) .µÁˆ¾ÃqãŒBİÉ¡®ÀNaV¿FÈyİK*N=ÁC}ÉÙ®âÄq¢\HKË”om÷RW/IÛ¼|sù#“åÊGHáN˜=§æ¯¶Û§97’'á¢é78Z¾Í¿-ˆ%£Aô~!ëÖùÒ^Øá…dÆ jÊ(6¦®Â·0ø"¡õ•~MÕ(L&âÔ±®†AAÈr÷ë0ÈCªtò¼İwˆg®ªp O”²ü|L–àÒï&ğfI(²Uyšl–8ê±·N½ÌI­ÎÅ¬kßsHí°.ÑnIçNòŒ}—Ğ‘¢ÔA§&4çêã<°³hVµÆÏ*ì.5í¥0˜,5ª0)†©¥t¾*ëÇÉWÉşZŸW¬¦îó2Õi¸ó©Gºy ¬{â¶ñü\yÁÚèc6‘îÔtgWZéqõDfò%Â_€3-ò¯´ƒ	™şÒ‘×ìitŒ8ª°G
½ÿ ¸1À©sıNºkeØ,Øá¦ûÁƒœ>Å‡Á$CR¼Š¤Û`5”š-/–P³g+uç_2€-˜%’£÷~²EöúáâãHÆñVÏFì
õÿ51(*¦§¦Îİõ¤¾Y…'0"¬!…à[0
l6ßëû7VÙÙ„ÔU2™Ml¤lóm	²ª¢-?N™ù×õ¹¼NygæaF×:¨Ï(l&•â×1¦¬BÅÉ«.Çdb›#e¯È^—÷iB¥Éƒ.ÙähúQ½ÄI«:·%ï¶nÃ±‚ÌY­ÂÅ©«Çuàš+Å½OdlË¨ÚåÍP´»ÚËò‚y†™–el¯¦0£N0•š~5nĞ&ä"óa½ĞI¤Ët
–„§‚´ğ©
Æ¹Ó½Ú5š&$7cnò›"#ÈĞØdrRHße  :ò.&¤WG")€ß¦ÒgP©÷VñıMDZÎ*
€E—t¤âvÒ>ÁŠXgöõª­*î–ÁÅvô»5>UTôóhŸÙ¹¢ÊÁ¯(D&‹bßQ @;@#*Ä.=ùÍëÑ„d[SCEÃÂ.ïdt;¢`JQUÉ"Åá«0Gl
•ö7<«²Ç`	ÙWH	ñH{îeª¿Ì/9‹€á³¸·gŠœYÕwİbe¢úHÕç'2¢­…˜[ƒu™ßà=¸KeFB—0á“ÌfíÒõ¥¿	9şªøG^ãÉ`eIù+çtrŸ]8X`‡‹²ÚDÍ¡¢ÿóÅHpù¥
ûË\{.qZ·rûÒ–K‰Ğ]­Fs<XœøíIıÀÑ÷´&T5•.Aêè‘ñ~¿'1ïü,â²£Ì×#­>éÒ+ì?€íU3X-Â¦íÆ@´§û\Ë47®4I
¥ÿ89êª÷6ÉË8yí¯~!ø`}ÀA´VÚ}Ü¹çò³=é¶Ñä\sAİÈa®D[FcJõJ_ógĞïn¦+)[A»øsÜÒ…Êî`T-Çe©×BS³ù~Æ2YÊ‚ï´2Ïm¬…÷>»` ¦øÙ©Û±Ü°RÌ­û±r[CXd²Ë–ê­ûàPp;që\~AÑ‚aBmuH8ã—{Dğ"]ºù;8¾Dè=ƒæ´öĞ}¡V7;Û÷»¡”CÊÿšoŠ$lj‹VM×r#Ö>»ıI#F¬MxæštÑÕÛâ"4»dÃ/¼æS:ˆ±–) ûÉ¡›ÄmUœU¿ò2A|p8Œ½˜ˆÈSËnïTt_z€@Ş¢çÀèeSsÚ«{›@h»s]ÿA¸J¾\>èXv‚ÙŸhÕ§ÜÂG€eg†Â·ß±C©¿¶ğú½5gÏdY\oÅË+/d WÕ<ÛšSWÕ.À$h#V¡ÆÀjè6¶®ÆÌ
 ¨3Úçß 8@*ˆ-¢°AŒ.ŸôÇ:+ñêœ2Ñí¤uƒ_À=â,ª¥ı†_<£Ÿ¨?ù³®±ézI8«÷I
ÏñB\?t§2F²‰ˆÑiÙc¾	aõÔ;’Q)7’ûåäèv7Ä#ÎŠì_5À/($&£bÉ¢Ë9ñ+¦ª''"¥ñÛ ?ÿ€•¶:È+.§dB“I•Î×,f¥ÒÃ%©ãşğıg9½&¬eâ-Å§doé6Âäçİ×@é¥2Ü.å Æ:VXò×ÍùIÎÑ¬dEÓK%Ïc,åôs7UqÃÇ:“Ü*Ô1§lB•Ã.Ö¤fÃ4™°É‰o„~™ØRâ…±›Z}ÊÓª>Çæß@Cù8èsç‘†T¾'>—ç{œ‡L'—„ê(ÇU‘¸m‹ÇÚphÙ]=œ¼““˜«+˜'” ]ÿxyHßÔkâîìáwª–ÊLg¨$›ªÉ²* ¡ç6ı[ÃÿÚ#^·VÉ´7•ëÄ³|MÙÍ¢í‰¥À*œ'øÿ¤A#fL÷}¾™ˆRŞ… [ x9Úªã1ú¬{Û{#TkÂLi·O¸"²şã7NĞüUüâÌ€<™S'¸pÎğJo!°é¶O©ÌøK™5oPE¥=-É˜ BÄ¶Ş6b:ü¯&Çf®'ş„o/†=ì€“®Õ”¦M×uºĞC4WlË‘™AÍhC»OL?Mè¶½ÉœnÑÔdgSR…Å›+guÒŸ*š"!‹$;ÀJqÆ9ßÑ“tZ¤ò>ªí.ÒÊµnuá"¢%í‚·Yó=Ø)¢¦Á‚èY¾Ì—¡1€’şvcÕ‹F)dîÔdì	ñqÑX{AßÕ›‰gI±ÇÚábjœ”»9‹jßW  2ĞsM7v°÷¥ó¸"jºÚË#/aästßq @1È,n¥ÔC'Iâñœs[ØØb2ÕD,ÊM¡IìoÃúÉÆÓ*åç32­í…µ›|5Ùï*ºnñmUMán
iR©¤°í¬+nÛë…ğÔ#kb“ Í\uÇ6c¿Z	YóØx±¶éöÜ~áØpjŒIôäDm">h’Êu2Ş­ E€?r¨†±šÌS-Åå«3mú•»yµ_Ô 
ÑvJÕ]É<<­…ä­¥Œ~İØa¢A”W~†˜ZÒƒ%‘­]¿øï:Jl§¨0ÂØ”wi°°…¹cùİ5Ì«2Ä)ïÓÎY_¶ÀWˆ$úõ…~AÕRâVã±ôD.«rÀÜòìç0¡€n˜íåŸ.]]ï¬rÅİ«!‡`Z9÷jş—8Y ‡Û™êdy§şÿIíIaœ”=ö_ )İæá²ğM¼‰ıùršTi~1Ø’ÄöCÜªO'1Œ<!V•>$$¬NAÓK!‹Õe Ç]\Ä„zĞÚ~îñ*Ô9§jÂ—!åÅ¥½„ˆÁ“²Ğˆ~Ÿ $?kwZsEİË!¯`Dt?_h ¸6Å¤îtU)#*wİëÜ%%*Gw^˜ R¸Š»p?\(	¨÷<ÇÎêRÑfoM•;¹ËwAÎôÓ
=rÄ™´Q‹ êBKº{KxÌ5lµØÕ§ô.Ú¤cQùÄzã(T0ëµ-‚?û•±\£mºìëÚµ£ü8yêš÷>µèO6Œ!×å}³#—Yî0‡:ÕÌ‡Kê¾Ã_å¦Å½Úœ¢k4êı3UŒñ3PJrµdèˆ½ôN{8z\µáòíìÊÀ—Ûl^;ßtc[vMb~e˜0y6éK1@7~®˜DR‹E—Ccl:O|b¥f¼îúô{5RhV¹Æ¹‰œHVOÜ;}8uÏ_, %ñ#5«êwGÉäA¾´wï8„/4áMŠ,}tâì¾Õ¼ÂıŠş~Ÿ‘ªm ^‘cîlÕjI÷3P=¸–ÿî8°GˆóUıB
}¿zÏ«Î«	‡~Ú˜c‘õ”X>Šİºæ¯óAËHoN”]tÆ™ªÒÇVÉÁxc›ËuõX5Â¯)&ÔhâM±·/	M”èËËšÌóÓ”çIéî™^l+drµİ!œ Y®K>6n²7ÜØÃ8GÇÌ_Õ3+âÊu°Hu{¥gğæ¼k¿Yü¦ÄLr^ñå¼s	İşá¸pB”|H¯@0¬‹wf)­ö³4Äèm¶•¤E5Å›.Ò±dÖ|U
ëZşC1ƒéBöó'‹l+ñÚ×ÙßÏŒÇ´¿M<j½¸£´jş¨xFšŠÛQj¾.odªµ$µ½t=¾_¦ ?n¸hõãÇÂæfŸÖÏ%¨g³¨ñuHBxÌŸ<Wºêî÷4~¯XD‹yŸZØJOŠ	£e6ìÒÆåªó7ó©»Ëz-]`µi‚\îí‘µ”OL9‡ïÁ´ù9?B´6=ÜA¡‡°bxvñvBµøpzœót}×ïLÍjíi“õoÂæmÆôœÑ±ÙâòèÁE¤„._{C_uã‰EÎ„WêAY.4$3°A©ÈFîŠô_7HKGtûÆûÏ;*ÒH
¸<J©Ïe£h°zu=iéÆ7°#–¤…æ>û"~z˜n–ğõİF_x¥¯¸wZ‘ø¥GTOîjBèxyå(?ÕNÏüTÍ yï°ÊçÍğeòZÇúM»ó-_²Yù£ÌïÉ“>©W3¾^ÄFXÁólÈï’á­Ó³z÷U¾‡Z¾ƒYş‚øY²Š¯zÍ°Dû4‡\ZÃiøŸı–ù–ú²˜D„ š"Ş;%8OOLıô¹¶€ËÃ/DGB##nf-gF2t„fkj#05ƒ…'0SuÅß+ '`"˜oÛnZ3CÓo†n'&&ÖÃĞÇæËš%`/ß	$!à$4–U*tÓ·¬IVâ£1ìXuÂŸ)&Ô"ïiÖù/ëyÎ-Ó™–ÒÖå¦óôù¹ºÊËKF[q´ J#P!Ä ki_<…2Û 
1Q†‹%m ÀËÖh^"çuİ5Dô8j˜¶µ†S"<†©$`€ê%Åg_3¶.ÄJû3„£p˜ƒš´ÔùÑÿ‘Bhú&ÈÑË)?>3?™~Ü“şğŸ<Ö+,Xá¤ë%65à¤¯/>y!Âlú$5ãlu‘j.+—“Hå–hS—ßº¶"—a–VÔ”ä_òğ©¹Uæ©òÁ­ğYâ—Ê©(Ñàdp\5Áï(t&ŸbĞ¤4LeHÈŠ9?ÖËáåâXCş®€ô`Ë! Ç{*›gRµÅ+i>¬‘"ÔŸ3‚P+ÀSI3àÍ“=éVÃ¾Ä¼MåÍ³.É Ûú_Èô0Ï4÷f-¾€HX‚¼Y‰ÂŞé¨~­nOõN€ğk<iö–ôßøfú’ûxËt<Ş3-w`Í¼HIÎìUuÎÕ)|&ıg™nõ9Bà[Ûj’+2ßİ˜ÕÓ©K¦¹½ŠÉŸ.Ğ$d#SaÍ$j03Ò‹†%gVÀgŞ<@Tf—.iÑ.h¹»Ô_"–Á#´¹U÷Cz<áUC³½®RÁò¶g“=•é—6Ö®æÌˆ.È#ïû9!ï³Xc–©ÎÚ°ü6Nöa¸J´|<éòöı¾ùˆzÑ‘!O`cœte*)Òô*ÒGE€…v{h$£vÁŞè`vÔ0gd\Ú»šlSëc”ëê…3oâˆZÎÿ“m™sÙÇ!®äñI ı,ÍºvÂMÅèk6—nÖ”f×Ræ…²ÓÅô¦ì;‚Ô¥”CIöôÕxaÚcra‚ş+5}êJ›jÓW%Æª*Îí)n¦ûÎØğ©»I¦4 J=!IÖ±¦ÌBíÉµ®Ïl;UëOyà‚Wx¹wÚÈ—R«+ÉÆú=Öº Ä·V{ğ&¶&§¨¸ú9YÄ}’˜Ç×°mI^aSÊ¢G	&Uâ3rÒ¤dÑ~½.ä±q”;ãøGçƒ(lârıR”‚8‚ŠV²(ø“ª€É#ú,ö(óë°úA6cöóüğôñ2q`‘]L¿ÀÅ%&./éi;ÛænÙU/Ê)"+ìªxÊ¢;Œ¦PÏÉ!#ílø˜÷Ÿ³ Üµ,Â(Ä¡¾@OH½üI¹ÎÊìo5Ô/O%p×6Ô‚$gá)•‰i 2ØšeË[À«±:Ój…&&÷·š2óÏÉñ †Ñ7ÑUÀö˜q­<0ŸÒ5Ëøäe¾SnŠ¯î9é³ô#pô¸ƒ*¡W8á´Í`”vØ%SÅ‰E06İ¿ôìƒáGí È_#€Gq¡­Å,SbÑÀÇCÎ–áV–‰­oøUåâRÓ=šâPZ°¡¬=Ş|Äå‹K¯wã Ì-'è¯»‰S÷Èó£°ÌÁ åm>¥z9V'Ëï¢y—ğÛ±.AiE[Ægñ_±M@µE4·âC¼„ÄÖfkßÚm.©‹Õj8Ÿ›/I‘Š;¡ ÍÈÉ‘ñ¹&Î4}éöÍO¯Yqf`2èæGCç¼xi+²qÑ¤Ô{ÀoTšs'ìÇÅÚÏ“²ÃB,ªS§³±}½p©±(ùSªĞÃ *âåóqÿºò‰ÿ\:Ã)ë$5¡­Â‡kXUƒFÙ¤”†R´j+Gdº«ì3.ı¦»@	Šüû3y¯ğx>Øj UÂÅëiõ”=Õ«eÅ‘éÖ·-ˆ³Kƒâ^îü=Xÿ\Ü>İ‹Åù=«o(/—æÃÇVı¾I°Ó¶İ-]T4Üœ~­œ!$ÔÚ‘+%Ê9«üVÿiƒ§›Å5.§˜æ.ÒÜÕ™@&Û”¦R¬J«ˆgf"ªF™w¢ÿò ÅHØ<b©·Óª§
r‡º®¢Œ?¿X:ĞÈ×ÔI),WÈçÆ_A¯7x îôg	í_Rõu‡¸.¡-?“‡‡GìÏ°Ïù³Z–Á-½j¤¹·ƒy,©´k•Ó´SÙ çi­‘*„¡BÖ±¯‹ü©Èóì|ï]"*b< 6qzFËÌä:öîq;r`YvÉíû5¸+Nv	-
õÒe¡E‘À‚-4.f0È|è’¡ô~fL²ğ UCKës™ÔaQ-yì=\…#sßîŞ	¦"C~Š¦É7²R²ŒÂ(Q‚5ãœ!¼ºÍ¼:®5•ğhŠÆY!•åÒ|êÔî37¤¨VÂIÏ™óyùoÀ¨›òÙzóA˜¹ÑçÉ JEfäŠÛúËŸY"sïw4aĞ2uhŒ,qˆñ,XØ«MeûÓM¼hûI¸

&‘Éëúæõ—ÕõJMë°Ş£¸io~0ne„!›`,/k²RH ö×Ó”Aj!¸¸b/y@lºdaè2ñX†>){‡_Ì– Æ´öN!)Ä&ëb÷Q¾„H[NƒL&²¬›ÀÖùªT­qy¨†GÅd?W,³Ÿ±cøLŒÈØ,=[?òBKµ»“Š
:›kWuÆŸ*Ğ'[]Íè³'GÇÛ›•ocÈ±[¨EõŠ&c‘%Ékò†ğ3„dÏ'°£ÓäA³HMÎ¬]…Á›(,ë¤²FÜH‚¹&6Ö2g²])Ş¥¤¶@ò{É†Ÿ÷°2ò×—Ñë™FÏÊ3Ê‰¯Ä0klU‰øP¬Á yö¿€b&ÊŞ­ šo·KË9P·èÀğí­¯ õ£E+¼Ztò‚}F|.™äRóE½Ë	Ğªnè.ÓÕæ¦Ï¿İ•!Hïêë4s+èİ
K(ù#¿pB°e8²jµ}xd§¢ßıüy¹ÚÊã/N›B¾¬Bé¥by©p±¡1qñ\£eƒP]€´¢sòiààµ5¡µ>Tm¿ü»Ç8jª—º¶Ëï|tf –tÓNëi	„‚ça£§²İåØÆÖARÕ3â(`<5Xlo¸¦î?‡îàtp\0ì8uêàH~XİG0	E½¦$ğÁSG°KK8ºP÷·Ê“ÙPçU¼"w"óŒÏ9QC+¶ÑœdQÓDeËSP:Š}Z¿PöÇSÇ÷Õ–2l2–©ÒsßáSÄX”+ŞÇÎkÜ¡—©¥¹ƒ
Ùÿ"ø!º KpJsÊŒu¤©­şw¹.|0,?›Ÿneb®Û€5`+Æ¶áXµG•9°i
×Vi«øÛ,ä×DÓø4WõÂi¸Oş“pĞË;æ?èxğ‘¾y—YŸÅh§¤ñÒÑ? ¾±›Éñ¾y_E	_¤PÅO|	œ±iL±°‹§ B¸
Îû™A.{K9Uî¥çÆw5–*øñ.&ô¤ôzòòúd¯PB–dö‹Vÿ£…¦«¿ÈoÇøˆ`†®'>87iëÙ@ılËJìzOc( \³ ®ÄÒúö>{wÛ¢üˆíD%MhZ“Z56-7ã%vD²ë=`šXp·¦r1)±‰qFù{¡}§'/Ö™¦ÒÂå©³Íúí»5ôq"YdIĞ¿ar5úÑ–zkD3É’Ea–f×dh6(kœ²ö³¹ÈJî4\/Aäs~§.Ìò(ø74Ñºn—*ûù ´·r{ëi¸\Î7†ªLVC•ÖŸ£Ç#äûc½Zèîú{V5Z´Gºp÷¯Ê™YWÇW6ì ¡ŒÒrWÉÉ?Ï{,eóS=Åø½íDåwdóÃ™@bÑ£‰ò,›¨ù¦NŒ	;Xˆø¬gÎ°Õ'ÙÄÁQU´rÆ¨GÎ~”blàaÃŞ”G:ãÊ–šfëæ‹s§©ú¼À¸x1Ú¬cÑû${c[QÃDiËVïFô
ÿ8*²§‚½™‰’ŞÕ g ¸5Š¯?F$_ç!gÄîËLßuY23ÀÎUèFKöúÊKtvK£õŒÍXŞ7É0">J·³}1şÈÕTšÆI ®Nw¼/øz{øşO‹ujõ¥°ôşšH¬rËéŞx‡<¼Ô5u¯Âİß€É}ÿ)ŸC	ô>ÿhxš¶Óåüs9İàî3
éJ³9É§hYÓ+°îi˜Ò¶åó}ñÙ¼bÉÑ®ìT+-8©'Ên#˜şTVj€6½¤ÍÆ$ÏUèWhÊşh@ën-É¦£ºr¯÷BÏëCÎxi2äÿÃ‹ÚãÇuªŸ:´+g|™õ’ÿ¸7
®¿H;N«FHgà‚¥ğyŞl‰‹d}î)E’Üíé¨mCÄW¾O­­ã@i<¤LóáÎŒş(…€ÈbWbáa
b´‰$+œ@²DùX€LÀ}—ø1ÏÜTÕ¶ii°ğ±ŒÃpî‡pï¦H±:š[hÓã{¤Ò¹ ‹ƒİ]ü¹øJú;;):b‘Íˆq‚å9z¶›Ù|'‡qåš !WşÈıÜ|È*…¨$;íÈ‚Ù<–ÄØÛs›¬™¢täer!¸µ§¼9‰êŞ÷ ~ @2ˆ-¥I#ô:»Ş1ß…öcvŒXªÜÒ(¿yè?6¨.Æ¤jÃW)Æ¦êÂÿ9æ¶ØRş™¤Jß5 ş·8N¥†G_ƒå¯wR@Ë:û‡Më/¤zƒ<ÖÒ³ŠúâŸôêÅÉCünDV@1R¬»#¨Ûûf^&XÈ1®¬DEËK/On9~±œùk†d®Å<#t:Z:İ~(Â®ªİ]Ä$kcWQÆ„jÛW#N±’Ğ86§pŞäÀ]EÇK*hó¼ØfÍL¢ÿÄ‹gÍ#Y©Œà.‹«?³Ì‹Qïõ‡^úŠZı»”«pú‡&Eà?—¯Äw	áñÉIı‘¹”J×E)¦!™¤çù	h†ŞÇ;ïúªnN¶XU¶c%Ñã$qã\qÁÜ`q€vÄ÷e£xü4”)—fÖìÕğ®Y²Æ™ôßÜ+R0ÊÌ{Qg#).†!8]Ş!ÙQS=g#gÛ°Wp	ã€÷'kßİUÚZ|í_S9}Ùêèø½è‡Åi_ ¸pWGƒÛG¶CÔè7…ó=ói½ÖÉ¦îÂüyçFØşªä[':½öÉ¾áÂt,Ö P|WG‹;M3CÏi¹$:,ÔÀ'UVèÃŸO½=.ÿlÜ]5€Y?ñ˜ó#LÒ¯øü;LØ±¼I¿ûL{MÛM©B«ÎÜ(ÔÜÛÒsÎÕ±¼‰ §±XSRÓDì X  9€*Ø'"ª±ÙHH’©‰§³, # !ø/p YIgxVÈØ£PU¸»1úËtZ%!’&Õqe¢ô€ZmÖçÃ‚™–ív„¹üjFŒ¼ŒTx2GÑ°piøú¶ûû|{YÑMÉJõ‹Š%#ÕÂ_aİËäş­-LÿDë R €;+r§]‚™BŠ•µ‹iåËŠO1!ê w ²0å[‡+Dë9²kÔáŸƒy¦v·¡øØ
İ^†õ*ÇÓI¤£sh\¢´øü¶ÖzıÆ[ì!‡}$?ÀÒ‡ªe‹õ¹°Ìu"ò­©è¶?ÅÉPÇ+Õ®îfÌáÕP9ªì“ÈeZÇñoá¯—ÁÚz.Æ™Fõ®R>xiõ_Œ³í¼„šv-ÀĞ(«Fs2Äğ	MÆ9İåaR÷RŒy!áØÉSZ·C‰ü^ùÀzè6³nÍÔm§U‚‡š²Ó¥÷Œš£”÷aûåA»ÌxVåÿ5hpËOîú8¤ä<õk5¨Àæ·©™Ô“±›‡Ìv×ƒï=oA0¢É1Q™2 mkN5ìšV®ìM3O L­„ôª†eĞ&^@4r7:ÑZ>	ĞĞ_$ #x!Ú c ø4z¯[	tSØ¦x‡©n¬X1LöÄşò;¬|İÈhì>.õq}9òªı‡1ŠòµbC›²)ŠSƒYôõyúS³T™=Àùµİë´Ñ¤YñCºæú¨	+.)¸hlú%njN%¾G#J¡Ï l8ê·7®¼DIËNåC^š1ó\ª1œhäìÏÆ<Šá‚ğ×æ¯²İNp[Äâ71%t~
ZZ¨¹òÚ£I^JBuP°şI–cô4peXbCû,ËššsÅ°9T)eÆ¡…gføMä.S[<ÏX—;§š»±Á¹(œ 6¿ßè]9O^Œ ]øº¸K
1ø£W†œÕfš'úi+éTñØ  Ë˜×¢U³G~é¯yÖw”:*ÈÆ³8¨bÏãİï“+i£2fßäÜ”xR+%˜JšõeÜATº£öh)‰ô£¥€ñiÈb'æÇ9ÇÙ[Vå‰j¿’dóæP}«?‰eÅì‘öxØ£“ñ¤ƒš]ŒøQº„KOXÍ¡ìîÄJª"tlM8¿N5e€‹0º„ï$pNàŸ$[ëóôLŠMêDÀ±ß9à	·Ú9GËĞ¢ó¨#W’Áâ" SÍG1| >¢a6*ÙÜû¥¤CIùÎúì{5´!o!‘!&ÅRG6ñ<ÙlG[È*›õfôªÅ>Ö1"³aĞ]¤ƒxY³ÌãZğ¡‰}âŸ…ãÛBì6–Á J‘²(P¿ÌûIé;„æİ,Ì	‹Ì®™÷œŠåí%D”·`ù,zD<iÿVøúº«Yr09C¶ËÇŠ`i¯o
Bz
¤mN]şHå“]|rÄëK:3ÒÑÕÀ4È‘`Ìs¨ªâ:XDı¶ëó™Ïg¿$&¦?ê,hY†ât€¯è
ÿÒ3ÑÌdmÓUÕ•Jeë®^«ØoÇ|Î¦Ğ2¶@ü,„Œ4¢ÒÓØMûÈŠš«ÚpÙ«6¥aîk#?òé9§jLÕˆä•_jO`¼&…İ•wÒ4)Êl[¸±®1-ƒı±\d¥¥1rĞzkêur&„”kú%ŸyÿÂĞŒLùûì¦€ù‡o“åws…Ä{F^0ÜŒíl»Ja7œ)±©Ş+’ƒèğ$F›î˜%Î‚,XU–jd3®+ãOÔ$Ã\SÁÏ}#èÃÄÆòÃÒ·9£S£k÷µôO?L(æ½²É¡×„.Õ
DSŠ7z7CwËÍëbe$îÅ'[Gp
œ?è4v¯TË*AxóÄq½.¬”ºäV3O¯w éd×Ék9eX\ù˜zÒ›%“cÑ÷$~£XAÂˆi–ĞVäózıÛ9£jÁ×(f¦’ÂÕ©§Âºé„<ß<¥U47bÅä
6ÔšÅë†D$ÉÛ^C¾ 1P°9÷åÓ·:œîk83‹ßzPä1.nóÜMòLÛje…ú,€;Î£¥Î¤ºĞaƒÛã·>}Îä30«ªÏvÉ"û3ö/"añL$àÏíêñı8=æİ@Š÷Ö[C<`fï%¼S±2ı
°?(=æ©²ÆÍªí‡?•…g¾(Dj2’œ7¼ñ30	LX½=º©‹ßzà03l-Õå§3­ù…ºÛ#aØb´t\Ckğ|>™èRö…¾Ûc~‘Ø\jÒÔĞ@	:§B-—|Êw°šë"ëhõú)³ï—ùlKŠË]­W‘Ô;VIœ$è<v©ŞÆàjğ<6©îÆôbqIøó“RMí(]BÊøØO0.cÊ™&HïYb—Ûû?ş¸äçÅÚ¿øñü|yÙÚâã1±ìLuÂÕ-ÉkÓfJuò÷/ÉMİ2™èü…ÂU]ó"¯”öóÃ”(Gt÷wš¡¥n8Ü5ßÓº(\y\° xÙhæ^«–2EX›[–œ*“”­/µW=ÆÎï’ÇZ¸îxPçíİJ¼lq„®*šŒKY«åõÌè¼Áê›^›:%ˆqkî³É$Eã¶Ù*”•f£&•D >Õ:›‡r’çãoÇ‘/zä•Iæ#Ó‰5Âó&ÚB…9ªÒ·‚sƒ‹˜ö´ÓşXLùºÑ‹$_c@È4ıU.Ö[[Q>¬Œ3¯œ0%%T™°g7!Ëg‹¥{¢L/äz¢hWÂğ£mó˜ÿ=ìµ’­\ò;J—²zIÎÁ*ªã”0Ó}¥WÁƒ«Ò+[î2ŠÛíºÕËa$Õföœ[¯ )Tº$©Ëã•Œål15Ûß¹,?Ş·rôYsÈ!¦ó¿Z¥1š…dU¦¢Å%\Çàğ½« dÀbËV9Î#¶lYW+‹åƒöÉ"¶¨ı we@›30*z¯Ò^(°#^l‚‰\N”%øƒ§uTêÂ'|¬´ÂĞæDŠ3¯Şöà¾Y>~Üíû»ÁúEZcîúâDn÷CÄlÍ~îF€¬+y'.çÁHÕıV™ÖªY½uv.è\øãKœî9Î®brñ•Æ!÷–;“õu]®,¥.Ö˜İÌËè^ğû,Ü:»q%-S•‹r{©úÆû*ûI#åE‡/_Ù:_Xñ¢ì9
ˆ«¯qü’dr8°A°yYcÿ¡½dÍÌãšÑâ³yä¨¬í!Ìµ$ÒvÅê–2'çÇ ÌAû‹¢[ŒZ&£q•˜Ä¯dD	Ô½l¥¨Œq-êéˆxˆß›1ŸÂ:_—4Ê.0É¡Øë"£Š›­Lî ª}ò"âè÷€DPDŒéº›ùŠÓè
B`¢=uñB4&R$øYİøaÅï({brü‚-dË‰c3Q0h§I‚·ê²Üº06;¾Æã$",Ç3GŸS9SŞZKî{,…m† ùÎj*«§—õ'İÅÌ™´{øÉ]‰ğBõÈw MoüöŞ“ÒÌLûùdÑ~´ }j`‘ş0¥€ÈG.ŠÛ `/T¸C‚ÂF=Í(ö|²QØÙÎi³ç›Ç€ßˆ5‚3Ñ¸—ònMgRÿ@Æ»|Å#ZâUlóöKÂûÜ5Ä9?ÇwVÚâDıEÜ~®]5§Â3ÇÖr’Øğ˜Á¡YàˆŠäèŒÇkR'Ï˜„ÿpDf )F¯6oø@EÃ¿H tÎÂ,¶Ëna6áCÑ!	‹B£Fşjg!ªĞàÙ'¦½ş™Øü“‰eĞI8ú‹;kp~.GÏîØ'ÉÓATh.	Ş	_Ï6” µñ"	\Uı¶,÷ØA!_äO"hˆpó­ qøz±Ûc}ÑÙ¤rÃQÀŠ®¥nØ(µü—¢ÈÏÜÚ×À[±G6çŠ[ynkéã6ñîütyßZà0(ì*œ©kwúÓõÎÃZzõ£±sºaÿá…)yŒT³g|íêõ·V|ÙrFäŸ•»*ºhkbêT†úˆx@³»ı}à–m±ÆØ.q¥XR‚Û:`àüp>úÅI²®»İ0ä=½Ì÷{±*0Sğ„£öŒÊDâ‹HèqJÆ=uB2W°s·B‡Ï¬VÍ‰%|tÉÆÇİÅtœ²%•~Aù.|;ÁB÷I¾Ü;ÓšPoÛÇÁÅo2½Ç}Âil“6"B‚$‰õ’¬Útø5H6§øö%NCT—Ï™\|‘3ğ'-QEãzíÒôm±†C«« *R¾¬Şq÷õJÿÏ*´:S’;$—d‹“ šî>í¨lóõšÈÓ5Ğ
8âÆzõ†#hdšó#êènœ¯Ä<9,ƒ´ÈúÊˆª"«êØ*Ã‹ºj[Tº˜7Pİ<ÙYğ4f
¥@¿<½³‡÷k“¶=#·ÆÑÖ gäƒV¬_L¸:u+ĞTÇ¯ßş]‹°?P¾k÷æˆ
Pİµ®U)¬³ı;Y£8·7øë¿YèŒ”,úD“æ¾Î´c0ñŠnÅ¤Ìşz|e«3©öAğ3€X=Â©Àô·”êãSt¸å7 ßpJ#uV`·&¶,¬Tèæ_|BL°°¼ï´ã‹.£*/G5Ä/+U",…œÎwcŸ$-&T_‚3+ËFCºÏa#=‰àJ´œUíÇ»èu7³Â‚Y¯ûr- #ˆ…©$º×—§ÉocàÎ[÷CGşõD%y<±D’V ½Ÿ@Ö>Ü .(ÆÇêó
ßËÿ„Õo?É wi85Ïd6“ £½*LËæäéc[zˆÒoÇsG¯S-SÑOŞxx„’Æ`Éş~>¤èB£Æpˆ;s™Ä{ÜÒ‚€E‘ÊÜaòŒÒúˆ‰‡7Œšx”î×´tB*p¡ò$ O‹SEtXLàíœşÎølê²dA~¨Åê`hM<éåDãİ_>üj
oÇäÙ¢¿öˆ1ÛÆÊG[Mü‘X¼¯bÒ.úØ?F8ŠºÃD¬¯²§~«=ôÏúiÕ¯bvfãïÀ ıDCê«Oª?{æoõ?–Î{İ5Õ†¯`²óHÏ¹Ñ7Õš—Ús¤øcø Á˜x*%İT0âŸF•oíi†gz‚ã¦ËµPşò€óúŒÖ<7I{Ê„Ka ÊîæYy6»nËTo.&{ÉüvDä¶À¿HXv=äá‹HÑ,HÖfK9óèŠKïìÉ"j¾ëZêÓšîƒ4YïBô	¿~Èn¢”MşÂÈÄÃ±Âğ¨G­¯©ûrhk%FÖÏ”›jnfî
p `rt´y"kÜ#!áàpp1ñì|dÙßK®uõru]´=ã}Írˆ±áøãLHƒ¹ä÷Â„ñ#o“t$àp4u] ª>$ˆaïŸdJV~ûcØhË¥_šF4g”2Ä9ïùõ>î¨ú>8ã†“­w"ó“$u£`O†I_~¥f€hòaÀ­Y˜‚tp«ƒ¬‚ÅàÜİ¦SİnLÊP?laSæ¿:‡ãøV—´O&{o¢?¬Ü]<ÉğgÚ|lsî‚ôYíœ\üğÌ@>ÙEŸ¹‰£é84ÚjfôåSˆI,cNŸŸÁrÏ0µ¹>mCøı¢g‰Ï«)àp9ÍYåÌo$ëyä•5ŞÂğêh»àK°Ô,ûœı¿İGçMoÍèÍ˜€KX7Ö‰‘Ï*Ş,8ò"ğ­Üuv,¾Òs:ëCò ÍX±4°C‡V‡¬¾0ÛÙ3wãó¶â²³ş5 ŸË"ïñDOIQ9¹Wû2 £ú°Ö-Ngh­ÉùêP"2ˆDœD8Cÿ}DîöIO:üâ\G1Ì˜ÄpÎfQá5Ğ?\—{¡$ñ•ÄÙIÓãÄ™¹Æ¼äÿSpªÅqnºËN];<–X"âdËi´Dâ6f*›MóãÌÁ]æˆßÕTF‡JÚJnP¿à|\Š{¢¨°&ÜZ^¹wõoI¬€§i/·ŒãvÍ¯øıÉYÕq¸`ş›Il=ÕéÎD³àéÉ#ˆ
ã>œ,ôÔ"
“ÙìËÆ³ôXğoÇtyË|q]ÍÁ#êäô¸“wÚ©0yÓT³‚HH+ÆäÙ_Äñ¶|‘4[­h–©!ù ƒ¿²eSğç#{çíˆ}ÑQF£'ó{ìXÁÜÍ¹0‚µ©Ù®ˆÿ¸8$Üæd$Ø˜|Ö‘¨‰Kü(Ô.Î2Xò)Ò¬û¦háøà¼L‰Ì¢#[ñäUD¸”m¦‰‹~åW‚d~şjáşfLÍf@æˆòÌ%°¿õÑ¹AvS«ÖrvÈÃ“6©¬µ}7é]„ø4×Ãkl½"´œ¾¥Ó_l­4­B®Ÿ»w8z©Kºê¾©„*oÆwW7ÔÊ„*ikÉ&šÒ@¸=>ÚhÓ˜oã4a—ï,ÃšX%º-i”»ö#“
é‰8èJ¾õ~¢n‘•íÒGÒ÷˜f¼×³ìMX°•HBŞéÌÊ£&lé!—`V½H–%2—	ÓÃß”Sæå¢‹¾å?Ì™Ûjm5¤‚"1LGq»‰2crlŠ€H`á	ƒ~Ù±“ß±ÙÆÃå‰‡cß EB¹osı.	}zŒ”0¬V©‚UØƒ3c°TÏŒ€ —W¦°ór+˜¢Ã“Ï´¬7¯™ù/Ëy/…	Ö
9TñÇE´ÍÕø›—ÍKX´Æ7œY¸Š(xK¨ïÛ¬¼îd€…7§Ÿ„O@f3MíÍÛÛæf‘%xˆ$VˆqLşª•u¶JzP°©x^ˆ&kÁù8¼	÷+±V.¡‰rÇtÈâNÖ½ºÀJàã÷€œ|ê€^N4ÓÄÈŸ.P6Ü3½ÏYHß"k~Êr¨¬ó•èÙ¥ì?w›¦k²$c?T–´Ì•P¤ú™5h^;¡­’Óªú»oÿ&Né…ù^^7#ˆyäì6œVxõ$f
¨ä(ŞÔ¹êüO úe>ı€÷ìJ”Ê~‰uo± %ÈYXpø Ó“Ûdª6ñ—ó6I‡ Ì7h‹¬âö ¨HùôÍ@Ü~™V0wÁ?À…Ã)<¢¶½Ş©7ÌŞ£),í”4WoFıx¦1&˜F—÷ìÃZ¢û¾Á?×ÙĞjQ¦)c<7UŸ’i(æì¸j¶ÅjBñdnéÔvç^ò€}˜’²Å§tÌåÜŞ ˆ•õ«S9^ÏìAfşáw*Ê$Kæ@‚ëåÔmÂ•©—ÖºæË2ïm¥RJô¢)]ıñ­Àî"Æ2œQ M)>V1B³5Ã‰éa…Ğ[Mq7Ñ—±0gQ£‹!«B@tÍl_ó9Ù»şŞwM%íğaøƒ{ÊÑ!fåQxèdÿâÖŞy×Ùıt¼šØ]‡ÿHÄ2“Ä¦Ø…}0Â¬òËÁõ ˜L€xãEøguWóaĞâı˜½(–;‰óƒõ€v>7)„„Q›$0µ]mæø€c1&¢¬)u#ÚÂ…^WšT>¬&–-'‡E÷¹§#”•Hü£Í™3š°æo„÷<ş£)2Š‹¸>Ä{¤ª! Mr”4Á[÷èÓÂå)¡¾İ˜±¼¨† ]%úÍ YAb¯fD	¾æT¯+x0ó]1¡Ü—’ÉÎ„×f» úJk	BÙBı”“óàîE(aG&Ï×ÖZsD&ô>!-z®^Oß565æ¢hI:eëÕ5­|UK‚’r^İl£Ï	¡dHö¸£Ã÷¼÷\ğ¬û‡1i®·HNéÉ]¨ü-Äß†‹&”c¢fùtI“Z±h9Ùæ¶´éı ÅŞ%4”L$dk)!œ®3u@ş`Õ»`r=*‘A§1KÛõÔJA'(jÜáü†<ßH´úûZ>*Î
…ÓkÓ-+‡w—¶{eç83ÇšÒu–â”®u¤«j-jÒÒ@Ÿõ£Î¡¼8öÉkŸ!è®5ZNká¼B\Ş¡ğ ÒQ4yæ7ùÛs#]á¨Â’˜è¨Ë5^ÏP»M<ò
1\°é!İÜ´2-N›öÌ¿!÷ÍO8T*‡g’³÷®±ˆ‰üDÔêš×/P·2²>îœÎé[†°=Ã®³¢ë¢V™€ ¼‘ï¹E7n˜R·E‹_qÑhx¬/‹†®wå6^Åü*Ç¹Ğ~^ ÷°MëˆcÑó:ÑM‚.#³ÒÒ™ëüWHùıºùâH®% Z5eÄ.šk3cÔÅÚ.P"ÏÈŸŞI$ì^ /`¤QUú	y»Ù@öU¥ÛnÍÔ<‘,ÑôjÚ)äXÆu’9ÕÁÃƒ\®Û°¼çÒòœÊ®^ŸÑ=ztn$*9QĞ+õ˜V I!NçõFç×úÿ2+o<~‡ušÍVD`¦a7l}Z(áÁİZø*éó^xXí.I¤ÚÔÌ2¾"y}”ëŞ*Tø¬×ñ¾b@½^çĞ´CCzü eñÒôkl˜¤°d!!ùÉ,ÚzH¶zÎ>ëu+¦!¬ÄŠ-˜ø’ã`Ñş	¡¾Ù=\G4ªcÅ½ Vı,À:­geâDÂ”2½VÖ†æˆ··hã§„f¨×úŠp@A"lÔ†RJĞ	aŒR.}\©rôÌ4Ü7ÿ”	:_ƒíòÉö¯‹ó'›QßP¯Ok0S¢Ì÷‘ÛaíÕS3?›]0›{°ppws†¥<pPÕsªä==_	ˆD¨V0ÃéÇ^dô'^gé´ÛşÌT%½óù_Kí.Iš²¸çŠÊyœgØ·7¸~ÕbÆÔÏİ’EõÛGœ0æSƒ3ac²àà‘Xù©ˆÓšú¯kd¹"zQ•Í:&_C@	È>‡ÚŸJ´Jru`,á… #¿[¿¼ùÿBvk/úESæîÎ…y"'‘A)_âŸMÂi p•-*‘çr·]œXQÂ”i›•F¬„§jo¶|ã2Í›¾¥ôĞ\P»|¼©º¡Ä?l-sCşsïîë4wo^” WxšºÓ%ÿc8ê´f^õFI±@®ù)[.·X8‘œ(Â…!©¶…éÔ	ı1›ØgÑôÇÅ}Îô‚ßhŸe}G†!>Ù}2†Ü•£eDâö4ÍİX–qfV®	é–¨B‚˜·7¾ë‹ü³G„»ù¬÷oÅ.?uòºLsÈêÖQæ¯Vo3£7µ1$÷cGæõN¥~³Ü“ü Â¿`Î&Öª©ä^AÙáUßóÿ–UbŸÌ˜t[¹E•=/v¤­ ¿ÿŸ„cqú’¨ÚwÁùÅHr§Ë¶0åAGP”ŒJh¬8Õ,¸ÊÃ'!±o½6îÃÆğCË^\ &ñşõ¹·t€ı¿TºâFE`šdSÓW}ÛÅZmí1zq·×¦´Šù\‹ôcl$²„ ©ù¯ÍŠãwÁ­²8ñª(PKoA‡Ç«È`¢ hÖ"9J»bUYÚ7€ ÈşÉ8d;à‹.ª­†Í”>X™ u-„ÍIr%p×\æ“jÈ‹×™ˆ¶H3“­Œ0ıÂpwEkëp@œd•ısäq87“×
£óa®¥ßiIóN¯‰-øˆ‹«;tîcXšÎ;ÈŞ}I¢ ì¿*´e|ëáƒHY­Î©çÂ¦gøc—°¾aãl:Ôh’¥Ù—F}¿Œû‡=şŠ
cäm¿9<‹Š¢¶‰ô¨ÙıtÔt[4B~~ë!~âÁ„UC'˜ÎÚ&ÜJo»`*UNáaA>üAñ²
·ñlxÜòL±Í<š‘5§Ğ	İ1X1ŠÖ)Ñ£{¥è²–İî^Î7ÓßSX‹ .m=VÂ´üË&“2µCş9 [in]      IRQn  Device specific interrupt number.
  \return             0  if interrupt is assigned to Secure
                      1  if interrupt is assigned to Non Secure
  \note    IRQn must not be negative.
 */
__STATIC_INLINE uint32_t NVIC_ClearTargetState(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    NVIC->ITNS[(((uint32_t)IRQn) >> 5UL)] &= ~((uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL)));
    return((uint32_t)(((NVIC->ITNS[(((uint32_t)IRQn) >> 5UL)] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }
  else
  {
    return(0U);
  }
}
#endif /* defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */


/**
  \brief   Set Interrupt Priority
  \details Sets the priority of a device specific interrupt or a processor exception.
           The interrupt number can be positive to specify a device specific interrupt,
           or negative to specify a processor exception.
  \param [in]      IRQn  Interrupt number.
  \param [in]  priority  Priority to set.
  \note    The priority cannot be set for every processor exception.
 */
__STATIC_INLINE void __NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
  if ((int32_t)(IRQn) >= 0)
  {
    NVIC->IPR[((uint32_t)IRQn)]               = (uint8_t)((priority << (8U - __NVIC_PRIO_BITS)) & (uint32_t)0xFFUL);
  }
  else
  {
    SCB->SHPR[(((uint32_t)IRQn) & 0xFUL)-4UL] = (uint8_t)((priority << (8U - __NVIC_PRIO_BITS)) & (uint32_t)0xFFUL);
  }
}


/**
  \brief   Get Interrupt Priority
  \details Reads the priority of a device specific interrupt or a processor exception.
           The interrupt number can be positive to specify a device specific interrupt,
           or negative to specify a processor exception.
  \param [in]   IRQn  Interrupt number.
  \return             Interrupt Priority.
                      Value is aligned automatically to the implemented priority bits of the microcontroller.
 */
__STATIC_INLINE uint32_t __NVIC_GetPriority(IRQn_Type IRQn)
{

  if ((int32_t)(IRQn) >= 0)
  {
    return(((uint32_t)NVIC->IPR[((uint32_t)IRQn)]               >> (8U - __NVIC_PRIO_BITS)));
  }
  else
  {
    return(((uint32_t)SCB->SHPR[(((uint32_t)IRQn) & 0xFUL)-4UL] >> (8U - __NVIC_PRIO_BITS)));
  }
}


/**
  \brief   Encode Priority
  \details Encodes the priority for an interrupt with the given priority group,
           preemptive priority value, and subpriority value.
           In case of a conflict between priority grouping and available
           priority bits (__NVIC_PRIO_BITS), the smallest possible priority group is set.
  \param [in]     PriorityGroup  Used priority group.
  \param [in]   PreemptPriority  Preemptive priority value (starting from 0).
  \param [in]       SubPriority  Subpriority value (starting from 0).
  \return                        Encoded priority. Value can be used in the function \ref NVIC_SetPriority().
 */
__STATIC_INLINE uint32_t NVIC_EncodePriority (uint32_t PriorityGroup, uint32_t PreemptPriority, uint32_t SubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07UL);   /* only values 0..7 are used          */
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7UL - PriorityGroupTmp) > (uint32_t)(__NVIC_PRIO_BITS)) ? (uint32_t)(__NVIC_PRIO_BITS) : (uint32_t)(7UL - PriorityGroupTmp);
  SubPriorityBits     = ((PriorityGroupTmp + (uint32_t)(__NVIC_PRIO_BITS)) < (uint32_t)7UL) ? (uint32_t)0UL : (uint32_t)((PriorityGroupTmp - 7UL) + (uint32_t)(__NVIC_PRIO_BITS));

  return (
           ((PreemptPriority & (uint32_t)((1UL << (PreemptPriorityBits)) - 1UL)) << SubPriorityBits) |
           ((SubPriority     & (uint32_t)((1UL << (SubPriorityBits    )) - 1UL)))
         );
}


/**
  \brief   Decode Priority
  \details Decodes an interrupt priority value with a given priority group to
           preemptive priority value and subpriority value.
           In case of a conflict between priority grouping and available
           priority bits (__NVIC_PRIO_BITS) the smallest possible priority group is set.
  \param [in]         Priority   Priority value, which can be retrieved with the function \ref NVIC_GetPriority().
  \param [in]     PriorityGroup  Used priority group.
  \param [out] pPreemptPriority  Preemptive priority value (starting from 0).
  \param [out]     pSubPriority  Subpriority value (starting from 0).
 */
__STATIC_INLINE void NVIC_DecodePriority (uint32_t Priority, uint32_t PriorityGroup, uint32_t* const pPreemptPriority, uint32_t* const pSubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07UL);   /* only values 0..7 are used          */
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7UL - PriorityGroupTmp) > (uint32_t)(__NVIC_PRIO_BITS)) ? (uint32_t)(__NVIC_PRIO_BITS) : (uint32_t)(7UL - PriorityGroupTmp);
  SubPriorityBits     = ((PriorityGroupTmp + (uint32_t)(__NVIC_PRIO_BITS)) < (uint32_t)7UL) ? (uint32_t)0UL : (uint32_t)((PriorityGroupTmp - 7UL) + (uint32_t)(__NVIC_PRIO_BITS));

  *pPreemptPriority = (Priority >> SubPriorityBits) & (uint32_t)((1UL << (PreemptPriorityBits)) - 1UL);
  *pSubPriority     = (Priority                   ) & (uint32_t)((1UL << (SubPriorityBits    )) - 1UL);
}


/**
  \brief   Set Interrupt Vector
  \details Sets an interrupt vector in SRAM based interrupt vector table.
           The interrupt number can be positive to specify a device specific interrupt,
           or negative to specify a processor exception.
           VTOR must been relocated to SRAM before.
  \param [in]   IRQn      Interrupt number
  \param [in]   vector    Address of interrupt handler function
 */
__STATIC_INLINE void __NVIC_SetVector(IRQn_Type IRQn, uint32_t vector)
{
  uint32_t *vectors = (uint32_t *)SCB->VTOR;
  vectors[(int32_t)IRQn + NVIC_USER_IRQ_OFFSET] = vector;
  __DSB();
}


/**
  \brief   Get Interrupt Vector
  \details Reads an interrupt vector from interrupt vector table.
           The interrupt number can be positive to specify a device specific interrupt,
           or negative to specify a processor exception.
  \param [in]   IRQn      Interrupt number.
  \return                 Address of interrupt handler function
 */
__STATIC_INLINE uint32_t __NVIC_GetVector(IRQn_Type IRQn)
{
  uint32_t *vectors = (uint32_t *)SCB->VTOR;
  return vectors[(int32_t)IRQn + NVIC_USER_IRQ_OFFSET];
}


/**
  \brief   System Reset
  \details Initiates a system reset request to reset the MCU.
 */
__NO_RETURN __STATIC_INLINE void __NVIC_SystemReset(void)
{
  __DSB();                                                          /* Ensure all outstanding memory accesses included
                                                                       buffered write are completed before reset */
  SCB->AIRCR  = (uint32_t)((0x5FAUL << SCB_AIRCR_VECTKEY_Pos)    |
                           (SCB->AIRCR & SCB_AIRCR_PRIGROUP_Msk) |
                            SCB_AIRCR_SYSRESETREQ_Msk    );         /* Keep priority group unchanged */
  __DSB();                                                          /* Ensure completion of memory access */

  for(;;)                                                           /* wait until reset */
  {
    __NOP();
  }
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  \brief   Set Priority Grouping (non-secure)
  \details Sets the non-secure priority grouping field when in secure state using the required unlock sequence.
           The parameter PriorityGroup is assigned to the field SCB->AIRCR [10:8] PRIGROUP field.
           Only values from 0..7 are used.
           In case of a conflict between priority grouping and available
           priority bits (__NVIC_PRIO_BITS), the smallest possible priority group is set.
  \param [in]      PriorityGroup  Priority grouping field.
 */
__STATIC_INLINE void TZ_NVIC_SetPriorityGrouping_NS(uint32_t PriorityGroup)
{
  uint32_t reg_value;
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07UL);             /* only values 0..7 are used          */

  reg_value  =  SCB_NS->AIRCR;                                                /* read old register configuration    */
  reg_value &= ~((uint32_t)(SCB_AIRCR_VECTKEY_Msk | SCB_AIRCR_PRIGROUP_Msk)); /* clear bits to change               */
  reg_value  =  (reg_value                                   |
                ((uint32_t)0x5FAUL << SCB_AIRCR_VECTKEY_Pos) |
                (PriorityGroupTmp << SCB_AIRCR_PRIGROUP_Pos)  );              /* Insert write key and priority group */
  SCB_NS->AIRCR =  reg_value;
}


/**
  \brief   Get Priority Grouping (non-secure)
  \details Reads the priority grouping field from the non-secure NVIC when in secure state.
  \return                Priority grouping field (SCB->AIRCR [10:8] PRIGROUP field).
 */
__STATIC_INLINE uint32_t TZ_NVIC_GetPriorityGrouping_NS(void)
{
  return ((uint32_t)((SCB_NS->AIRCR & SCB_AIRCR_PRIGROUP_Msk) >> SCB_AIRCR_PRIGROUP_Pos));
}


/**
  \brief   Enable Interrupt (non-secure)
  \details Enables a device specific interrupt in the non-secure NVIC interrupt controller when in secure state.
  \param [in]      IRQn  Device specific interrupt number.
  \note    IRQn must not be negative.
 */
__STATIC_INLINE void TZ_NVIC_EnableIRQ_NS(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    NVIC_NS->ISER[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  }
}


/**
  \brief   Get Interrupt Enable status (non-secure)
  \details Returns a device specific interrupt enable status from the non-secure NVIC interrupt controller when in secure state.
  \param [in]      IRQn  Device specific interrupt number.
  \return             0  Interrupt is not enabled.
  \return             1  Interrupt is enabled.
  \note    IRQn must not be negative.
 */
__STATIC_INLINE uint32_t TZ_NVIC_GetEnableIRQ_NS(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((NVIC_NS->ISER[(((uint32_t)IRQn) >> 5UL)] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }
  else
  {
    return(0U);
  }
}


/**
  \brief   Disable Interrupt (non-secure)
  \details Disables a device specific interrupt in the non-secure NVIC interrupt controller when in secure state.
  \param [in]      IRQn  Device specific interrupt number.
  \note    IRQn must not be negative.
 */
__STATIC_INLINE void TZ_NVIC_DisableIRQ_NS(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    NVIC_NS->ICER[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  }
}


/**
  \brief   Get Pending Interrupt (non-secure)
  \details Reads the NVIC pending register in the non-secure NVIC when in secure state and returns the pending bit for the specified device specific interrupt.
  \param [in]      IRQn  Device specific interrupt number.
  \return             0  Interrupt status is not pending.
  \return             1  Interrupt status is pending.
  \note    IRQn must not be negative.
 */
__STATIC_INLINE uint32_t TZ_NVIC_GetPendingIRQ_NS(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((NVIC_NS->ISPR[(((uint32_t)IRQn) >> 5UL)] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }
  else
  {
    return(0U);
  }
}


/**
  \brief   Set Pending Interrupt (non-secure)
  \details Sets the pending bit of a device specific interrupt in the non-secure NVIC pending register when in secure state.
  \param [in]      IRQn  Device specific interrupt number.
  \note    IRQn must not be negative.
 */
__STATIC_INLINE void TZ_NVIC_SetPendingIRQ_NS(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    NVIC_NS->ISPR[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  }
}


/**
  \brief   Clear Pending Interrupt (non-secure)
  \details Clears the pending bit of a device specific interrupt in the non-secure NVIC pending register when in secure state.
  \param [in]      IRQn  Device specific interrupt number.
  \note    IRQn must not be negative.
 */
__STATIC_INLINE void TZ_NVIC_ClearPendingIRQ_NS(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    NVIC_NS->ICPR[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  }
}


/**
  \brief   Get Active Interrupt (non-secure)
  \details Reads the active register in non-secure NVIC when in secure state and returns the active bit for the device specific interrupt.
  \param [in]      IRQn  Device specific interrupt number.
  \return             0  Interrupt status is not active.
  \return             1  Interrupt status is active.
  \note    IRQn must not be negative.
 */
__STATIC_INLINE uint32_t TZ_NVIC_GetActive_NS(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((NVIC_NS->IABR[(((uint32_t)IRQn) >> 5UL)] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }
  else
  {
    return(0U);
  }
}


/**
  \brief   Set Interrupt Priority (non-secure)
  \details Sets the priority of a non-secure device specific interrupt or a non-secure processor exception when in secure state.
           The interrupt number can be positive to specify a device specific interrupt,
           or negative to specify a processor exception.
  \param [in]      IRQn  Interrupt number.
  \param [in]  priority  Priority to set.
  \note    The priority cannot be set for every non-secure processor exception.
 */
__STATIC_INLINE void TZ_NVIC_SetPriority_NS(IRQn_Type IRQn, uint32_t priority)
{
  if ((int32_t)(IRQn) >= 0)
  {
    NVIC_NS->IPR[((uint32_t)IRQn)]               = (uint8_t)((priority << (8U - __NVIC_PRIO_BITS)) & (uint32_t)0xFFUL);
  }
  else
  {
    SCB_NS->SHPR[(((uint32_t)IRQn) & 0xFUL)-4UL] = (uint8_t)((priority << (8U - __NVIC_PRIO_BITS)) & (uint32_t)0xFFUL);
  }
}


/**
  \brief   Get Interrupt Priority (non-secure)
  \details Reads the priority of a non-secure device specific interrupt or a non-secure processor exception when in secure state.
           The interrupt number can be positive to specify a device specific interrupt,
           or negative to specify a processor exception.
  \param [in]   IRQn  Interrupt number.
  \return             Interrupt Priority. Value is aligned automatically to the implemented priority bits of the microcontroller.
 */
__STATIC_INLINE uint32_t TZ_NVIC_GetPriority_NS(IRQn_Type IRQn)
{

  if ((int32_t)(IRQn) >= 0)
  {
    return(((uint32_t)NVIC_NS->IPR[((uint32_t)IRQn)]               >> (8U - __NVIC_PRIO_BITS)));
  }
  else
  {
    return(((uint32_t)SCB_NS->SHPR[(((uint32_t)IRQn) & 0xFUL)-4UL] >> (8U - __NVIC_PRIO_BITS)));
  }
}
#endif /*  defined (__ARM_FEATURE_CMSE) &&(__ARM_FEATURE_CMSE == 3U) */

/*@} end of CMSIS_Core_NVICFunctions */

/* ##########################  MPU functions  #################################### */

#if defined (__MPU_PRESENT) && (__MPU_PRESENT == 1U)

#include "mpu_armv8.h"

#endif

/* ##########################  FPU functions  #################################### */
/**
  \ingroup  CMSIS_Core_FunctionInterface
  \defgroup CMSIS_Core_FpuFunctions FPU Functions
  \brief    Function that provides FPU type.
  @{
 */

/**
  \brief   get FPU type
  \details returns the FPU type
  \returns
   - \b  0: No FPU
   - \b  1: Single precision FPU
   - \b  2: Double + Single precision FPU
 */
__STATIC_INLINE uint32_t SCB_GetFPUType(void)
{
  uint32_t mvfr0;

  mvfr0 = FPU->MVFR0;
  if      ((mvfr0 & (FPU_MVFR0_Single_precision_Msk | FPU_MVFR0_Double_precision_Msk)) == 0x220U)
  {
    return 2U;           /* Double + Single precision FPU */
  }
  else if ((mvfr0 & (FPU_MVFR0_Single_precision_Msk | FPU_MVFR0_Double_precision_Msk)) == 0x020U)
  {
    return 1U;           /* Single precision FPU */
  }
  else
  {
    return 0U;           /* No FPU */
  }
}


/*@} end of CMSIS_Core_FpuFunctions */



/* ##########################   SAU functions  #################################### */
/**
  \ingroup  CMSIS_Core_FunctionInterface
  \defgroup CMSIS_Core_SAUFunctions SAU Functions
  \brief    Functions that configure the SAU.
  @{
 */

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)

/**
  \brief   Enable SAU
  \details Enables the Security Attribution Unit (SAU).
 */
__STATIC_INLINE void TZ_SAU_Enable(void)
{
    SAU->CTRL |=  (SAU_CTRL_ENABLE_Msk);
}



/**
  \brief   Disable SAU
  \details Disables the Security Attribution Unit (SAU).
 */
__STATIC_INLINE void TZ_SAU_Disable(void)
{
    SAU->CTRL &= ~(SAU_CTRL_ENABLE_Msk);
}

#endif /* defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

/*@} end of CMSIS_Core_SAUFunctions */




/* ##################################    Debug Control function  ############################################ */
/**
  \ingroup  CMSIS_Core_FunctionInterface
  \defgroup CMSIS_Core_DCBFunctions Debug Control Functions
  \brief    Functions that access the Debug Control Block.
  @{
 */

 
/**
  \brief   Set Debug Authentication Control Register
  \details writes to Debug Authentication Control register.
  \param [in]  value  value to be writen.
 */
__STATIC_INLINE void DCB_SetAuthCtrl(uint32_t value)
{
    __DSB();
    __ISB();
    DCB->DAUTHCTRL = value;
    __DSB();
    __ISB();
}


/**
  \brief   Get Debug Authentication Control Register
  \details Reads Debug Authentication Control register.
  \return             Debug Authentication Control Register.
 */
__STATIC_INLINE uint32_t DCB_GetAuthCtrl(void)
{
    return (DCB->DAUTHCTRL);
}


#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  \brief   Set Debug Authentication Control Register (non-secure)
  \details writes to non-secure Debug Authentication Control register when in secure state.
  \param [in]  value  value to be writen
 */
__STATIC_INLINE void TZ_DCB_SetAuthCtrl_NS(uint32_t value)
{
    __DSB();
    __ISB();
    DCB_NS->DAUTHCTRL = value;
    __DSB();
    __ISB();
}


/**
  \brief   Get Debug Authentication Control Register (non-secure)
  \details Reads non-secure Debug Authentication Control register when in secure state.
  \return             Debug Authentication Control Register.
 */
__STATIC_INLINE uint32_t TZ_DCB_GetAuthCtrl_NS(void)
{
    return (DCB_NS->DAUTHCTRL);
}
#endif /* defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

/*@} end of CMSIS_Core_DCBFunctions */




/* ##################################    Debug Identification function  ############################################ */
/**
  \ingroup  CMSIS_Core_FunctionInterface
  \defgroup CMSIS_Core_DIBFunctions Debug Identification Functions
  \brief    Functions that access the Debug Identification Block.
  @{
 */

 
/**
  \brief   Get Debug Authentication Status Register
  \details Reads Debug Authentication Status register.
  \return             Debug Authentication Status Register.
 */
__STATIC_INLINE uint32_t DIB_GetAuthStatus(void)
{
    return (DIB->DAUTHSTATUS);
}


#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  \brief   Get Debug Authentication Status Register (non-secure)
  \details Reads non-secure Debug Authentication Status register when in secure state.
  \return             Debug Authentication Status Register.
 */
__STATIC_INLINE uint32_t TZ_DIB_GetAuthStatus_NS(void)
{
    return (DIB_NS->DAUTHSTATUS);
}
#endif /* defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

/*@} end of CMSIS_Core_DCBFunctions */




/* ##################################    SysTick function  ############################################ */
/**
  \ingroup  CMSIS_Core_FunctionInterface
  \defgroup CMSIS_Core_SysTickFunctions SysTick Functions
  \brief    Functions that configure the System.
  @{
 */

#if defined (__Vendor_SysTickConfig) && (__Vendor_SysTickConfig == 0U)

/**
  \brief   System Tick Configuration
  \details Initializes the System Timer and its interrupt, and starts the System Tick Timer.
           Counter is in free running mode to generate periodic interrupts.
  \param [in]  ticks  Number of ticks between two interrupts.
  \return          0  Function succeeded.
  \return          1  Function failed.
  \note    When the variable <b>__Vendor_SysTickConfig</b> is set to 1, then the
           function <b>SysTick_Config</b> is not included. In this case, the file <b><i>device</i>.h</b>
           must contain a vendor-specific implementation of this function.
 */
__STATIC_INLINE uint32_t SysTick_Config(uint32_t ticks)
{
  if ((ticks - 1UL) > SysTick_LOAD_RELOAD_Msk)
  {
    return (1UL);                                                   /* Reload value impossible */
  }

  SysTick->LOAD  = (uint32_t)(ticks - 1UL);                         /* set reload register */
  NVIC_SetPriority (SysTick_IRQn, (1UL << __NVIC_PRIO_BITS) - 1UL); /* set Priority for Systick Interrupt */
  SysTick->VAL   = 0UL;                                             /* Load the SysTick Counter Value */
  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |
                   SysTick_CTRL_TICKINT_Msk   |
                   SysTick_CTRL_ENABLE_Msk;                         /* Enable SysTick IRQ and SysTick Timer */
  return (0UL);                                                     /* Function successful */
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  \brief   System Tick Configuration (non-secure)
  \details Initializes the non-secure System Timer and its interrupt when in secure state, and starts the System Tick Timer.
           Counter is in free running mode to generate periodic interrupts.
  \param [in]  ticks  Number of ticks between two interrupts.
  \return          0  Function succeeded.
  \return          1  Function failed.
  \note    When the variable <b>__Vendor_SysTickConfig</b> is set to 1, then the
           function <b>TZ_SysTick_Config_NS</b> is not included. In this case, the file <b><i>device</i>.h</b>
           must contain a vendor-specific implementation of this function.

 */
__STATIC_INLINE uint32_t TZ_SysTick_Config_NS(uint32_t ticks)
{
  if ((ticks - 1UL) > SysTick_LOAD_RELOAD_Msk)
  {
    return (1UL);                                                         /* Reload value impossible */
  }

  SysTick_NS->LOAD  = (uint32_t)(ticks - 1UL);                            /* set reload register */
  TZ_NVIC_SetPriority_NS (SysTick_IRQn, (1UL << __NVIC_PRIO_BITS) - 1UL); /* set Priority for Systick Interrupt */
  SysTick_NS->VAL   = 0UL;                                                /* Load the SysTick Counter Value */
  SysTick_NS->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |
                      SysTick_CTRL_TICKINT_Msk   |
                      SysTick_CTRL_ENABLE_Msk;                            /* Enable SysTick IRQ and SysTick Timer */
  return (0UL);                                                           /* Function successful */
}
#endif /* defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

#endif

/*@} end of CMSIS_Core_SysTickFunctions */



/* ##################################### Debug In/Output function ########################################### */
/**
  \ingroup  CMSIS_Core_FunctionInterface
  \defgroup CMSIS_core_DebugFunctions ITM Functions
  \brief    Functions that access the ITM debug interface.
  @{
 */

extern volatile int32_t ITM_RxBuffer;                              /*!< External variable to receive characters. */
#define                 ITM_RXBUFFER_EMPTY  ((int32_t)0x5AA55AA5U) /*!< Value identifying \ref ITM_RxBuffer is ready for next character. */


/**
  \brief   ITM Send Character
  \details Transmits a character via the ITM channel 0, and
           \li Just returns when no debugger is connected that has booked the output.
           \li Is blocking when a debugger is connected, but the previous character sent has not been transmitted.
  \param [in]     ch  Character to transmit.
  \returns            Character to transmit.
 */
__STATIC_INLINE uint32_t ITM_SendChar (uint32_t ch)
{
  if (((ITM->TCR & ITM_TCR_ITMENA_Msk) != 0UL) &&      /* ITM enabled */
      ((ITM->TER & 1UL               ) != 0UL)   )     /* ITM Port #0 enabled */
  {
    while (ITM->PORT[0U].u32 == 0UL)
    {
      __NOP();
    }
    ITM->PORT[0U].u8 = (uint8_t)ch;
  }
  return (ch);
}


/**
  \brief   ITM Receive Character
  \details Inputs a character via the external variable \ref ITM_RxBuffer.
  \return             Received character.
  \return         -1  No character pending.
 */
__STATIC_INLINE int32_t ITM_ReceiveChar (void)
{
  int32_t ch = -1;                           /* no character available */

  if (ITM_RxBuffer != ITM_RXBUFFER_EMPTY)
  {
    ch = ITM_RxBuffer;
    ITM_RxBuffer = ITM_RXBUFFER_EMPTY;       /* ready for next character */
  }

  return (ch);
}


/**
  \brief   ITM Check Character
  \details Checks whether a character is pending for reading in the variable \ref ITM_RxBuffer.
  \return          0  No character available.
  \return          1  Character available.
 */
__STATIC_INLINE int32_t ITM_CheckChar (void)
{

  if (ITM_RxBuffer == ITM_RXBUFFER_EMPTY)
  {
    return (0);                              /* no character available */
  }
  else
  {
    return (1);                              /*    character available */
  }
}

/*@} end of CMSIS_core_DebugFunctions */




#ifdef __cplusplus
}
#endif

#endif /* __CORE_CM35P_H_DEPENDANT */

#endif /* __CMSIS_GENERIC */
