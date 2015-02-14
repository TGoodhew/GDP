// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "arduino.h"
#include "spi.h"

// Software SPI
//  U8GLIB_LM6059(sck, mosi, cs, a0 [, reset]) 

//U8GLIB_LM6059 u8g(13, 11, 8, 10, 9);
//U8GLIB_LM6059_2X u8g(13, 11, 8, 10, 9);

// Hardware SPI
//	U8GLIB_LM6059(cs, a0[, reset])
U8GLIB_LM6059 u8g(7, 6, 9);

int _tmain(int argc, _TCHAR* argv[])
{
    return RunArduinoSketch();
}

//void draw(void) {
//	// graphic commands to redraw the complete screen should be placed here  
//	u8g.setFont(u8g_font_unifont);
//	//u8g.setFont(u8g_font_osb21);
//	u8g.drawStr(0, 22, "Hello World!");
//}
//
//void setup(void) {
//
//	// flip screen, if required
//	// u8g.setRot180();
//
//	// set SPI backup if required
//	//u8g.setHardwareBackup(u8g_backup_avr_spi);
//
//	// assign default color value
//	if (u8g.getMode() == U8G_MODE_R3G3B2) {
//		u8g.setColorIndex(255);     // white
//	}
//	else if (u8g.getMode() == U8G_MODE_GRAY2BIT) {
//		u8g.setColorIndex(3);         // max intensity
//	}
//	else if (u8g.getMode() == U8G_MODE_BW) {
//		u8g.setColorIndex(1);         // pixel on
//	}
//	else if (u8g.getMode() == U8G_MODE_HICOLOR) {
//		u8g.setHiColorByRGB(255, 255, 255);
//	}
//}
//
//void loop(void) {
//	// picture loop
//	u8g.firstPage();
//	do {
//		draw();
//	} while (u8g.nextPage());
//
//	// rebuild the picture after some delay
//	delay(50);
//}

//void u8g_prepare(void) {
//	u8g.setFont(u8g_font_6x10);
//	u8g.setFontRefHeightExtendedText();
//	u8g.setDefaultForegroundColor();
//	u8g.setFontPosTop();
//}
//
//void u8g_box_frame(uint8_t a) {
//	u8g.drawStr(0, 0, "drawBox");
//	u8g.drawBox(5, 10, 20, 10);
//	u8g.drawBox(10 + a, 15, 30, 7);
//	u8g.drawStr(0, 30, "drawFrame");
//	u8g.drawFrame(5, 10 + 30, 20, 10);
//	u8g.drawFrame(10 + a, 15 + 30, 30, 7);
//}
//
//void u8g_disc_circle(uint8_t a) {
//	u8g.drawStr(0, 0, "drawDisc");
//	u8g.drawDisc(10, 18, 9);
//	u8g.drawDisc(24 + a, 16, 7);
//	u8g.drawStr(0, 30, "drawCircle");
//	u8g.drawCircle(10, 18 + 30, 9);
//	u8g.drawCircle(24 + a, 16 + 30, 7);
//}
//
//void u8g_r_frame(uint8_t a) {
//	u8g.drawStr(0, 0, "drawRFrame/Box");
//	u8g.drawRFrame(5, 10, 40, 30, a + 1);
//	u8g.drawRBox(50, 10, 25, 40, a + 1);
//}
//
//void u8g_string(uint8_t a) {
//	u8g.drawStr(30 + a, 31, " 0");
//	u8g.drawStr90(30, 31 + a, " 90");
//	u8g.drawStr180(30 - a, 31, " 180");
//	u8g.drawStr270(30, 31 - a, " 270");
//}
//
//void u8g_line(uint8_t a) {
//	u8g.drawStr(0, 0, "drawLine");
//	u8g.drawLine(7 + a, 10, 40, 55);
//	u8g.drawLine(7 + a * 2, 10, 60, 55);
//	u8g.drawLine(7 + a * 3, 10, 80, 55);
//	u8g.drawLine(7 + a * 4, 10, 100, 55);
//}
//
//void u8g_triangle(uint8_t a) {
//	uint16_t offset = a;
//	u8g.drawStr(0, 0, "drawTriangle");
//	u8g.drawTriangle(14, 7, 45, 30, 10, 40);
//	u8g.drawTriangle(14 + offset, 7 - offset, 45 + offset, 30 - offset, 57 + offset, 10 - offset);
//	u8g.drawTriangle(57 + offset * 2, 10, 45 + offset * 2, 30, 86 + offset * 2, 53);
//	u8g.drawTriangle(10 + offset, 40 + offset, 45 + offset, 30 + offset, 86 + offset, 53 + offset);
//}
//
//void u8g_ascii_1() {
//	char s[2] = " ";
//	uint8_t x, y;
//	u8g.drawStr(0, 0, "ASCII page 1");
//	for (y = 0; y < 6; y++) {
//		for (x = 0; x < 16; x++) {
//			s[0] = y * 16 + x + 32;
//			u8g.drawStr(x * 7, y * 10 + 10, s);
//		}
//	}
//}
//
//void u8g_ascii_2() {
//	char s[2] = " ";
//	uint8_t x, y;
//	u8g.drawStr(0, 0, "ASCII page 2");
//	for (y = 0; y < 6; y++) {
//		for (x = 0; x < 16; x++) {
//			s[0] = y * 16 + x + 160;
//			u8g.drawStr(x * 7, y * 10 + 10, s);
//		}
//	}
//}
//
//void u8g_extra_page(uint8_t a)
//{
//	if (u8g.getMode() == U8G_MODE_HICOLOR || u8g.getMode() == U8G_MODE_R3G3B2) {
//		/* draw background (area is 128x128) */
//		u8g_uint_t r, g, b;
//		b = a << 5;
//		for (g = 0; g < 64; g++)
//		{
//			for (r = 0; r < 64; r++)
//			{
//				u8g.setRGB(r << 2, g << 2, b);
//				u8g.drawPixel(g, r);
//			}
//		}
//		u8g.setRGB(255, 255, 255);
//		u8g.drawStr(66, 0, "Color Page");
//	}
//	else if (u8g.getMode() == U8G_MODE_GRAY2BIT)
//	{
//		u8g.drawStr(66, 0, "Gray Level");
//		u8g.setColorIndex(1);
//		u8g.drawBox(0, 4, 64, 32);
//		u8g.drawBox(70, 20, 4, 12);
//		u8g.setColorIndex(2);
//		u8g.drawBox(0 + 1 * a, 4 + 1 * a, 64 - 2 * a, 32 - 2 * a);
//		u8g.drawBox(74, 20, 4, 12);
//		u8g.setColorIndex(3);
//		u8g.drawBox(0 + 2 * a, 4 + 2 * a, 64 - 4 * a, 32 - 4 * a);
//		u8g.drawBox(78, 20, 4, 12);
//	}
//	else
//	{
//		u8g.drawStr(0, 12, "setScale2x2");
//		u8g.setScale2x2();
//		u8g.drawStr(0, 6 + a, "setScale2x2");
//		u8g.undoScale();
//	}
//}
//
//
//uint8_t draw_state = 0;
//
//void draw(void) {
//	u8g_prepare();
//	switch (draw_state >> 3) {
//	case 0: u8g_box_frame(draw_state & 7); break;
//	case 1: u8g_disc_circle(draw_state & 7); break;
//	case 2: u8g_r_frame(draw_state & 7); break;
//	case 3: u8g_string(draw_state & 7); break;
//	case 4: u8g_line(draw_state & 7); break;
//	case 5: u8g_triangle(draw_state & 7); break;
//	case 6: u8g_ascii_1(); break;
//	case 7: u8g_ascii_2(); break;
//	case 8: u8g_extra_page(draw_state & 7); break;
//	}
//}
//
//void setup(void) {
//	
//	// flip screen, if required
//	//u8g.setRot180();
//
//
//	//pinMode(13, OUTPUT);
//	//digitalWrite(13, HIGH);
//}
//
//void loop(void) {
//
//	// picture loop  
//	u8g.firstPage();
//	do {
//		draw();
//	} while (u8g.nextPage());
//
//	// increase the state
//	draw_state++;
//	if (draw_state >= 9 * 8)
//		draw_state = 0;
//
//	// rebuild the picture after some delay
//	delay(150);
//
//}


#define SECONDS 10
uint8_t flip_color = 0;
uint8_t draw_color = 1;

void draw_set_screen(void) {
	// graphic commands to redraw the complete screen should be placed here  
	if (u8g.getMode() == U8G_MODE_HICOLOR) {
		if (flip_color == 0)
			u8g.setHiColorByRGB(0, 0, 0);
		else
			u8g.setHiColorByRGB(255, 255, 255);
	}
	else {
		u8g.setColorIndex(flip_color);
	}
	u8g.drawBox(0, 0, u8g.getWidth(), u8g.getHeight());
}

void draw_clip_test(void) {
	u8g_uint_t i, j, k;
	char buf[3] = "AB";
	k = 0;
	if (u8g.getMode() == U8G_MODE_HICOLOR) {
		u8g.setHiColorByRGB(255, 255, 255);
	}
	else {
		u8g.setColorIndex(draw_color);
	}
	u8g.setFont(u8g_font_6x10);

	for (i = 0; i < 6; i++) {
		for (j = 1; j < 8; j++) {
			u8g.drawHLine(i - 3, k, j);
			u8g.drawHLine(i - 3 + 10, k, j);

			u8g.drawVLine(k + 20, i - 3, j);
			u8g.drawVLine(k + 20, i - 3 + 10, j);

			k++;
		}
	}
	u8g.drawStr(0 - 3, 50, buf);
	u8g.drawStr180(0 + 3, 50, buf);

	u8g.drawStr(u8g.getWidth() - 3, 40, buf);
	u8g.drawStr180(u8g.getWidth() + 3, 40, buf);

	u8g.drawStr90(u8g.getWidth() - 10, 0 - 3, buf);
	u8g.drawStr270(u8g.getWidth() - 10, 3, buf);

	u8g.drawStr90(u8g.getWidth() - 20, u8g.getHeight() - 3, buf);
	u8g.drawStr270(u8g.getWidth() - 20, u8g.getHeight() + 3, buf);

}

void draw_char(void) {
	char buf[2] = "@";
	u8g_uint_t i, j;
	// graphic commands to redraw the complete screen should be placed here  
	if (u8g.getMode() == U8G_MODE_HICOLOR) {
		u8g.setHiColorByRGB(255, 255, 255);
	}
	else {
		u8g.setColorIndex(draw_color);
	}
	u8g.setFont(u8g_font_6x10);
	j = 8;
	for (;;) {
		i = 0;
		for (;;) {
			u8g.drawStr(i, j, buf);
			i += 8;
			if (i > u8g.getWidth())
				break;
		}
		j += 8;
		if (j > u8g.getHeight())
			break;
	}

}

void draw_pixel(void) {
	u8g_uint_t x, y, w2, h2;
	if (u8g.getMode() == U8G_MODE_HICOLOR) {
		u8g.setHiColorByRGB(255, 255, 255);
	}
	else {
		u8g.setColorIndex(draw_color);
	}
	w2 = u8g.getWidth();
	h2 = u8g.getHeight();
	w2 /= 2;
	h2 /= 2;
	for (y = 0; y < h2; y++) {
		for (x = 0; x < w2; x++) {
			if ((x + y) & 1) {
				u8g.drawPixel(x, y);
				u8g.drawPixel(x, y + h2);
				u8g.drawPixel(x + w2, y);
				u8g.drawPixel(x + w2, y + h2);
			}
		}
	}
}

// returns unadjusted FPS
uint16_t picture_loop_with_fps(void(*draw_fn)(void)) {
	uint16_t FPS10 = 0;
	uint32_t time;

	time = millis() + SECONDS * 1000;

	// picture loop
	do {
		u8g.firstPage();
		do {
			draw_fn();
		} while (u8g.nextPage());
		FPS10++;
		flip_color = flip_color ^ 1;
	} while (millis() < time);
	return FPS10;
}

const char *convert_FPS(uint16_t fps) {
	static char buf[6];
	strcpy(buf, u8g_u8toa((uint8_t)(fps / 10), 3));
	buf[3] = '.';
	buf[4] = (fps % 10) + '0';
	buf[5] = '\0';
	return buf;
}

void show_result(const char *s, uint16_t fps) {
	// assign default color value
	if (u8g.getMode() == U8G_MODE_HICOLOR) {
		u8g.setHiColorByRGB(255, 255, 255);
	}
	else {
		u8g.setColorIndex(draw_color);
	}
	u8g.setFont(u8g_font_8x13B);
	u8g.firstPage();
	do {
		u8g.drawStr(0, 12, s);
		u8g.drawStr(0, 24, convert_FPS(fps));
	} while (u8g.nextPage());
}

void drawColorBox(void)
{
	u8g_uint_t w, h;
	u8g_uint_t r, g, b;

	w = u8g.getWidth() / 32;
	h = u8g.getHeight() / 8;
	for (b = 0; b < 4; b++)
		for (g = 0; g < 8; g++)
			for (r = 0; r < 8; r++)
			{
				u8g.setColorIndex((r << 5) | (g << 2) | b);
				u8g.drawBox(g*w + b*w * 8, r*h, w, h);
			}
}

void drawLogo(uint8_t d)
{
#ifdef MINI_LOGO
	u8g.setFont(u8g_font_gdr17r);
	u8g.drawStr(0 + d, 22 + d, "U");
	u8g.setFont(u8g_font_gdr20n);
	u8g.drawStr90(17 + d, 8 + d, "8");
	u8g.setFont(u8g_font_gdr17r);
	u8g.drawStr(39 + d, 22 + d, "g");

	u8g.drawHLine(2 + d, 25 + d, 34);
	u8g.drawVLine(32 + d, 22 + d, 12);
#else
	u8g.setFont(u8g_font_gdr25r);
	u8g.drawStr(0 + d, 30 + d, "U");
	u8g.setFont(u8g_font_gdr30n);
	u8g.drawStr90(23 + d, 10 + d, "8");
	u8g.setFont(u8g_font_gdr25r);
	u8g.drawStr(53 + d, 30 + d, "g");

	u8g.drawHLine(2 + d, 35 + d, 47);
	u8g.drawVLine(45 + d, 32 + d, 12);
#endif
}

void drawURL(void)
{
#ifndef MINI_LOGO
	u8g.setFont(u8g_font_4x6);
	if (u8g.getHeight() < 59)
	{
		u8g.drawStr(53, 9, "code.google.com");
		u8g.drawStr(77, 18, "/p/u8glib");
	}
	else
	{
		u8g.drawStr(1, 54, "code.google.com/p/u8glib");
	}
#endif
}


void draw_logo_test(void) {
	if (u8g.getMode() == U8G_MODE_R3G3B2) {
		drawColorBox();
	}
	u8g.setColorIndex(1);
	if (U8G_MODE_GET_BITS_PER_PIXEL(u8g.getMode()) > 1) {
		drawLogo(2);
		u8g.setColorIndex(2);
		drawLogo(1);
		u8g.setColorIndex(3);
	}
	drawLogo(0);
	drawURL();
}

void setup(void) {
	// flip screen, if required
	// u8g.setRot180();

	// assign default color value
	if (u8g.getMode() == U8G_MODE_R3G3B2)
		draw_color = 255;     // white
	else if (u8g.getMode() == U8G_MODE_GRAY2BIT)
		draw_color = 3;         // max intensity
	else if (u8g.getMode() == U8G_MODE_BW)
		draw_color = 1;         // pixel on
	else if (u8g.getMode() == U8G_MODE_HICOLOR) {
		u8g.setHiColorByRGB(255, 255, 255);
	}
}

void loop(void) {
	uint16_t fps;
	fps = picture_loop_with_fps(draw_logo_test);
	show_result("draw logo test", fps);
	delay(5000);
	fps = picture_loop_with_fps(draw_clip_test);
	show_result("draw clip test", fps);
	delay(5000);
	fps = picture_loop_with_fps(draw_set_screen);
	show_result("clear screen", fps);
	delay(5000);
	fps = picture_loop_with_fps(draw_char);
	show_result("draw @", fps);
	delay(5000);
	fps = picture_loop_with_fps(draw_pixel);
	show_result("draw pixel", fps);
	delay(5000);
}