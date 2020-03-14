#pragma once

namespace app::Interpolation
{
	using EasingFunction = double(*)(double);

	// lerp(xp[i1], xp[i2], r) == x となる (r, i1, i2) を返す
	template <class X>
	static auto interp_x_(const Array<X>& xp, const X& x)
	{
		const auto l = std::upper_bound(xp.cbegin(), xp.cend(), x);
		const size_t i2 = l - xp.cbegin();

		if (i2 >= xp.size()) return std::make_tuple(0.0, i2 - 1, i2 - 1);
		if (i2 == 0) return std::make_tuple(0.0, i2, i2);

		const auto i1 = i2 - 1;
		const double r = (x - xp[i1]) * 1.0 / (xp[i2] - xp[i1]);
		return std::make_tuple(r, i1, i2);
	}

	// 配列xp, ypの組から、値xのときのyを線形補間で算出する
	template <class X, class Y>
	Y interp(const Array<X>& xp, const Array<Y>& yp, const X& x)
	{
		const auto [r, i1, i2] = interp_x_(xp, x);
		const auto y = yp[i1] + (yp[i2] - yp[i1]) * r;
		return y;
	}

	// 配列xp, ypの組から、値xのときのyを線形補間で算出したのち、イージング関数を適用する
	template <class X, class Y>
	Y interp(const Array<X>& xp, const Array<Y>& yp, const Array<EasingFunction>& easing, const X& x)
	{
		const auto [r, i1, i2] = interp_x_(xp, x);
		const auto y = yp[i1] + (yp[i2] - yp[i1]) * easing[i1](r);
		return y;
	}

	// 文字列に対応するイージング関数
	EasingFunction easingFunction(std::string_view name);

	// 配列の組xp,ypを保持し、値xに対応するyをInterpolation::interpで求めて返すクラス
	template <class X, class Y>
	class Interp
	{
	public:
		Interp() {}

		template <class ... Args>
		Interp(Args&& ...args)
		{
			set(std::forward<Args>(args)...);
		}

		// 引数：X1, Y1, X2, Y2, ... もしくは X1, Y1, E1, X2, Y2, E2, ...
		// Xn: n番目のX値
		// Yn: n番目のY値
		// En: イージング関数を表す文字列
		template <class ... Args>
		void set(Args&& ...args)
		{
			xp_.clear();
			yp_.clear();
			ef_.clear();
			set_(std::forward<Args>(args)...);
			//dump_();
		}

		// xに対応する線形補完された値yを得る
		Y get(const X& x) const
		{
			return interp(xp_, yp_, ef_, x);
		}

	private:
		void set_(const Array<X>& xp, const Array<Y>& yp)
		{
			xp_ = xp;
			yp_ = yp;
			ef_.resize(xp.size(), EaseInOutLinear);
		}

		void set_(const Array<X>& xp, const Array<Y>& yp, const Array<EasingFunction>& ef)
		{
			xp_ = xp;
			yp_ = yp;
			ef_ = ef;
		}

		template <class ... Args>
		void set_(const X& x, const Y& y, Args&& ...args)
		{
			setXYE_(x, y, EaseInOutLinear);
			set_(std::forward<Args>(args)...);
		}

		template <class Str, class ... Args>
		void set_(const X& x, const Y& y, const Str& easing, Args&& ...args)
		{
			setXYE_(x, y, easingFunction(easing));
			set_(std::forward<Args>(args)...);
		}

		void set_() {}

		void setXYE_(const X& x, const Y& y, EasingFunction f)
		{
			xp_.emplace_back(x);
			yp_.emplace_back(y);
			ef_.emplace_back(f);
		}

		void dump_()
		{
			for (auto i : step(xp_.size()))
			{
				Print << (U"{}, {}"_fmt(xp_[i], yp_[i]));
			}
		}

	private:
		Array<X> xp_;
		Array<Y> yp_;
		Array<EasingFunction> ef_;
	};
}
