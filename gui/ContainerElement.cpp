#include "ContainerElement.hpp"
#include "Visualizer.hpp"
#include "Notificator.hpp"

BEGIN_INANITY_GUI

ContainerElement::ContainerElement(ptr<Visualizer> visualizer)
: Element(visualizer) {}

void ContainerElement::SetNotificator(ptr<Notificator> notificator)
{
	this->notificator = notificator;
}

void ContainerElement::QueryFocus(ptr<Element> element)
{
	//если сам контейнер находится в фокусе
	if(IsFocused())
	{
		//если есть прежний элемент, находящийся в фокусе
		if(focusedElement)
			//сообщить ему, что он теряет фокус
			focusedElement->EventLostFocus();
		//указать новому элементу, что он получает фокус
		focusedElement = element;
		focusedElement->EventSetFocus();
	}
	//иначе сам контейнер не находится в фокусе
	else
	{
		//тогда никакому прежнему элементу ничего не надо сообщать
		//укажем новый элемент
		focusedElement = element;
		//установим себе фокус
		//остальное сделает обработчик EventSetFocus
		SetFocus();
	}
}

void ContainerElement::Notify(ptr<Element> element, int code)
{
	if(notificator)
		notificator->Notify(element, code);
	else if(parent)
		parent->Notify(element, code);
}

void ContainerElement::EventMouseMove(Position position)
{
	ptr<Element> newMousedElement = TryGetElementByPosition(position);
	if(newMousedElement != mousedElement)
	{
		if(mousedElement)
			mousedElement->EventMouseLeave();
		mousedElement = newMousedElement;
		if(mousedElement)
			mousedElement->EventMouseEnter();
	}
	if(mousedElement)
		mousedElement->EventMouseMove(position - mousedElement->GetPosition());
}

void ContainerElement::EventMouseDown(Position position, MouseEvent::Button button)
{
	ptr<Element> element = TryGetElementByPosition(position);
	if(element)
		element->EventMouseDown(position - element->GetPosition(), button);
}

void ContainerElement::EventMouseUp(Position position, MouseEvent::Button button)
{
	ptr<Element> element = TryGetElementByPosition(position);
	if(element)
		element->EventMouseUp(position - element->GetPosition(), button);
}

void ContainerElement::EventMouseLeave()
{
	if(mousedElement)
	{
		mousedElement->EventMouseLeave();
		mousedElement = nullptr;
	}
}

void ContainerElement::EventSetFocus()
{
	Element::EventSetFocus();
	if(focusedElement)
		focusedElement->EventSetFocus();
}

void ContainerElement::EventLostFocus()
{
	Element::EventLostFocus();
	if(focusedElement)
		focusedElement->EventLostFocus();
}

void ContainerElement::EventKeyDown(Key key)
{
	Element::EventKeyDown(key);
	if(focusedElement)
		focusedElement->EventKeyDown(key);
}

void ContainerElement::EventKeyUp(Key key)
{
	Element::EventKeyUp(key);
	if(focusedElement)
		focusedElement->EventKeyUp(key);
}

void ContainerElement::EventKeyPress(wchar_t key)
{
	Element::EventKeyPress(key);
	if(focusedElement)
		focusedElement->EventKeyPress(key);
}

END_INANITY_GUI
