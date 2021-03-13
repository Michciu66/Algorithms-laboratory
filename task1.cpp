#include <cstdio>
#include <iostream>
using namespace std;

/*
   Complete Implementation of single linked list with possible non-unique Keys using templates for compatibility with all data types,
   Created for Algorithms and Data Structures course, April 2020
*/

template <typename Key, typename Info>
class element 
{
private:
    Key key;
    Info info;
    element<Key, Info> *next;

public:
    element(Key _key, Info _info)
    {
        key = _key;
        info = _info;
        next = NULL;
    }
    element()
    {
        key = Key();
        info = Info();
        next = NULL;
    }
    void set_key(Key _key)
    {
        key = _key;
    }
    void set_info(Info _info)
    {
        info = _info;
    }
    void set_next(element<Key, Info> *_next)
    {
        next = _next;
    }
    element<Key, Info> *get_next() const
    {
        return next;
    }
    Key get_key() const
    {
        return key;
    }
    Info get_info() const
    {
        return info;
    }
    const element<Key, Info> &operator=(const element<Key, Info> &cmpr)
    {
        key = cmpr.get_key();
        info = cmpr.get_info();
        next = cmpr.get_next();
        return *this;
    }
};

template <typename Key, typename Info>
class Sequence
{
private:
    element<Key, Info> *HEAD;

public:
    Sequence()
    {
        HEAD = NULL;
    }
    ~Sequence()
    {
        element<Key, Info> *current = HEAD;
        while (current != NULL)
        {
            element<Key, Info> *prev = current;
            current = current->get_next();
            delete prev;
        }
    }
    bool insertFirst(const Key _key, const Info _info)
    {
        element<Key, Info> *newdata = new element<Key, Info>(_info, _key);
        newdata->set_next(HEAD);
        HEAD = newdata;
        if (HEAD == newdata)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool insertLast(const Key _key, const Info _info)
    {
        if (!HEAD)
        {
            this->HEAD = new element<Key, Info>(_key, _info);
            this->HEAD->set_next(NULL);
            return true;
        }
        element<Key, Info> *current = HEAD;
        element<Key, Info> *newdata = new element<Key, Info>(_key, _info);
        newdata->set_next(NULL);
        bool add = false;
        while (current && !add)
        {
            if (!current->get_next())
            {
                current->set_next(newdata);
                add = true;
            }
            current = current->get_next();
        }
        return add;
    }
    bool insertAfter(const Key _key, const Info _info, const Key where, int which) //Function for insertion after specific occurance of a specific key in the sequence (keys aren't unique)
    {
        element<Key, Info> *newdata = new element<Key, Info>(_key, _info);
        newdata->set_next(NULL);
        int count = 0;
        element<Key, Info> *curr = HEAD;
        if (!HEAD)
        {
            cout << "Can't insert after, list is empty" << endl;
            return false;
        }
        while (curr)
        {
            if (curr->get_key() == where)
            {
                count++;
                if (count == which)
                {
                    newdata->set_next(curr->get_next());
                    curr->set_next(newdata);
                    return true;
                }
            }
            curr = curr->get_next();
        }
        return false;
    }

    bool remove(const Key _key, int which) //Function for removal of specific occurance of specific key
    {
        int count = 0;
        element<Key, Info> *curr = HEAD;
        element<Key, Info> *prev = NULL;
        while (curr)
        {
            if (curr->get_key() == _key)
            {
                count++;
                if (count == which)
                {
                    if (curr == HEAD)
                    {
                        HEAD = curr->get_next();
                    }
                    else
                    {
                        prev->set_next(curr->get_next());
                    }
                    delete curr;
                    return true;
                }
            }
            prev = curr;
            curr = curr->get_next();
        }
        return false;
    }

    bool removeAll(const Key _key) //removes all occurances of a specific key in the list
    {
        if (!remove(_key, 1))
        {
            return false;
        }
        while (remove(_key, 1))
        {
        }
        return true
    }

    bool IsEmpty() const
    {
        return !HEAD;
    }

    bool clear()
    {
        while (!IsEmpty())
        {
            remove(HEAD->get_key(), 1);
        }
        return (!HEAD);
    }

    const Sequence<Key, Info> &operator=(const Sequence<Key, Info> &other)
    {
        if (other.IsEmpty()) //if the other list is empty, return an empty list
        {
            clear();
            return *this;
        }

        if (!IsEmpty()) //start with an empty list
        {
            clear();
        }

        this->HEAD = element<Key, Info>(
            other.HEAD->get_key(),
            other.HEAD->get_info()); //create a new HEAD

        element<Key, Info> otherCurr * = other.HEAD;

        do
        {
            otherCurr = otherCurr->get_next();
            insertLast(otherCurr->get_key(), otherCurr->get_info());
        } while (otherCurr->get_next() != NULL) //add copies of the elements of the other list

            return *this;
    }

    int size()
    {
        int count = 0;
        element<Key, Info> *curr = HEAD;
        while (curr)
        {
            count++;
            curr = curr->get_next();
        }
        return count;
    }
    element<Key, Info> *begin() const
    {
        return HEAD;
    }

    element<Key, Info> *end() const
    {
        if (!HEAD)
        {
            return NULL;
        }

        element<Key, Info> *curr = HEAD;

        while (!curr->get_next())
        {
            curr = curr->get_next();
        }

        return curr;
    }

    bool removeLast()
    {
        if (!HEAD)
        {
            return false;
        }
        element<Key, Info> *prev = HEAD;
        element<Key, Info> *curr = HEAD->get_next();
        if (!curr)
        {
            remove(HEAD->get_key(), 1);
            return true;
        }
        else
        {
            while (curr->get_next())
            {
                prev = curr;
                curr = curr->get_next();
            }
            prev->set_next(NULL);
            delete curr;
            return true;
        }
        return false;
    }

    int countByKey(const Key _key) //counts amount of occurances of  a key in the list
    {
        element<Key, Info> *curr = HEAD;
        int count = 0;
        while (curr)
        {
            if (curr->get_key() == _key)
            {
                count++;
            }
            curr = curr->get_next();
        }
        return count;
    }

    void print()
    {
        element<Key, Info> *curr = HEAD;
        if (!curr)
        {
            cout << "EMPTY SEQUENCE";
        }
        while (curr != NULL)
        {
            cout << curr->get_key() << " " << curr->get_info() << endl;
            curr = curr->get_next();
        }
    }
};
template <typename Key, typename Info>
Sequence<Key, Info> shuffle(const Sequence<Key, Info> &source1, int startIndex1, int length1, const Sequence<Key, Info> &source2, int startIndex2, int length2)
{
    /*
        This function shuffles elements from two lists into a third one.
        It works as follows: Starting from elements at the indexes startIndex1 and startIndex2 it first copies length1 elements from the first list, than length2 elements from the second
        Than it repeats the process until it reaches the end of both sequences
        Example:
        Sequence1: 1 2 3 4 5 6 7 8 9 10 
        Sequence2: 101 102 103 104 105 106 107 108 109 110
        startIndex1 = 3, length1 = 2, startIndex2 = 5, length = 3
        result: 3 4 105 106 107 5 6 108 109 110 7 8 9 10
    */
    Sequence<Key, Info> result;
    element<Key, Info> *curr1 = source1.begin();
    element<Key, Info> *curr2 = source2.begin();
    while (count1 != startIndex1) //find both starting points
    {
        if (!curr1)
        {
            break;
        }
        curr1 = curr1->get_next();
    }
    while (count2 != startIndex2)
    {
        if (!curr2)
        {
            break;
        }
        curr2 = curr2->get_next();
    }
    while (curr1 || curr2) //as long as there are still elements in either sequence
    {
        for (int i = 0; i < length1; i++)
        {
            if (!curr1)
            {
                break;
            }
            result.insertLast(curr1->get_key(), curr1->get_info());
            curr1 = curr1->get_next();
        }
        for (int j = 0; j < length2; j++)
        {
            if (!curr2)
            {
                break;
            }
            result.insertLast(curr2->get_key(), curr2->get_info());
            curr2 = curr2->get_next();
        }
    }
    return result;
}

int main()
{
    Sequence<int, int> seq1;
    seq1.insertFirst(1, 69);
    seq1.insertLast(69, 1);
    seq1.insertAfter(78, 420, 1, 1);
    seq1.insertLast(55, 2);
    Sequence<int, int> seq2;
    seq1.print();
    cout << "----------------------------------------------------------------------------------------------------------" << endl;
    seq2 = seq1;
    seq2.print();
    cout << "----------------------------------------------------------------------------------------------------------" << endl;
    seq2.removeLast();
    seq2.print();
    cout << "----------------------------------------------------------------------------------------------------------" << endl;
    seq1.clear();
    seq1.print();
    cout << endl;
    Sequence<int, int> shuffle1;
    Sequence<int, int> shuffle2;
    Sequence<int, int> shuffleresult;
    shuffle1.insertLast(1, 1);
    shuffle1.insertLast(2, 2);
    shuffle1.insertLast(3, 3);
    shuffle1.insertLast(4, 4);
    shuffle1.insertLast(5, 5);
    shuffle1.insertLast(6, 6);
    shuffle1.insertLast(7, 7);
    shuffle1.insertLast(8, 8);
    shuffle1.insertLast(9, 9);
    shuffle1.insertLast(10, 0);
    shuffle1.insertLast(11, 1);
    shuffle1.insertLast(12, 2);
    shuffle1.insertLast(13, 3);
    shuffle1.insertLast(14, 4);
    shuffle1.insertLast(15, 5);
    shuffle1.insertLast(16, 6);
    shuffle2.insertLast(0, 50);
    shuffle2.insertLast(1, 60);
    shuffle2.insertLast(2, 70);
    shuffle2.insertLast(3, 80);
    shuffle2.insertLast(4, 90);
    shuffle2.insertLast(5, 10);
    shuffle2.insertLast(6, 20);
    shuffle2.insertLast(7, 30);
    shuffle2.insertLast(8, 40);
    shuffle2.insertLast(9, 50);
    shuffle2.insertLast(10, 60);
    shuffle2.insertLast(11, 70);
    shuffle2.insertLast(12, 80);
    shuffle1.print();
    cout << "---------------------------------------------------------------------------------------------------------------------------" << endl;
    shuffle2.print();
    cout << "---------------------------------------------------------------------------------------------------------------------------" << endl;
    shuffleresult = shuffle<int, int>(shuffle1, 3, 3, shuffle2, 1, 2);
    cout << "Test for normal situation" << endl;
    shuffleresult.print();
    shuffle1.clear();
    shuffle2.clear();
    shuffleresult.clear();
    shuffle1.insertLast(1, 10);
    shuffle2.insertLast(1, 1);
    shuffle2.insertLast(2, 2);
    shuffle2.insertLast(3, 3);
    shuffleresult = shuffle<int, int>(shuffle1, 3, 3, shuffle2, 1, 2);
    cout << "Test for one sequence incomplete" << endl;
    shuffleresult.print();
    shuffle1.clear();
    shuffle2.clear();
    shuffleresult.clear();
    shuffleresult = shuffle<int, int>(shuffle1, 3, 3, shuffle2, 1, 2);
    cout << "Test for two empty sequences" << endl;
    shuffleresult.print();
}

