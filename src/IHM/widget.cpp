#include <IHM/widget.hpp>
#include <IHM/focusgroup.hpp>

void
Widget::setPosition (const sf::Vector2f& position)
{
	mPosition = position;
}

const sf::Vector2f&
Widget::getPosition () const {
	return mPosition;
}

void
Widget::draw (sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform.translate(mPosition);
	render(target, states);
}

void
Widget::focus () 
{
	if (mFocusGroup)
		mFocusGroup->setFocus(*this);
}

void
Widget::setFocusGroup (FocusGroup* group)
{
	//FIXME Completer
	if (mFocusGroup == group) return;
	
	if (mFocusGroup)
		mFocusGroup->remove(*this);
	mFocusGroup = group; 
	group->append(*this);
}

FocusGroup*
Widget::getFocusGroup ()
{
	return mFocusGroup;
}
