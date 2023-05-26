#include "Easing.h"

namespace Easing
{
	//イージング関数種類
	//https://easings.net/ja

	float EaseInSine(float x)
	{
		return 1 - cos(((x) * M_PI) / 2.0f);
	}

	float EaseOutSine(float x)
	{
		return  sin((x * M_PI) / 2);
	}

	float EaseInOutSine(float x)
	{
		return  -(cos(M_PI * x) - 1) / 2;
	}

	float EaseInQuad(float x)
	{
		return x * x;
	}

	float EaseOutQuad(float x)
	{
		return 1 - (1 - x) * (1 - x);
	}

	float EaseInOutQuad(float x)
	{
		return x < 0.5 ? 2 * x * x : 1 - pow(-2 * x + 2, 2) / 2;
	}

	float EaseInCubic(float x)
	{
		return x * x * x;
	}

	float EaseOutCubic(float x)
	{
		return 1 - pow(1 - x, 3);
	}

	float EaseInOutCubic(float x)
	{
		return x < 0.5 ? 4 * x * x * x : 1 - pow(-2 * x + 2, 3) / 2;
	}

	float EaseInQuart(float x)
	{
		return x * x * x * x;
	}

	float EaseOutQuart(float x)
	{
		return 1 - pow(1 - x, 4);
	}

	float EaseInOutQuart(float x)
	{
		return x < 0.5 ? 8 * x * x * x * x : 1 - pow(-2 * x + 2, 4) / 2;
	}

	float EaseInQuint(float x)
	{
		return x * x * x * x * x;
	}

	float EaseOutQuint(float x)
	{
		return 1 - pow(1 - x, 5);
	}

	float EaseInOutQuint(float x)
	{
		return x < 0.5 ? 16 * x * x * x * x * x : 1 - pow(-2 * x + 2, 5) / 2;
	}

	float EaseInExpo(float x)
	{
		return x == 0 ? 0 : pow(2, 10 * x - 10);
	}

	float EaseOutExpo(float x)
	{
		return x == 1 ? 1 : 1 - pow(2, -10 * x);
	}

	float EaseInOutExpo(float x)
	{
		return x == 0
			? 0
			: x == 1
			? 1
			: x < 0.5 ? pow(2, 20 * x - 10) / 2
			: (2 - pow(2, -20 * x + 10)) / 2;
	}

	float EaseInCirc(float x)
	{
		return 1 - sqrt(1 - pow(x, 2));
	}

	float EaseOutCirc(float x)
	{
		return sqrt(1 - pow(x - 1, 2));
	}

	float EaseInOutCirc(float x)
	{
		return x < 0.5
			? (1 - sqrt(1 - pow(2 * x, 2))) / 2
			: (sqrt(1 - pow(-2 * x + 2, 2)) + 1) / 2;
	}

	float EaseInBack(float x)
	{
		float c1 = 1.70158;
		float c3 = c1 + 1;

		return c3 * x * x * x - c1 * x * x;
	}

	float EaseOutBack(float x)
	{
		float c1 = 1.70158;
		float c3 = c1 + 1;

		return 1 + c3 * pow(x - 1, 3) + c1 * pow(x - 1, 2);
	}

	float EaseInOutBack(float x)
	{
		float c1 = 1.70158;
		float c2 = c1 * 1.525;

		return x < 0.5
			? (pow(2 * x, 2) * ((c2 + 1) * 2 * x - c2)) / 2
			: (pow(2 * x - 2, 2) * ((c2 + 1) * (x * 2 - 2) + c2) + 2) / 2;
	}

	float EaseInElastic(float x)
	{
		float c4 = (2 * M_PI) / 3;

		return x == 0
			? 0
			: x == 1
			? 1
			: -pow(2, 10 * x - 10) * sin((x * 10 - 10.75) * c4);
	}

	float EaseOutElastic(float x)
	{
		float c4 = (2 * M_PI) / 3;

		return x == 0
			? 0
			: x == 1
			? 1
			: pow(2, -10 * x) * sin((x * 10 - 0.75) * c4) + 1;
	}

	float EaseInOutElastic(float x)
	{
		float c5 = (2 * M_PI) / 4.5;

		return x == 0
			? 0
			: x == 1
			? 1
			: x < 0.5
			? -(pow(2, 20 * x - 10) * sin((20 * x - 11.125) * c5)) / 2
			: (pow(2, -20 * x + 10) * sin((20 * x - 11.125) * c5)) / 2 + 1;
	}

	float EaseInBounce(float x)
	{
		return 1 - EaseOutBounce(1 - x);
	}

	float EaseOutBounce(float x)
	{
		float n1 = 7.5625;
		float d1 = 2.75;

		if (x < 1 / d1) {
			return n1 * x * x;
		}
		else if (x < 2 / d1) {
			return n1 * (x -= 1.5 / d1) * x + 0.75;
		}
		else if (x < 2.5 / d1) {
			return n1 * (x -= 2.25 / d1) * x + 0.9375;
		}
		else {
			return n1 * (x -= 2.625 / d1) * x + 0.984375;
		}
	}

	float EaseInOutBounce(float x)
	{
		return x < 0.5
			? (1 - EaseOutBounce(1 - 2 * x)) / 2
			: (1 + EaseOutBounce(2 * x - 1)) / 2;
	}
};