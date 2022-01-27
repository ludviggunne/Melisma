#pragma once

namespace melisma {

	struct Viewport {
		Viewport() : X(0), Y(0), Width(800), Height(600) {}
		Viewport(int x, int y, int width, int height)
			: X(x), Y(y), Width(width), Height(height) {}

		int X;
		int Y;
		int Width;
		int Height;
	};

}