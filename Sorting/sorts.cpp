#ifndef __SORTS_CPP
#define __SORTS_CPP
#include "sorts.h"
#include "LinkedList.cpp"

//===========================Helper Function Definition================================
void split(shared_ptr<LinkedList<long>>& myList, LinkedList<long>& l1, LinkedList<long>& l2);
LinkedList<long> merge(LinkedList<long>& list1, LinkedList<long>& list2);
LinkedList<long> merge_helper(LinkedList<long>& myList);

//=====================================================================================
vector<long> InsertionSort(vector<long> nums)
{
    long arr[nums.size()];
    int size = nums.size();
    for(int i=0; i<size; i++)
    {
        arr[i] = nums.back();
        nums.pop_back();
    }   
    long temp;
    int j;
    int i=1;
    while(i<size)
    {
        j=i++;
        
        while(j && arr[j] < arr[j-1])
        {
            temp = arr[j];
            arr[j] = arr[j-1];
            arr[--j] = temp;
            
        }
        
    }

    for(int i=0; i<size; i++)
    {
        nums.push_back(arr[i]) ;
    } 

    return nums;

    
}

//=====================================================================================
vector<long> MergeSort(vector<long> nums)
{

    LinkedList<long> list;
    int size = nums.size();
    for (int i = 0; i<size; i++)
    {
        list.insertAtHead(nums.back());
        nums.pop_back();
    }
    LinkedList<long> result = merge_helper(list);
	//cout << result.length();
	for (int i = 0; i < size; i++)
	{
	 	nums.push_back(result.getHead()->value);
        result.deleteHead();
	}



	return nums;
}

//=====================================================================================


//==============================Helper Functions=======================================
LinkedList<long> merge(LinkedList<long>& list1, LinkedList<long>& list2)
{
	LinkedList<long> result;
	shared_ptr<ListItem<long>> l1 = list1.getTail();
	shared_ptr<ListItem<long>> l2 = list2.getTail();
	while(true)
	{
		if(!l1 && !l2)
		{
			break;
		}
		if ( l1 && !l2 )
		{
			result.insertAtHead(l1->value);
			l1 = l1->prev;
		}
		else if (!l1 && l2 )
		{
			result.insertAtHead(l2->value);
			l2 = l2->prev;
		}
		else if(l1->value <= l2->value )
		{
			result.insertAtHead(l2->value);
			l2 = l2->prev;
		}	
		else
		{
			result.insertAtHead(l1->value);
			l1 = l1->prev;
		}
		
	}
	return result;
}

void split(LinkedList<long>& myList, LinkedList<long>& l1, LinkedList<long>& l2)
{
	int size = myList.length();
	if (!size)
	{
		return;
	}
	if (size == 1 )
	{
		l1.insertAtHead(myList.getHead()->value);
	}
	else
	{
		int mid = size/2;
		shared_ptr<ListItem<long>> temp = myList.getTail();
		for (int i = 0; i < size; i++)
		{
			if(i<mid)
			{
				l2.insertAtHead(temp->value);
				temp = temp->prev;
			}

			else
			{
				l1.insertAtHead(temp->value);
				temp = temp->prev;
			}
			
		}
	}
}

LinkedList<long> merge_helper(LinkedList<long>& myList)
{
	int size = myList.length();
	if (size == 0 || size == 1)
	{
		
		return myList;
	}
	LinkedList<long> first;
	LinkedList<long> second;
	
	split(myList, first, second);

	
	LinkedList<long> l1 = merge_helper(first);
	LinkedList<long> l2 = merge_helper(second);
	
	LinkedList<long> result = merge(l1, l2);
	
	
	return result;
}


#endif
