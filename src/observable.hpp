#pragma once

#include <algorithm>
#include <vector>

template <typename T>
class Observer;

template <typename T>
class Observable {
	public:
		void
		addListener(Observer<T>& observer);

		void
		removeListener(Observer<T>& observer);

	protected:
		void
		notify();

	private:
		std::vector<Observer<T>*> mObservers;
};

#include <observer.hpp>


template <typename T> void
Observable<T>::addListener(Observer<T>& observer)
{
	mObservers.push_back(&observer);
}

template <typename T> void
Observable<T>::removeListener(Observer<T>& observer)
{
	auto it = std::find(mObservers.begin(), mObservers.end(), &observer);
	if (it != mObservers.end()) {
		mObservers.erase(it);
	}
}

template <typename T> void
Observable<T>::notify () {
	for(auto observer : mObservers)
	{
		observer->onUpdate(*this);
	}	
}

struct Updatable {};
