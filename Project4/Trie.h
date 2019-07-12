#ifndef TRIE_INCLUDED
#define TRIE_INCLUDED

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;


template<typename ValueType>
class Trie
{
public:
    Trie();
    ~Trie();
    void reset();
    void insert(const std::string& key, const ValueType& value);
    std::vector<ValueType> find(const std::string& key, bool exactMatchOnly) const;
    
    // C++11 syntax for preventing copying and assignment
    Trie(const Trie&) = delete;
    Trie& operator=(const Trie&) = delete;
private:
    struct VectorIndex;
    struct Node
    {
        vector<ValueType> currentValues;
        vector<VectorIndex*> nextNodes;
        ~Node()
        {
            for(int i = 0; i < nextNodes.size(); i++)
            {
                delete nextNodes[i];
            }
        }
    };
    struct VectorIndex
    {
        VectorIndex()
        {
            next = nullptr;
        }
        ~VectorIndex()
        {
            
        }
        char item;
        Node* next;
    };
    
    void removeNodes(Node* root);
    void findNode(Node* root, std::vector<ValueType>& items, const string& key, bool mismatches) const; //std::vector<ValueType>
    int containsValue(VectorIndex* current, char c);
    //int numNodes = 0;
    Node* root;
};

template<typename ValueType>
Trie<ValueType>::Trie()
{
    root = new Node;
}



template<typename ValueType>
Trie<ValueType>::~Trie()
{
    removeNodes(root);
}


template<typename ValueType>
void Trie<ValueType>::removeNodes(Node* root)
{
    if(root == nullptr)
        return;
    
    for(auto p = root->nextNodes.begin(); p != root->nextNodes.end(); p++)
    {
        removeNodes((*p)->next);
    }
    
    delete root;
}

template<typename ValueType>
void Trie<ValueType>::reset()
{
    removeNodes(root);
    root = new Node;
}
//
template<typename ValueType>
int Trie<ValueType>::containsValue(VectorIndex *current, char c)
{
    int i = 0;
    for(; i < current->nextNodes.size(); i++)
    {
        if(current->nextNodes[i].item == c)
            break;
    }
    
    return 1;
}


template<typename ValueType>
void Trie<ValueType>::insert(const string& key, const ValueType& value)
{
    string input = key;
    Node* current = root;

    while(input.size() != 0)
    {
        int i = 0;
        for(; i < current->nextNodes.size(); i++)
        {
            if(current->nextNodes[i]->item == input[0])
                break;
        }
        if(i < current->nextNodes.size())
        {
            current = current->nextNodes[i]->next;
            input = input.substr(1);
        }
        else
        {
            VectorIndex* newNode = new VectorIndex;
            newNode->next  = new Node;
            newNode->item = input[0];
            input = input.substr(1);
            current->nextNodes.push_back(newNode);
            current = newNode->next;
        }
    }

    current->currentValues.push_back(value);
    //numNodes++;
    
    
}

template<typename ValueType>
void Trie<ValueType>::findNode(Node* root, std::vector<ValueType>& items, const string& key, bool mismatches) const
{
    if(key.size() == 0)
    {
        items.insert(items.begin(), root->currentValues.begin(), root->currentValues.end());
        return;
    }
    if(root->nextNodes.size() == 0)
        return;
    
    for(int i = 0; i < root->nextNodes.size(); i++)
    {
        if(root->nextNodes[i]->item == key[0])
        {
            if(key.size() == 1)
            {
                findNode(root->nextNodes[i]->next, items, "", mismatches);
            }
            else
                findNode(root->nextNodes[i]->next, items, key.substr(1), mismatches);
        }
        else if(mismatches)
        {
            if(key.size() == 1)
            {
                findNode(root->nextNodes[i]->next, items, "", false);
            }
            else
            {
                findNode(root->nextNodes[i]->next, items, key.substr(1), false);
            }
        }
    }
}

template<typename ValueType>
std::vector<ValueType> Trie<ValueType>::find(const std::string& key, bool exactMatchOnly) const
{
    
    vector<ValueType> finalVector;
    
    int i = 0;
    for(; i < root->nextNodes.size(); i++)
    {
        if(root->nextNodes[i]->item == key[0])
            break;
    }
    if(i < root->nextNodes.size())
        
    {
        if(key.size() == 1)
            finalVector.insert(finalVector.begin(), root->currentValues.begin(), root->currentValues.end()); //ask
        else
            findNode(root, finalVector, key, !exactMatchOnly);
    }
    
    return finalVector;
}

#endif // TRIE_INCLUDED

