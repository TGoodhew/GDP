// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "arduino.h"
#include "..\..\M2tklib\M2tk.h"
#include "..\..\M2tklib\utility\m2ghu8g.h"
#include "spi.h"
#include "..\..\U8glib\U8glib.h"

U8GLIB_LM6059 u8g(8, 10, 9);

int _tmain(int argc, _TCHAR* argv[])
{
    return RunArduinoSketch();
}

M2_LABEL(hello_world_label, NULL, "Hello World");
M2tk m2(&hello_world_label, NULL, NULL, m2_gh_u8g_bfs);

void draw(void) {
	m2.draw();
}

void setup() {
	/* connect u8glib with m2tklib */
	m2_SetU8g(u8g.getU8g(), m2_u8g_box_icon);

	/* assign u8g font to index 0 */
	m2.setFont(0, u8g_font_7x13);
}

void loop() {
	u8g.firstPage();
	do {
		draw();
	} while (u8g.nextPage());
}