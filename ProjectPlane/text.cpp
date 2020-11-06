#include "Text.h"

vector<Text> Text::textlist;
vector<Text>::iterator Text::iter;
enum Text::TEXTS;

Text::Text(TEXTS t) {
	type = t;
	x = 100;
	y = 20;
}

void Text::ReloadText() {
	for (iter = textlist.begin(); iter != textlist.end();) {

	}
}
