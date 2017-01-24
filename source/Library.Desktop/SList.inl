#pragma once
#include <exception>

template <class T>
SList<T>::SList() : 
mSize(0), mFront(nullptr), mBack(nullptr), mBegin(this, mFront), mEnd(this, nullptr) {}

template <class T>
SList<T>::SList(const SList<T>& obj) :
	SList()
{
	auto current = obj.mFront;
	if (current != nullptr)
	{
		while (current != nullptr)
		{
			pushBack(current->mData);
			current = current->next;
		}
	}
}

template <class T>
SList<T>& SList<T>::operator=(const SList<T>& rhs)
{
	if (this != &rhs)
	{
		clear();
		auto current = rhs.mFront;
		while (current != nullptr)
		{
			pushBack(current->mData);
			current = current->next;
		}
	}
	return *this;
}

template <class T>
SList<T>::~SList()
{
	Node* current = mFront;
	while (current != nullptr)
	{
		Node* newCurrent = current->next;
		delete(current);
		current = newCurrent;
	}
}

template <class T>
typename SList<T>::Iterator SList<T>::pushFront(T data)
{
	auto temp = mFront;
	mFront = new Node(data);
	mFront->next = temp;
	mBegin.mNode = mFront;
	mSize++;
	if (mBack == nullptr)
	{
		mBack = mFront;
		mBack->next = nullptr;
		mEnd.mNode = mBack->next;
	}

	return Iterator(this, mFront);
}

template <class T>
typename SList<T>::Iterator SList<T>::pushBack(T data)
{
	if (mFront == nullptr)
	{
		mFront = new Node(data);
		mBack = mFront;
		mBack->next = nullptr;
		mEnd.mNode = mBack->next;
	}
	else
	{
		auto current = mFront;
		while (current->next != nullptr)
		{
			current = current->next;
		}
		current->next = new Node(data);
		mBack = current->next;
		mBack->next = nullptr;
		mEnd.mNode = mBack->next;
	}

	mSize++;
	mBegin.mNode = mFront;
	mEnd.mNode = mBack;

	return Iterator(this, mBack);
}

template <class T>
void SList<T>::clear()
{
	auto current = mFront;
	if (current != nullptr)
	{
		while (current->next != nullptr)
		{
			auto temp = current;
			current = current->next;
			delete(temp);
		}
	}
	mSize = 0;
}

template <class T>
T SList<T>::popFront()
{
	auto oldFront = mFront;
	auto result = mFront->mData;
	mFront = mFront->next;
	mBegin.mNode = mFront;
	delete(oldFront);
	mSize--;
	return result;
}

template <class T>
T& SList<T>::front()
{
	if (mFront == nullptr)
	{
		throw std::exception("List is null");
	}
	return mFront->mData;
}

template <class T>
const T& SList<T>::front() const
{
	if (mFront == nullptr)
	{
		throw std::exception("List is null");
	}
	return mFront->mData;
}

template <class T>
T& SList<T>::back()
{
	if (mFront == nullptr)
	{
		throw std::exception("List is null");
	}
	return mBack->mData;
}

template <class T>
const T& SList<T>::back() const
{
	if (mFront == nullptr)
	{
		throw std::exception("List is null");
	}
	return mBack->mData;
}

template <class T>
bool SList<T>::isEmpty() const
{
	return mSize == 0;
}

template <class T>
int SList<T>::size() const
{
	return mSize;
}

template <class T>
typename SList<T>::Iterator& SList<T>::begin()
{
	return mBegin;
}

template <class T>
typename SList<T>::Iterator& SList<T>::end()
{
	return mEnd;
}

template <class T>
typename SList<T>::Iterator SList<T>::insertAfter(T value, Iterator& location)
{
	if (location == end() || location.mNode == mBack)
	{
		pushBack(value);
		
		return Iterator(this, mBack);
	}

	for (Iterator iter = begin(); iter != end(); ++iter)
	{
		if (location == iter)
		{
			Node* temp = new Node(value);
			temp->next = location.mNode->next;
			location.mNode->next = temp;
			return Iterator(this, temp);
		}
	}

	return end();
}
