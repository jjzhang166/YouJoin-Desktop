#ifndef LQUEUE_H
#define LQUEUE_H

#include "Link.h"
template<typename E>class LQueue{
private:
	Link<E>* front;
	Link<E>* rear;
	int size;
public:
	LQueue(){
		front = rear = new Link<E>(); 
		size = 0;
	}
	~LQueue(){
		clear();
		delete front;
	}
	void clear(){
		while (front->getNext() != NULL){
			rear = front;
			delete rear;
		}
		rear = front;
		size = 0;
	}
	void enqueue( E& it){						//出队
		rear->setNext(new Link<E>(it, NULL));
		rear = rear->getNext();
		size++;
	}
	E dequeue(){								//入队
		E it = front->getNext()->getElement();
		Link<E> *temp = front->getNext();
		front->setNext(temp->getNext());
		if (rear == temp) rear = front;
		delete temp;
		size--;
		return it;
	}
	int getSize(){					//获取队列容量
		return size;
	}
	bool isEmpty(){		//判断是否为空，如果空返回false；
		return size;
	}

};
#endif