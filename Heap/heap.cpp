#ifndef __HEAP_CPP
#define __HEAP_CPP
#include "heap.h"
#include <memory>

MinHeap::MinHeap(int cap)
{
	capacity = cap;
	heap_size = 0;
	shared_ptr<int> myArray(new int[capacity], default_delete<int[]>());
	harr = myArray;
	
}
 
int MinHeap::parent(int i)
{
	return (i-1)/2;
}
 
int MinHeap::left(int i)
{
	return 1 + 2*i ;
}
 
int MinHeap::right(int i)
{
	return 2 + 2*i;
}
 
int MinHeap::extractMin()
{
	if(!heap_size)
	{
		return 0;
	}
	int min = harr.get()[0];
	deleteKey(0);
	return min;
	
}
 
void MinHeap::decreaseKey(int i, int new_val)
{
	if(i>=heap_size)
	{
		return;
	}
	harr.get()[i] = new_val;
	while(1)
	{
		if(parent(i) >=0 && harr.get()[parent(i)] > harr.get()[i])
		{
			int temp = harr.get()[i];
			harr.get()[i] = harr.get()[parent(i)];
			harr.get()[parent(i)] = temp;
			i = parent(i);
		}
		else
		{
			break;
		}
	}

}
 
int MinHeap::getMin()
{
	return harr.get()[0];
}
 
void MinHeap::deleteKey(int i)
{
	if(i>= heap_size)
	{
		return;
	}
	if(!heap_size)
	{
		return ;
	}
	if(heap_size > 1)
	{
		harr.get()[i] = harr.get()[heap_size-1];
	}
	if(heap_size == 1)
	{
		heap_size--;
		return;
	}
	heap_size--;
	while(1)
	{
		//swapping if there are only two elements. will only have left child in this case
		if(heap_size == 2 && harr.get()[0]>harr.get()[1])
		{
			int temp = harr.get()[0];
			harr.get()[0] = harr.get()[1];
			harr.get()[1] = temp;
		}
		if(parent(i) >=0 && harr.get()[parent(i)] > harr.get()[i])
		{
			int temp = harr.get()[i];
			harr.get()[i] = harr.get()[parent(i)];
			harr.get()[parent(i)] = temp;
			i = parent(i);
		}
		else if(left(i) < heap_size && right(i) < heap_size && (harr.get()[i]>harr.get()[left(i)] || harr.get()[i]>harr.get()[right(i)]))
		{
			if(left(i) < heap_size && harr.get()[left(i)] < harr.get()[right(i)])
			{
				int temp = harr.get()[i];
				harr.get()[i] = harr.get()[left(i)];
				harr.get()[left(i)] = temp;
				i = left(i);
			}

			else if(right(i) < heap_size && harr.get()[right(i)] < harr.get()[left(i)])
			{
				int temp = harr.get()[i];
				harr.get()[i] = harr.get()[right(i)];
				harr.get()[right(i)] = temp;
				i = right(i);
			}
		}

		else
		{
			break;
		}
	}
}
 
void MinHeap::insertKey(int k)
{
	if(heap_size == capacity)
	{
		return;
	}

	harr.get()[heap_size] = k;
	heap_size++;

	int childIndex = heap_size - 1;
	int parentIndex = parent(childIndex);

	while(childIndex)
	{
		if(harr.get()[childIndex]<harr.get()[parentIndex])
		{
			int temp = harr.get()[childIndex];
			harr.get()[childIndex] = harr.get()[parentIndex];
			harr.get()[parentIndex] = temp;

			childIndex = parentIndex;
			parentIndex = parent(childIndex);
		}
		else
		{
			break;
		}
	}


}

shared_ptr<int> MinHeap::getHeap()
{
	return harr;
}

#endif
