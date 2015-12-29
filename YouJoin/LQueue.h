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
	void enqueue( E& it){						//����
		rear->setNext(new Link<E>(it, NULL));
		rear = rear->getNext();
		size++;
	}
	E dequeue(){								//���
		E it = front->getNext()->getElement();
		Link<E> *temp = front->getNext();
		front->setNext(temp->getNext());
		if (rear == temp) rear = front;
		delete temp;
		size--;
		return it;
	}
	int getSize(){					//��ȡ��������
		return size;
	}
	bool isEmpty(){		//�ж��Ƿ�Ϊ�գ�����շ���false��
		return size;
	}

};
#endif