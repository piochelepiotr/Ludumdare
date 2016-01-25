#include <IHM/selectorwidget.hpp>
//#include <algorithm>
//#include <iostream>

SelectorWidget::SelectorWidget(sf::Font& font, TriggerFun callback) :
	mCallback()
{
	mText.setFont(font);
}


void SelectorWidget::addEntry ( int id, const sf::String& name )
{
	mEntries.push_back(std::pair<int, sf::String>(id,name));
	recompute();
}

bool SelectorWidget::event ( sf::Event e )
{
	if (e.type == sf::Event::KeyPressed)
	{
		switch (e.key.code)
		{
			case sf::Keyboard::Left:
				previous();
				return true;
			
			case sf::Keyboard::Right:
				next();
				return true;
			
			default:
				break;
		}
	}
	return false;
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
	auto area = getArea();
	area.left += getPosition().x;
	area.top  += getPosition().y;
	
	if (e.type == sf::Event::MouseMoved) {
		if (area.contains(local)) {
			focus();
			return true;
		}
	}
		else if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
			if (area.contains(local)) {
				return true;
			}
		}
			return false;
	return false;
}

void SelectorWidget::next()
{
	++mCursor;
	if (mCursor >= mEntries.size())
		mCursor %= mEntries.size();
	recompute();
	//mCallback(mEntries[mCursor].first);
}

void SelectorWidget::previous()
{
	if (mCursor == 0 && !mEntries.empty()) {
		mCursor = mEntries.size()-1; return;
	}
	--mCursor;
	recompute();
	//mCallback(mEntries[mCursor].first);
}

void SelectorWidget::removeEntry ( const sf::String& name )
{
	std::remove_if(mEntries.begin(), mEntries.end(), [&name](std::pair<int,sf::String>& e) {return e.second == name;});
	recompute();
}

void SelectorWidget::removeEntry ( int id )
{
	std::remove_if(mEntries.begin(), mEntries.end(), [&id](std::pair<int,sf::String> e) {return e.first == id; });
	recompute();
}

void SelectorWidget::render ( sf::RenderTarget& target, sf::RenderStates states ) const
{
	//TODO dessin de l'entry [mCursor]
	//states.transform.translate(getPosition());
	target.draw(mText, states);
}

void SelectorWidget::update ( sf::Time t )
{
	
}

void SelectorWidget::disableFocus()
{
    mText.setColor(sf::Color::White);
}

void SelectorWidget::enableFocus()
{
    mText.setColor(sf::Color::Red);
}

void SelectorWidget::recompute()
{
	if (mEntries.empty()) return;
	
	mText.setCharacterSize(120);
	mText.setString(mEntries[mCursor].second);
	mText.getLocalBounds().width;
	//auto w = mText.getLocalBounds().width;
	//mText.setPosition({-w/2.f,0.f});
	
	notify();
}
