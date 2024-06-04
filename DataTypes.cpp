#include "DataTypes.h"

Vec3 operator- (const Vec3& first, const Vec3& second) {
	Vec3 temp;
	temp.X = first.X - second.X;
	temp.Y = first.Y - second.Y;
	temp.Z = first.Z - second.Z;
	return temp;
};