#include <IHM/widget.hpp>
#include <IHM/focusgroup.hpp>

Widget::~Widget()
{
	if (mFocusGroup)
		mFocusGroup->remove(*this);
}

void
Widget::setPosition (const sf::Vector2f& position)
{
	mPosition = position;
}

const sf::Vector2f&
Widget::getPosition () const {
	return mPosition;
}

const sf::Vector2f&
Widget::getSize() const {
	return mSize;
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
	//FIXME? Completer
	if (mFocusGroup == group) return;
	
	if (mFocusGroup)
		mFocusGroup->remove(*this);
	
	mFocusGroup = group; 
	
	if (mFocusGroup)
		mFocusGroup->append(*this);
}

FocusGroup*
Widget::getFocusGroup ()
{
	return mFocusGroup;
}

void Widget::setSize ( const sf::Vector2f& size )
{
	mSize = size;
	notify();
}
