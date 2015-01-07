// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "arduino.h"
#include "..\..\M2tklib\M2tk.h"
#include "..\..\M2tklib\utility\m2ghu8g.h"
#include "spi.h"
#include "..\..\U8glib\U8glib.h"

// Temp function defs
extern "C" uint8_t m2_es_i2c(m2_p ep, uint8_t msg);

uint32_t number = 1234;
char	*str;
U8GLIB_LM6059 u8g(8, 10, 9);

int _tmain(int argc, _TCHAR* argv[])
{
	str = (char *)malloc(512);
	memset(str, 0, 512);
    return RunArduinoSketch();
}

void fn_ok(m2_el_fnarg_p fnarg) {
	/* do something with the number */
	sprintf(str, "Selected %d", number);
}

M2_LABELPTR(el_selected, NULL, (const char**)(&str));
M2_LABEL(el_label, NULL, "Num: ");
M2_U32NUM(el_num, "a1c4", &number);
M2_BUTTON(el_ok, "", " ok ", fn_ok);
M2_LIST(list) = { &el_label, &el_num, &el_ok };
M2_HLIST(el_hlist, NULL, list);
M2_LIST(toplist) = { &el_selected, &el_hlist};
M2_VLIST(top_el_vlist, NULL, toplist);

M2tk m2(&top_el_vlist, m2_es_i2c, m2_eh_4bs, m2_gh_u8g_bfs);

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
	m2.checkKey();
	if (m2.handleKey() != 0)
	{
		u8g.firstPage();
		do {
			m2.checkKey();
			draw();
		} while (u8g.nextPage());
	}
}