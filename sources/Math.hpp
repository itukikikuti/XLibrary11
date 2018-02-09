class Float2 {
	PUBLIC float x;
	PUBLIC float y;

	PUBLIC Float2() : x(0.0f), y(0.0f) {
	}
	PUBLIC Float2(float x, float y) : x(x), y(y) {
	}
	PUBLIC operator DirectX::XMFLOAT2() const noexcept {
		return DirectX::XMFLOAT2(x, y);
	}
	PUBLIC Float2& operator=(const Float2& value) {
		x = value.x;
		y = value.y;
		return *this;
	}
	PUBLIC Float2& operator=(const float& value) {
		x = value;
		y = value;
		return *this;
	}
	PUBLIC Float2& operator+=(const Float2& value) {
		x += value.x;
		y += value.y;
		return *this;
	}
	PUBLIC Float2& operator+=(const float& value) {
		x += value;
		y += value;
		return *this;
	}
	PUBLIC Float2& operator-=(const Float2& value) {
		x -= value.x;
		y -= value.y;
		return *this;
	}
	PUBLIC Float2& operator-=(const float& value) {
		x -= value;
		y -= value;
		return *this;
	}
	PUBLIC Float2& operator*=(const Float2& value) {
		x *= value.x;
		y *= value.y;
		return *this;
	}
	PUBLIC Float2& operator*=(const float& value) {
		x *= value;
		y *= value;
		return *this;
	}
	PUBLIC Float2& operator/=(const Float2& value) {
		x /= value.x;
		y /= value.y;
		return *this;
	}
	PUBLIC Float2& operator/=(const float& value) {
		x /= value;
		y /= value;
		return *this;
	}
};

Float2 operator+(const Float2& t1, const Float2& t2) {
	return Float2(t1) += t2;
}
Float2 operator+(const Float2& t1, const float& t2) {
	return Float2(t1) += t2;
}
Float2 operator-(const Float2& t1, const Float2& t2) {
	return Float2(t1) -= t2;
}
Float2 operator-(const Float2& t1, const float& t2) {
	return Float2(t1) -= t2;
}
Float2 operator*(const Float2& t1, const Float2& t2) {
	return Float2(t1) *= t2;
}
Float2 operator*(const Float2& t1, const float& t2) {
	return Float2(t1) *= t2;
}
Float2 operator/(const Float2& t1, const Float2& t2) {
	return Float2(t1) /= t2;
}
Float2 operator/(const Float2& t1, const float& t2) {
	return Float2(t1) /= t2;
}

class Float3 {
	PUBLIC float x;
	PUBLIC float y;
	PUBLIC float z;

	PUBLIC Float3() : x(0.0f), y(0.0f), z(0.0f) {
	}
	PUBLIC Float3(float x, float y, float z) : x(x), y(y), z(z) {
	}
	PUBLIC operator DirectX::XMFLOAT3() const noexcept {
		return DirectX::XMFLOAT3(x, y, z);
	}
	PUBLIC Float3& operator=(const Float3& value) {
		x = value.x;
		y = value.y;
		z = value.z;
		return *this;
	}
	PUBLIC Float3& operator=(const float& value) {
		x = value;
		y = value;
		z = value;
		return *this;
	}
	PUBLIC Float3& operator+=(const Float3& value) {
		x += value.x;
		y += value.y;
		z += value.z;
		return *this;
	}
	PUBLIC Float3& operator+=(const float& value) {
		x += value;
		y += value;
		z += value;
		return *this;
	}
	PUBLIC Float3& operator-=(const Float3& value) {
		x -= value.x;
		y -= value.y;
		z -= value.z;
		return *this;
	}
	PUBLIC Float3& operator-=(const float& value) {
		x -= value;
		y -= value;
		z -= value;
		return *this;
	}
	PUBLIC Float3& operator*=(const Float3& value) {
		x *= value.x;
		y *= value.y;
		z *= value.z;
		return *this;
	}
	PUBLIC Float3& operator*=(const float& value) {
		x *= value;
		y *= value;
		z *= value;
		return *this;
	}
	PUBLIC Float3& operator/=(const Float3& value) {
		x /= value.x;
		y /= value.y;
		z /= value.z;
		return *this;
	}
	PUBLIC Float3& operator/=(const float& value) {
		x /= value;
		y /= value;
		z /= value;
		return *this;
	}
};

Float3 operator+(const Float3& t1, const Float3& t2) {
	return Float3(t1) += t2;
}
Float3 operator+(const Float3& t1, const float& t2) {
	return Float3(t1) += t2;
}
Float3 operator-(const Float3& t1, const Float3& t2) {
	return Float3(t1) -= t2;
}
Float3 operator-(const Float3& t1, const float& t2) {
	return Float3(t1) -= t2;
}
Float3 operator*(const Float3& t1, const Float3& t2) {
	return Float3(t1) *= t2;
}
Float3 operator*(const Float3& t1, const float& t2) {
	return Float3(t1) *= t2;
}
Float3 operator/(const Float3& t1, const Float3& t2) {
	return Float3(t1) /= t2;
}
Float3 operator/(const Float3& t1, const float& t2) {
	return Float3(t1) /= t2;
}

class Float4 {
	PUBLIC float x;
	PUBLIC float y;
	PUBLIC float z;
	PUBLIC float w;

	PUBLIC Float4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {
	}
	PUBLIC Float4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {
	}
	PUBLIC operator DirectX::XMFLOAT4() const noexcept {
		return DirectX::XMFLOAT4(x, y, z, w);
	}
	PUBLIC Float4& operator=(const Float4& value) {
		x = value.x;
		y = value.y;
		z = value.z;
		w = value.w;
		return *this;
	}
	PUBLIC Float4& operator=(const float& value) {
		x = value;
		y = value;
		z = value;
		w = value;
		return *this;
	}
	PUBLIC Float4& operator+=(const Float4& value) {
		x += value.x;
		y += value.y;
		z += value.z;
		w += value.w;
		return *this;
	}
	PUBLIC Float4& operator+=(const float& value) {
		x += value;
		y += value;
		z += value;
		w += value;
		return *this;
	}
	PUBLIC Float4& operator-=(const Float4& value) {
		x -= value.x;
		y -= value.y;
		z -= value.z;
		w -= value.w;
		return *this;
	}
	PUBLIC Float4& operator-=(const float& value) {
		x -= value;
		y -= value;
		z -= value;
		w -= value;
		return *this;
	}
	PUBLIC Float4& operator*=(const Float4& value) {
		x *= value.x;
		y *= value.y;
		z *= value.z;
		w *= value.w;
		return *this;
	}
	PUBLIC Float4& operator*=(const float& value) {
		x *= value;
		y *= value;
		z *= value;
		w *= value;
		return *this;
	}
	PUBLIC Float4& operator/=(const Float4& value) {
		x /= value.x;
		y /= value.y;
		z /= value.z;
		w /= value.w;
		return *this;
	}
	PUBLIC Float4& operator/=(const float& value) {
		x /= value;
		y /= value;
		z /= value;
		w /= value;
		return *this;
	}
};

Float4 operator+(const Float4& t1, const Float4& t2) {
	return Float4(t1) += t2;
}
Float4 operator+(const Float4& t1, const float& t2) {
	return Float4(t1) += t2;
}
Float4 operator-(const Float4& t1, const Float4& t2) {
	return Float4(t1) -= t2;
}
Float4 operator-(const Float4& t1, const float& t2) {
	return Float4(t1) -= t2;
}
Float4 operator*(const Float4& t1, const Float4& t2) {
	return Float4(t1) *= t2;
}
Float4 operator*(const Float4& t1, const float& t2) {
	return Float4(t1) *= t2;
}
Float4 operator/(const Float4& t1, const Float4& t2) {
	return Float4(t1) /= t2;
}
Float4 operator/(const Float4& t1, const float& t2) {
	return Float4(t1) /= t2;
}

struct Vertex {
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 normal;
	DirectX::XMFLOAT2 texcoord;

	//Vertex(DirectX::XMFLOAT3 position, DirectX::XMFLOAT2 texcoord, DirectX::XMFLOAT3 normal) {
	//	this->position = position;
	//	this->texcoord = texcoord;
	//	this->normal = normal;
	//}
};
