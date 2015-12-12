#include <IHM/focusgroup.hpp>
#include <IHM/widget.hpp>
#include <algorithm>

FocusGroup* FocusGroup::mCurrentFocusGroup = nullptr;

void
FocusGroup::append (Widget& widget)
{
	mWidgets.push_back(&widget);
	if (mCurrent == nullptr)
		setFocus(widget);
}

void
FocusGroup::remove (Widget& widget)
{
	auto it = std::find(mWidgets.begin(), mWidgets.end(), &widget);
	if (it != mWidgets.end())
	{
		if (mWidgets.size() <= 1) {	
			mWidgets.clear();
			mCurrent = nullptr;
		}

		else if (&widget == mCurrent) {
			next();
			mWidgets.erase(it);
		}
	}
}

void
FocusGroup::setFocus (Widget& widget)
{
	if (mCurrent)
		mCurrent->disableFocus();
	mCurrent = &widget;

	if (mCurrentFocusGroup)
		mCurrentFocusGroup->unfocus();

	mCurrentFocusGroup = this;
	widget.enableFocus();
}


Widget*
FocusGroup::next()
{
	if(mWidgets.size() == 0)
		return nullptr;

	auto it = std::find(mWidgets.begin(), mWidgets.end(), mCurrent);
	++it;
	if (it == mWidgets.end())
	{
		setFocus(**mWidgets.begin());
		return mCurrent;
	}
	setFocus(**it);
	return mCurrent;
}

Widget*
FocusGroup::previous()
{
	if(mWidgets.size() == 0)
		return nullptr;

	auto it = std::find(mWidgets.rbegin(), mWidgets.rend(), mCurrent);
	++it;
	if (it == mWidgets.rend())
	{
		setFocus(**mWidgets.rbegin());
		return mCurrent;
	}
	setFocus(**it);
	return mCurrent;
}

Widget*
FocusGroup::current() 
{
	return mCurrent;
}

void
FocusGroup::unfocus()
{
	if (mCurrent)
		mCurrent->disableFocus();
	mCurrentFocusGroup = nullptr;
}

