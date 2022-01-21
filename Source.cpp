#include"Header.h" // Utility and predefines

//https://www.cs.rit.edu/~ncs/color/t_convert.html
GMEXPORT double gm_RGBToHSV(float* rgb_buffer_addr, float* hsv_buffer_addr) {

	ClampBuffer(rgb_buffer_addr); // clamp values so it doesn't go all screwy

	float min = fmin(fmin(RGB_RED, RGB_GREEN), RGB_BLUE);
	float max = fmax(fmax(RGB_RED, RGB_GREEN), RGB_BLUE);
	float delta = max - min;

	HSV_VAL = max;

	if (max != 0) {
		HSV_SAT = delta / max;
	}
	else {
		HSV_SAT = 0;
		HSV_HUE = -1;
		return 1;
	}

	if (RGB_RED == max) {
		HSV_HUE = (RGB_GREEN - RGB_BLUE) / delta;
	}
	else if (RGB_GREEN == max) {
		HSV_HUE = 2.0f + (RGB_BLUE - RGB_RED) / delta;
	}
	else {
		HSV_HUE = 4.0f + (RGB_RED - RGB_GREEN) / delta;
	}

	HSV_HUE *= 60;
	if (HSV_HUE < 0) {
		HSV_HUE += 360;
	}

	HSV_HUE /= 360;

	return 1;

}

/* PRIORITY: Currently have a little "bug" where blue gets set to 1 if hue is 1 (red) for some reason... */
GMEXPORT double gm_HSVToRGB(float* hsv_buffer_addr, float* rgb_buffer_addr) {

	ClampBuffer(hsv_buffer_addr); // clamp values so it doesn't go all screwy
	
	if (HSV_HUE == 1) HSV_HUE = 0; // This is necessary to stop the HUE value of 360 causing blue to be 1 for some reason...

	int i;

	float f, p, q, t;
	if (HSV_SAT == 0) {	// grayscale
		RGB_RED = RGB_GREEN = RGB_BLUE = HSV_VAL;
		return 0;
	}

	float h = (HSV_HUE * 360) / 60; 
	i = (int)floor(h);
	f = h - i;
	p = HSV_VAL * (1 - HSV_SAT);
	q = HSV_VAL * (1 - HSV_SAT * f);
	t = HSV_VAL * (1 - HSV_SAT * (1 - f));

	switch (i) {
	case 0:
		RGB_RED = HSV_VAL;
		RGB_GREEN = t;
		RGB_BLUE = p;
		return 0;
		break;
	case 1:
		RGB_RED = q;
		RGB_GREEN = HSV_VAL;
		RGB_BLUE = p;
		return 1;
		break;
	case 2:
		RGB_RED = p;
		RGB_GREEN = HSV_VAL;
		RGB_BLUE = t;
		return 2;
		break;
	case 3:
		RGB_RED = p;
		RGB_GREEN = q;
		RGB_BLUE = HSV_VAL;
		return 3;
		break;
	case 4:
		RGB_RED = t;
		RGB_GREEN = p;
		RGB_BLUE = HSV_VAL;
		return 4;
		break;
	default:	// NOTE: Q for some reason at this point is 1, which means that despite HUE being 1 (RED) it still turns blue 1.0 - Find out what's up with that.
		RGB_RED = HSV_VAL;
		RGB_GREEN = p;
		RGB_BLUE = q;
		return 5;
		break;
	}

	return -2; // something might have gone wrong if we got here...

}

// Trying new implementations of HSV to RGB from elsewhere. https://stackoverflow.com/questions/3018313/algorithm-to-convert-rgb-to-hsv-and-hsv-to-rgb-in-range-0-255-for-both
GMEXPORT double gm_new_HSVToRGB(float* hsv_buffer_addr, float* rgb_buffer_addr) {

	return -1;
}

// Convert values between different color spaces
GMEXPORT double gm_Convert(float* color_space_in, float* color_space_out) {
	switch ((int)color_space_in[3]) {
		case 0 :	// from HUE
			break;
		case 1:		// from SAT
			break;

		case 2:		// from VAL
			break;
	}
}
