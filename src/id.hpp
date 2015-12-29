#pragma once
#include <cstddef>
#include <map>


// Gestion des IDs

// ID pour un type quelconque
template <typename T>
class ID
{
	public:
	explicit inline ID(std::size_t const& n) : id(n) {}
	inline bool operator == (ID const& other) const { return id == other.id; }
	inline bool operator != (ID const& other) const { return id != other.id; }
	inline bool operator < (ID const& other) const { return id < other.id; }
	inline ID& operator ++ () { ++id; return *this; }

	std::size_t id;
};


// noID, valeur des ID particulière
constexpr class noID_t
{
	public:
	template <typename T>
	inline operator ID<T>() const { return ID<T>(0); }
} noID;


// Génère des ID uniques pour des types quelconques.
// Utiliser next() pour obtenir le prochain id.
// NoID est la seule valeur qui n’est jamais donnée,
// et est utilisée pour les cas particuliers.
template <typename T>
class IDgenerator
{
	public:
	inline IDgenerator() : id(0) {};
	inline ID<T> next() { return ++id; }
	inline void reset() { id = ID<T>(0); }
	private:
	ID<T> id;
};


// Table associative ID -> Obj
// addObj(…) pour ajouter un objet
// remove(id) pour supprimer un objet
template <typename T>
class IDstaticmap
{
	public:
	template <typename... Args>
	typename std::map<ID<T>, T>::iterator addObj(Args&... args)
	{
		return map.emplace_hint(map.end(), std::piecewise_construct,
				std::forward_as_tuple(idgen.next()),
				std::forward_as_tuple(args...));
	}
	void removeObj(ID<T> id) { map.erase(id); }
	void clear() { idgen.reset(); map.clear(); }
	T const& operator [] (ID<T> id) const { return map.find(id)->second; }
	T& operator [] (ID<T> id) { return map.find(id)->second; }
	typename std::map<ID<T>, T>::iterator begin() { return map.begin(); }
	typename std::map<ID<T>, T>::const_iterator begin() const { return map.begin(); }
	typename std::map<ID<T>, T>::iterator end() { return map.end(); }
	typename std::map<ID<T>, T>::const_iterator end() const { return map.end(); }
	private:
	IDgenerator<T> idgen;
	std::map<ID<T>, T> map;
};
