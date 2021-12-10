#ifndef __TRIE_CPP
#define __TRIE_CPP

#include "trie.hpp"

trie::trie()
{
    root = shared_ptr<Node>(new Node); root->value = ' ';
}

void sort(vector<shared_ptr<Node>>& nums)
{
    shared_ptr<Node> arr[nums.size()];
    int size = nums.size();
    for(int i=0; i<size; i++)
    {
        arr[i] = nums.back();
        nums.pop_back();
    }   
    shared_ptr<Node> temp;
    int j;
    int i=1;
    while(i<size)
    {
        j=i++;
        
        while(j && arr[j]->value < arr[j-1]->value)
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

}

void trie::insertWord(string word)
{
    shared_ptr<Node> temp = root;
    shared_ptr<Node> location = NULL;
    int size = word.length();
    for(int i=0; i<size; i++)
    {

        location = NULL;
        int vecSize = temp->children.size();
        for(int j=0; j<vecSize; j++)
        {
            if(temp->children[j]->value == word[i])
            {
                location = temp->children[j];
                break;
            }
        }
        if(location)
        {
            temp = location;
        }
        else
        {
            shared_ptr<Node> newNode(new Node);
            newNode->value = word[i]; 
            temp->children.push_back(newNode);
            sort(temp->children);
            temp = newNode;
        }
    }

}

bool trie::search(string word)
{
    shared_ptr<Node> temp = root;
    shared_ptr<Node> location = NULL;
    int size = word.length();
    for(int i=0; i<size; i++)
    {

        location = NULL;
        int vecSize = temp->children.size();
        for(int j=0; j<vecSize; j++)
        {
            if(temp->children[j]->value == word[i])
            {
                location = temp->children[j];
                break;
            }
        }
        if(location)
        {
            temp = location;
        }
        else
        {
            return false;
        }
    }
    return true;
}
string trie::longestSubstr(string word)
{
    shared_ptr<Node> temp = root;
    shared_ptr<Node> location = NULL;
    string answer = "";
    int size = word.length();
    for(int i=0; i<size; i++)
    {

        location = NULL;
        int vecSize = temp->children.size();
        for(int j=0; j<vecSize; j++)
        {
            if(temp->children[j]->value == word[i])
            {
                location = temp->children[j];
                break;
            }
        }

        if(i==0 && !location)
        {
            return "";
        }
        if(location)
        {
            temp = location;
            answer += word[i];
        }
        else
        {
            break;
        }
    }
    return answer;
}

vector<string> trie::getTrie()
{
    vector<string> result;
    getTrieHelper(root, "", result);
    return result;

}
void trie::deleteWord(string word)
{
    shared_ptr<Node> prev = root;
    shared_ptr<Node> current = root;
    shared_ptr<Node> check = NULL;

    for (int i = 0; i < word.length(); i++)
    {
        int len = current->children.size();
        for (int j = 0; j < len; j++)
        {
            if(current->children[j]->value == word[i])
            {
                check = current-> children[j];
                break;
            }
        }
        if(check)
        {
            prev = current;
            current = check;
        }
        if(i == word.length()-1 && !current->children.size())
        {
            deleteHelper(prev, current, word);
        }
    }
}

void trie::deleteHelper(shared_ptr<Node>& prev , shared_ptr<Node>& current, string word)
{ 
    int size = prev->children.size();
    int i=0;
    for(int i=0; i<size; i++)
    {
        
        if(prev->children[i] == current)
        {
            int len = prev->children.size();
            vector<shared_ptr<Node>> temp;
            for(int j=0; j<len; j++)
            {
                if(i != j)
                {
                    temp.push_back(prev->children[j]);
                }
                
            }
            sort(temp);
            prev->children.clear();
            prev->children = temp;
        }
    }
    word = word.substr(0,word.length()-1);
    deleteWord(word);
        
}

void trie::getTrieHelper(shared_ptr<Node> ptr, string word, vector<string>& result)
{

    if(!ptr->children.size())
    {
        result.push_back(word);
        return;
    }

    int size = ptr->children.size();
    for(int i=0; i<size; i++)
    {
        getTrieHelper(ptr->children[i], word + ptr->children[i]->value, result);
    }
    
}

// int main()
// {
//     trie my_trie;
//     my_trie.insertWord("BALL");
//     cout << endl;
//     my_trie.insertWord("BAT");
//     cout << endl;
//     my_trie.insertWord("BACK");

//     my_trie.deleteWord("BACK");
//     cout <<endl;
//     cout <<endl;
//     cout <<endl;
//     my_trie.deleteWord("BALL");
//     cout <<endl;
//     cout <<endl;
//     cout <<endl;
    
//     my_trie.deleteWord("BAT");

//     //cout << "final "<<my_trie.getRoot()->children.size();



//  }


#endif