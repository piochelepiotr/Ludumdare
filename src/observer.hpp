#pragma once

#include <observable.hpp>

template <typename T>
class Observer
{
	protected:
		virtual void
		onUpdate(Observable<T>& source)=0;
		
		friend class Observable<T>;

};

