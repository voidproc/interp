#include "Interpolation.h"

#define RETURN_EASING_FUNC(x) if(name==#x){return x;}

namespace interp
{
	EasingFunction easingFunction(std::string_view name)
	{
		RETURN_EASING_FUNC(EaseInOutBack);
		RETURN_EASING_FUNC(EaseInOutBounce);
		RETURN_EASING_FUNC(EaseInOutCirc);
		RETURN_EASING_FUNC(EaseInOutCubic);
		RETURN_EASING_FUNC(EaseInOutElastic);
		RETURN_EASING_FUNC(EaseInOutExpo);
		RETURN_EASING_FUNC(EaseInOutQuad);
		RETURN_EASING_FUNC(EaseInOutQuart);
		RETURN_EASING_FUNC(EaseInOutSine);

		RETURN_EASING_FUNC(EaseInBack);
		RETURN_EASING_FUNC(EaseInBounce);
		RETURN_EASING_FUNC(EaseInCirc);
		RETURN_EASING_FUNC(EaseInCubic);
		RETURN_EASING_FUNC(EaseInElastic);
		RETURN_EASING_FUNC(EaseInExpo);
		RETURN_EASING_FUNC(EaseInQuad);
		RETURN_EASING_FUNC(EaseInQuart);
		RETURN_EASING_FUNC(EaseInSine);

		RETURN_EASING_FUNC(EaseOutBack);
		RETURN_EASING_FUNC(EaseOutBounce);
		RETURN_EASING_FUNC(EaseOutCirc);
		RETURN_EASING_FUNC(EaseOutCubic);
		RETURN_EASING_FUNC(EaseOutElastic);
		RETURN_EASING_FUNC(EaseOutExpo);
		RETURN_EASING_FUNC(EaseOutQuad);
		RETURN_EASING_FUNC(EaseOutQuart);
		RETURN_EASING_FUNC(EaseOutSine);

		return EaseInOutLinear;
	}
}
