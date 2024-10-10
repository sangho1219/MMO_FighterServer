#pragma once
#include <memory>
class RingQueue
{
private:
	int _front, _rear;
	int _size;
	int _resizeCount = 1;
	char* _circular;

public:
	RingQueue(int size_arg);
	RingQueue();
	~RingQueue();
	RingQueue(const RingQueue& src);
	RingQueue& operator=(const RingQueue& src);
	void INIT(int size_arg);
	int GetBufferSize();
	char* GetCircularPtr()
	{
		return _circular;
	}
	int GetUseSize();
	int GetFreeSize();
	int DirectEnqueueSize();
	int DirectDequeueSize();
	bool isEmpty();
	bool isFull();
	int Enqueue(char* chpData, int iSize);
	int Dequeue(char* chpDest, int iSize);
	int Peek(char* chpDest, int iSize);
	int MoveRear(int iSize);
	int MoveFront(int iSize);
	void ClearBuffer();
	char* GetFrontBufferPtr();
	char* GetRearBufferPtr();
	void resize();
	int getResizeCount();
};


RingQueue::RingQueue(int size_arg)
{
	_size = size_arg;
	_circular = new char[_size];
	_front = 0;
	_rear = 0;
}
RingQueue::RingQueue()
{
	_front = 0;
	_rear = 0;
	_size = 0;
	_resizeCount = 1;
	_circular = 0;
}
RingQueue::~RingQueue()
{
	if (_circular != 0)
	{
		delete[] _circular;
	}
}
RingQueue::RingQueue(const RingQueue& src)
{
	this->_front = src._front;
	this->_rear = src._rear;
	this->_size = src._size;
	this->_resizeCount = src._resizeCount;
	this->_circular = new char[_size];
	if (src._circular)
	{
		for (int i = 0; i < _size; i++)
		{
			this->_circular[i] = src._circular[i];
		}
	}
}
RingQueue& RingQueue::operator=(const RingQueue& src)
{
	if (this == &src) {
		return *this;
	}

	if (this->_circular)
	{
		delete[] _circular;
	}

	this->_front = src._front;
	this->_rear = src._rear;
	this->_size = src._size;
	this->_resizeCount = src._resizeCount;
	this->_circular = new char[_size];
	if (src._circular)
	{
		for (int i = 0; i < _size; i++)
		{
			this->_circular[i] = src._circular[i];
		}
	}

}

void	RingQueue::INIT(int size_arg)
{
	_size = size_arg;
	_circular = new char[_size];
	_front = 0;
	_rear = 0;
}
int		RingQueue::GetBufferSize()
{
	return _size;
}
int		RingQueue::GetUseSize()
{
	if (_size == 0)
		return 0;

	return ((_rear - _front) + _size) % _size;
}
int		RingQueue::GetFreeSize()
{
	return _size - GetUseSize() - 1;
}
int		RingQueue::DirectEnqueueSize()
{
	if (_rear >= _front)
	{
		if (_front == 0)
			return _size - _rear - 1;
		return _size - _rear;
	}
	if(_front > _rear)
		return _front - _rear - 1;

}
int		RingQueue::DirectDequeueSize()
{
	if (_front > _rear)
		return _size - _front;
	else
		return _rear - _front;
}
bool	RingQueue::isEmpty()
{
	if (_size == 0)
	{
		return true;
	}

	if (_front == _rear)
	{
		return true;
	}
	return false;
}
bool	RingQueue::isFull()
{
	if (_size == 0)
	{
		return 0;
	}
	if ((_rear + 1) % _size == _front)
	{
		return true;
	}
	return false;
}
int		RingQueue::Enqueue(char* chpData, int iSize)
{
	if (iSize > GetFreeSize())
		iSize = GetFreeSize();


	if (iSize > DirectEnqueueSize())
	{
		int iLeftoverSize = iSize - DirectEnqueueSize();
		char* chpLeftoverData = chpData + DirectEnqueueSize();

		memcpy(GetRearBufferPtr(), chpData, DirectEnqueueSize());
		MoveRear(DirectEnqueueSize());

		memcpy(GetRearBufferPtr(), chpLeftoverData, iLeftoverSize);
		MoveRear(iLeftoverSize);
	}
	else
	{
		memcpy(GetRearBufferPtr(), chpData, iSize);
		MoveRear(iSize);
	}

	return iSize;
}
int		RingQueue::Dequeue(char* chpDest, int iSize)
{
	if (iSize > GetUseSize())
		iSize = GetUseSize();

	int DDS = DirectDequeueSize();

	if (iSize > DDS)
	{
		int iLeftoverSize = iSize - DDS;
		char* chpLeftoverDest = chpDest + DDS;

		memcpy(chpDest, GetFrontBufferPtr(), DDS);
		memcpy(chpLeftoverDest, GetCircularPtr(), iLeftoverSize);
		MoveFront(iSize);
	}
	else
	{
		memcpy(chpDest, GetFrontBufferPtr(), iSize);
		MoveFront(iSize);
	}
	return iSize;
}
int		RingQueue::Peek(char* chpDest, int iSize)
{
	if (iSize > GetUseSize())
		iSize = GetUseSize();

	int DDS = DirectDequeueSize();

	if (iSize > DDS)
	{
		int iLeftoverSize = iSize - DDS;
		char* chpLeftoverDest = chpDest + DDS;

		memcpy(chpDest, GetFrontBufferPtr(), DDS);
		memcpy(chpLeftoverDest, GetCircularPtr(), iLeftoverSize);
	}
	else
	{
		memcpy(chpDest, GetFrontBufferPtr(), iSize);
	}

	return iSize;
}
int		RingQueue::MoveRear(int iSize)
{
	if (iSize > GetFreeSize())
		iSize = GetFreeSize();

	_rear = (_rear + iSize) % _size;

	return iSize;
}
int		RingQueue::MoveFront(int iSize)
{
	if (iSize > GetUseSize())
		iSize = GetUseSize();

	_front = (_front + iSize) % _size;

	return iSize;
}
void	RingQueue::ClearBuffer()
{
	_front = _rear;
}
char*	RingQueue::GetFrontBufferPtr()
{
	return &(_circular[_front]);
}
char*	RingQueue::GetRearBufferPtr()
{
	return &(_circular[_rear]);
}
void	RingQueue::resize()
{
	int prevSize = GetUseSize();
	char* cpy = new char[prevSize];
	Dequeue(cpy, prevSize);
	delete[] _circular;

	_size = _size + 500;
	_circular = new char[_size];
	_rear = 0; _front = 0;


	Enqueue(cpy, prevSize);
	delete[] cpy;
	_resizeCount--;

}
int		RingQueue::getResizeCount()
{
	return _resizeCount;
}