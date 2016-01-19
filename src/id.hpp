#pragma once

// Définition des IDs

// ID pour un type quelconque
template <typename T>
class ID
{
	public:
	explicit inline ID(unsigned int const n) : id(n) {}
	inline bool operator == (ID const& other) const { return id == other.id; }
	inline bool operator != (ID const& other) const { return id != other.id; }
	inline bool operator < (ID const& other) const { return id < other.id; }
	inline ID& operator ++ () { ++id; return *this; }

	unsigned int id;
};


// noID, valeur des IDs particulière
constexpr class noID_t
{
	public:
	template <typename T>
	inline operator ID<T>() const { return ID<T>(0); }
} noID;
