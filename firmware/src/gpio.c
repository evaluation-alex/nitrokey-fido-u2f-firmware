/*
 * Copyright (c) 2016, Conor Patrick
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 *
 * gpio.c
 * 		This file contains the GPIO access functions.
 * 		It provides abstractions for access to the LED as well as the user button.
 *
 */
#include <SI_EFM8UB3_Register_Enums.h>

#include "bsp.h"


#define ms_since(ms,num) (((uint16_t)get_ms() - (ms)) >= num ? ((ms=(uint16_t)get_ms())):0)

typedef enum {
	BST_UNPRESSED,
	BST_PRESSED_RECENTLY,
	BST_PRESSED_REGISTERED,

	BST_MAX_NUM
} BUTTON_STATE_T;

data  uint32_t        ButtonPressT;                   // Timer for TaskButton() timings
data  BUTTON_STATE_T  ButtonState = BST_UNPRESSED;    // Holds the actual registered logical state of the button

static data uint32_t  LedBlinkTmr;                    // Timer for TaskLedBlink() timings
static data uint16_t  LedBlinkPeriodT;                // Period time register
static data uint8_t   LedBlinkNum;                    // Blink number counter, also an indicator if blinking is on

void TaskButton (void) {                              // Requires at least a 750ms long button press to register a valid user button press
	if (IS_BUTTON_PRESSED()) {                        // Button's physical state: pressed
		switch (ButtonState) {                        // Handle press phase
		    case BST_UNPRESSED: {                     // It happened at this moment
				ButtonState  = BST_PRESSED_RECENTLY;  // Update button state
				ButtonPressT = get_ms();              // Start measure press time
		    }break;
		    case BST_PRESSED_RECENTLY: {              // Button is already pressed, press time measurement is ongoing
				if (get_ms() - ButtonPressT >= BUTTON_MIN_PRESS_T_MS) { // Press time reached the critical value to register a valid user touch
				    ButtonState = BST_PRESSED_REGISTERED; // Update button state
				}
		    }break;
		    default: {}break;
		}
	} else {                                          // Button is unprssed
		ButtonState = BST_UNPRESSED;                  // Update button state
	}
}

uint8_t IsButtonPressed (void) {
	return ((ButtonState == BST_PRESSED_REGISTERED)? 1 : 0);
}


void LedOn (void) {
	LedBlinkNum = 0;                                  // Stop ongoing blinking
	LED_ON();                                         // LED physical state -> ON
}

void LedOff (void) {
	LedBlinkNum = 0;                                  // Stop ongoing blinking
	LED_OFF();                                        // LED physical state -> OFF
}

void LedBlink (uint8_t blink_num, uint16_t period_t) {
	LedBlinkNum     = blink_num;
	LedBlinkPeriodT = period_t;
	LedBlinkTmr     = get_ms();
    LED_ON();
}

void TaskLedBlink (void) {
	if (LedBlinkNum) {                                     // LED blinking is on
		if (IS_LED_ON()) {                                 // ON state
			if (get_ms() - LedBlinkTmr >= LED_BLINK_T_ON) { // ON time expired
				LED_OFF();                                 // LED physical state -> OFF
				if (LedBlinkNum) {                         // It isnt the last blink round: initialize OFF state:
					LedBlinkTmr   = get_ms();		       // Init OFF timer
					if (LedBlinkNum != 255) {              // Not endless blinking:
						LedBlinkNum--;                     // Update the remaining blink num
					}
				}
			}
		} else {                                           // OFF state
			if (get_ms() - LedBlinkTmr >= LED_BLINK_T_OFF) { // OFF time expired
				LED_ON();                                  // LED physical state -> ON
				LedBlinkTmr   = get_ms();		           // Init ON timer
			}
		}
	}
}
