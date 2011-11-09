#pragma once

namespace CGTutorial {
	typedef struct CAMERA{
		float xpos, ypos, zpos,
			xlook, ylook, zlook,
			xup, yup, zup;
		CAMERA():xpos(0), ypos(0), zpos(0),
				xlook(0), ylook(0), zlook(0),
				xup(0), yup(0), zup(0)
		{
		}
	};
}
