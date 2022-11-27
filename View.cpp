#include "View.h"

sf::View view;
sf::View getPlayerCoordForView(float x, float y) {
	view.setCenter(x, y);
	return view;
}
