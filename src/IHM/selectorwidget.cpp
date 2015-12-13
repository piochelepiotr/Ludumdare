#include <IHM/selectorwidget.hpp>


void SelectorWidget::addEntry ( int id, const sf::String& name )
{
	mEntries.push_back(std::pair<int, sf::String>(id,name));
}

void SelectorWidget::event ( sf::Event e )
{
	if (e.type == sf::Event::KeyPressed)
	{
		switch (e.key.code)
		{
			case sf::Keyboard::Left:{
				previous();
				break;
			}
			
			case sf::Keyboard::Right:{
				next();
				break;
			}
			
			default:
				break;
		}
		
	}
}

sf::FloatRect SelectorWidget::getArea() const
{
	auto r = mText.getLocalBounds();
	r.left += getPosition().x;
	r.top  += getPosition().y;
	return r;
}

bool SelectorWidget::mouseEvent ( sf::Event e, sf::Vector2f local )
{

	return false;
}

void SelectorWidget::next()
{
	++mCursor;
	if (mCursor >= mEntries.size())
		mCursor %= mEntries.size();
}

void SelectorWidget::previous()
{
	if (mCursor == 0 && !mEntries.empty()) {
		mCursor = mEntries.size()-1; return;
	}
	--mCursor;
}

void SelectorWidget::removeEntry ( const sf::String& name )
{
	
}

void SelectorWidget::removeEntry ( int id )
{

}

void SelectorWidget::render ( sf::RenderTarget& target, sf::RenderStates states ) const
{
	//FIXME dessin de l'entry [mCursor]
	states.transform.translate(getPosition());
	target.draw(mText, states);
}

void SelectorWidget::update ( sf::Time t )
{
	
}
