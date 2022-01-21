#pragma once
#include<Math.h>

#define GMEXPORT extern "C" __declspec(dllexport)

#define RGB_RED rgb_buffer_addr[0]
#define RGB_GREEN rgb_buffer_addr[1]
#define RGB_BLUE rgb_buffer_addr[2]

#define HSV_HUE hsv_buffer_addr[0]
#define HSV_SAT hsv_buffer_addr[1]
#define HSV_VAL hsv_buffer_addr[2]

void ClampValue(float* value) {	// clamps the value contained at the address of value
	if (*value < 0.0f) {
		*value = 0.0f;
	}
	else if (*value > 1.0f) {
		*value = 1.0f;
	}
}

void ClampBuffer(float* buffer) { // Clamps the buffer between 0-1
	ClampValue(&buffer[0]);	// clamp the value at the address of the 0th offset of our buffer
	ClampValue(&buffer[1]); // clamp the value at the address of the 1st offset of our buffer
	ClampValue(&buffer[2]); // clamp the value at the address of the 2nd offset of our buffer
}