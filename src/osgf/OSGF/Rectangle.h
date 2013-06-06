#pragma once
#include <windows.h>
namespace util
{
	class Rectangle
		:public RECT
	{
	public:
		Rectangle()
		{
			top = 0;
			left = 0;
			right = 0;
			bottom = 0;
		}
		Rectangle(LONG aLeft,LONG aTop,LONG aRight,LONG aBottom)
		{
			top = aTop;
			left = aLeft;
			right = aRight;
			bottom = aBottom;
		}
		Rectangle(const Rectangle& r)
		{
			Copy(r);
		}
		Rectangle(const RECT& r)
		{
			top = r.top;
			left = r.left;
			right = r.right;
			bottom = r.bottom;
		}
		Rectangle& operator=(const Rectangle& r)
		{
			if(this!=&r)
				Copy(r);
			return *this;
		}
		const RECT& ToRect()const
		{
			return dynamic_cast<const RECT&>(*this);
		}
		bool IsPointInside(LONG x,LONG y)
		{
			return x>left&&x<right&&y>top&&y<bottom;		
		}
	private:
		void Copy(const Rectangle&r)
		{
			top = r.top;
			left = r.left;
			right = r.right;
			bottom = r.bottom;
		}
	};
}