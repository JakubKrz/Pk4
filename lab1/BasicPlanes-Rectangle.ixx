export module BasicPlanes:Rectangle;

import :Point;

export struct Rectangle
{
	Point upleft, lowright;
};

export float Height(const Rectangle& A)
{
	float h = A.upleft.y - A.lowright.y;
	if (h < 0)
	{
		return -h;
	}
	else return h;
}

export float Width(const Rectangle& A)
{
	float w = A.upleft.x - A.lowright.x;
	if (w < 0)
	{
		return -w;
	}
	else return w;
}

export float Area(const Rectangle& A)
{
	return Height(A) * Width(A);
}