#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

vector<string> explode(const string& str, const char& ch)
{
    string next;
    vector<string> result;

    for (string::const_iterator it = str.begin(); it != str.end(); it++)
    {
        if (*it == ch)
        {
            if (!next.empty())
            {
                result.push_back(next);
                next.clear();
            }
        }
        else
        {
            next += *it;
        }
    }
    if (!next.empty())
        result.push_back(next);
    return result;
}


struct TreapNod    //node declaration
{
    string data;
    int priority;
    TreapNod* l, *r;
    TreapNod(string d)   //constructor
    {
        this->data = d;
        this->priority = rand() % 100;
        this->l= this->r = nullptr;
    }
};
void rotLeft(TreapNod* &root)   //left rotation
{
    TreapNod* R = root->r;
    TreapNod* X = root->r->l;
    R->l = root;
    root->r= X;
    root = R;
}
void rotRight(TreapNod* &root)   //right rotation
{
    TreapNod* L = root->l;
    TreapNod* Y = root->l->r;
    L->r = root;
    root->l= Y;
    root = L;
}
void insertNod(TreapNod* &root, string d)   //insertion
{
    if (root == nullptr)
    {
        root = new TreapNod(d);
        return;
    }
    if (d.compare(root->data)<0)
    {
        insertNod(root->l, d);
        if (root->l != nullptr && root->l->priority > root->priority)
            rotRight(root);
    }
    else
    {
        insertNod(root->r, d);
        if (root->r!= nullptr && root->r->priority > root->priority)
            rotLeft(root);
    }
}
bool searchNod(TreapNod* root, string key)
{
    if (root == nullptr)
        return false;
    if (root->data == key)
        return true;
    if (key < root->data)
        return searchNod(root->l, key);
    return searchNod(root->r, key);
}
void deleteNod(TreapNod* &root, string key)
{
    if (root == nullptr)
        return;
    if (key < root->data)
        deleteNod(root->l, key);
    else if (key > root->data)
        deleteNod(root->r, key);
    else
    {
        if (root->l ==nullptr && root->r == nullptr)
        {
            delete root;
            root = nullptr;
        }
        else if (root->l && root->r)
        {
            if (root->l->priority < root->r->priority)
            {
                rotLeft(root);
                deleteNod(root->l, key);
            }
            else
            {
                rotRight(root);
                deleteNod(root->r, key);
            }
        }
        //node to be deleted has only one child
        else
        {
            TreapNod* child = (root->l)? root->l: root->r;
            TreapNod* curr = root;
            root = child;
            delete curr;
        }
    }
}
void displayTreap(TreapNod *root, int space = 0, int height =10)   //display treap
{
    if (root == nullptr)
        return;
    space += height;
    displayTreap(root->l, space);
    cout << root->data;
    cout << endl;
    displayTreap(root->r, space);
}

class User
{
public:
    string name;
    string email;
    string userName;
    TreapNod  *fbst;
};
struct node
{
    User data;
    node *next;
};
class linked_list
{
public:
    node *head,*tail;
public:
    linked_list()
    {
        head = NULL;
        tail = NULL;
    }

    void add_node(User n)
    {
        node *tmp = new node;
        tmp->data = n;
        tmp->next = NULL;

        if(head == NULL)
        {
            head = tmp;
            tail = tmp;
        }
        else
        {
            tail->next = tmp;
            tail = tail->next;
        }
    }

};
void printList(node* n)
{
    while (n != NULL)
    {
        cout <<n->data.name<<"   "<<n->data.userName<<"   "<< n->data.email<< "\n";
        n = n->next;
    }
}
int main()
{
    vector<string> users_vector ;
    ifstream  usersRelations;
    usersRelations.open ("all-users-relations.in");
    string line1;
    if (usersRelations.is_open())
    {
        linked_list a;
        while ( getline (usersRelations,line1) )
        {
            users_vector.push_back(line1);
            cout << line1 << '\n';


        }

        usersRelations.close();
    }

    else cout << "Unable to open file";

    usersRelations.close();



    ifstream  users;
    users.open ("all-users.in");
    string line;
    linked_list a;
    if (users.is_open())
    {


        while ( getline (users,line) )
        {
            TreapNod* root = nullptr;
            //cout << line << '\n';
            std::vector<std::string> result = explode(line, ',');
            User* user1 = NULL;
            user1 = new User();
            user1->userName = result[0];
            user1->name = result[1];
            user1->email = result[2];
            for (int i = 0; i != users_vector.size(); ++i)
            {
                if (users_vector.at(i).substr(0, users_vector.at(i).find(',')).compare(user1->userName)==0)
                {
                    insertNod(root, users_vector.at(i).substr(users_vector.at(i).find(',')+2));

                }
                else if(users_vector.at(i).substr(users_vector.at(i).find(',')+2).compare(user1->userName)==0)
                {
                    insertNod(root, users_vector.at(i).substr(0, users_vector.at(i).find(',')));
                }
            }
            user1->fbst=root;
            a.add_node(*user1);

        }

        printList(a.head);
        users.close();
    }

    else cout << "Unable to open file";

    users.close();

    while(true)
    {
        string choice;
        cin>>choice;
        User user;
        if (choice.compare("exit") !=0)
        {
            node* n=a.head;
            while (n != NULL)
            {
                if (n->data.userName == choice )
                {
                    user=n->data;
                    cout<<"you are logged in"<<endl;
                    break;
                }
                n = n->next;
            }
            while(true)
            {
                cout<<"1)List all friends"<<endl<<"2)search by username"<<endl<<"3)add friend"<<endl<<"4)remove friend"<<endl<<"5)people you may know"<<endl<<"6)logout"<<endl;
                string logged_choice;
                cin>>logged_choice;
                if(logged_choice.compare("1")==0)
                {
                    displayTreap(user.fbst);
                    cout<<endl;
                }
                if(logged_choice.compare("2")==0)
                {
                    string username;
                    cin>>username;

                    if(searchNod(user.fbst,username)==true)
                    {
                        node* n=a.head;
                        while (n != NULL)
                        {
                            if (n->data.userName == username )
                            {
                                cout<<n->data.email<<"   "<<n->data.userName<<"   "<< n->data.email<<endl;
                                break;
                            }
                            n = n->next;
                        }
                    }
                    else
                    {
                        cout<<"Not found"<<endl;
                    }
                    cout<<endl;
                }
                if(logged_choice.compare("3")==0)
                {
                    string username;
                    cin>>username;
                    node* n1=a.head;
                    User user1;
                    while (n1 != NULL)
                    {
                        if (n1->data.userName == username )
                        {
                            user1=n1->data;
                            break;
                        }
                        n1 = n1->next;
                    }

                    if(searchNod(user.fbst,username)!=true)
                    {
                        node* n=a.head;
                        while (n != NULL)
                        {
                            if (n->data.userName == username )
                            {
                                insertNod(user.fbst, username);
                                insertNod(user1.fbst, user.userName);
                                cout<<"you are now friends"<<endl;
                                break;
                            }
                            n = n->next;
                        }
                    }
                    else
                    {
                        cout<<"you are already friends"<<endl;
                    }

                }
                if(logged_choice.compare("4")==0)
                {
                    string username;
                    cin>>username;
                    node* n1=a.head;
                    User user1;
                    while (n1 != NULL)
                    {
                        if (n1->data.userName == username )
                        {
                            user1=n1->data;
                            break;
                        }
                        n1 = n1->next;
                    }
                    node* n=a.head;
                    while (n != NULL)
                    {
                        if (n->data.userName == username )
                        {
                            deleteNod(user.fbst, username);
                            deleteNod(user1.fbst, user.userName);
                            cout<<"Done"<<endl;
                            break;
                        }
                        n = n->next;
                    }
                }
                if(logged_choice.compare("5")==0)
                {
                    node* n=a.head;
                    int count=0;
                    while (n != NULL)
                    {
                        if(searchNod(user.fbst,n->data.userName)!=true && n->data.userName.compare(user.userName) !=0 && count <5){
                            cout<<n->data.userName<<endl;
                             count++;
                        }
                        n = n->next;
                    }
                }
                if(logged_choice.compare("6")==0)
                {
                    break;
                }
                if(logged_choice.compare("exit")==0)
                    return false;

            }
        }
        else
        {
            return false;
        }

    }

    /*BST b, *root = NULL;
    root = b.Insert(root, *user1);
    b.Inorder(root);*/

    return 0;
}

