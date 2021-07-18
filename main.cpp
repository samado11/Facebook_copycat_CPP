#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <linked_list.h>
#include <Node.h>
#include <Treap.h>
#include <User.h>
using namespace std;

    void ROTATE_LEFT(Treap* &root)
{
    Treap* R = root->r;
    Treap* X = root->r->l;
    R->l = root;
    root->r= X;
    root = R;
}
void rotRight(Treap* &root)
{
    Treap* L = root->l;
    Treap* Y = root->l->r;
    L->r = root;
    root->l= Y;
    root = L;
}

bool SEARCH(Treap* root, string key)
{
    if (root == nullptr)
        return false;
    if (root->data == key)
        return true;
    if (key < root->data)
        return SEARCH(root->l, key);
    return SEARCH(root->r, key);
}
void DELETE(Treap* &root, string key)
{
    if (root == nullptr)
        return;
    if (key < root->data)
        DELETE(root->l, key);
    else if (key > root->data)
        DELETE(root->r, key);
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
                ROTATE_LEFT(root);
                DELETE(root->l, key);
            }
            else
            {
                rotRight(root);
                DELETE(root->r, key);
            }
        }
        else
        {
            Treap* child = (root->l)? root->l: root->r;
            Treap* curr = root;
            root = child;
            delete curr;
        }
    }
}
void displayTreap(Treap *root, int space = 0, int height =10)
{
    if (root == nullptr)
        return;
    space += height;
    displayTreap(root->l, space);
    cout << root->data;
    cout << endl;
    displayTreap(root->r, space);
}
void INSERT(Treap* &root, string d)
{
    if (root == nullptr)
    {
        root = new Treap(d);
        return;
    }
    if (d.compare(root->data)<0)
    {
        INSERT(root->l, d);
        if (root->l != nullptr && root->l->priority > root->priority)
            rotRight(root);
    }
    else
    {
        INSERT(root->r, d);
        if (root->r!= nullptr && root->r->priority > root->priority)
            ROTATE_LEFT(root);
    }
}
vector<string> STR_CUT(const string& str, const char& ch)
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

void printList(Node* node)
{
    while (node != NULL)
    {
        cout <<node->data.name<<"   "<<node->data.userName<<"   "<< node->data.email<< "\n";
        node = node->next;
    }
}
int main()
{
    vector<string> USERS ;
    ifstream  MAIN_NETWORK;
    MAIN_NETWORK.open ("all-users-relations.in");
    string line1;
    if (MAIN_NETWORK.is_open())
    {
        linked_list a;
        while ( getline (MAIN_NETWORK,line1) )
        {
            USERS.push_back(line1);
            cout << line1 << '\n';


        }

        MAIN_NETWORK.close();
    }

    else cout << "Unable to open file";

    MAIN_NETWORK.close();

    ifstream  USERS_INFO;
    USERS_INFO.open ("all-users.in");
    string line;
    linked_list a;
    if (USERS_INFO.is_open())
    {


        while ( getline (USERS_INFO,line) )
        {
            Treap* root = nullptr;
            //cout << line << '\n';
            std::vector<std::string> result = STR_CUT(line, ',');
            User* main_user = NULL;
            main_user = new User();
            main_user->userName = result[0];
            main_user->name = result[1];
            main_user->email = result[2];
            for (int i = 0; i != USERS.size(); ++i)
            {
                if (USERS.at(i).substr(0, USERS.at(i).find(',')).compare(main_user->userName)==0)
                {
                    INSERT(root, USERS.at(i).substr(USERS.at(i).find(',')+2));

                }
                else if(USERS.at(i).substr(USERS.at(i).find(',')+2).compare(main_user->userName)==0)
                {
                    INSERT(root, USERS.at(i).substr(0, USERS.at(i).find(',')));
                }
            }
            main_user->fbst=root;
            a.add_node(*main_user);

        }

        //printList(a.head);
        USERS_INFO.close();
    }

    else cout << "Unable to open file";

    USERS_INFO.close();

    while(true)
    {
        cout<<" Enter your username"<<endl;
        string user_input;
        cin>>user_input;
        User USER_ONE;
        bool flag =false;
        if (user_input.compare("exit") !=0)
        {
            Node* n=a.head;
            while (n != NULL)
            {
                if (n->data.userName == user_input )
                {
                    USER_ONE=n->data;
                    cout<<"logged in successfully"<<endl;
                    flag=true;
                    break;
                }
                n = n->next;
            }
            if (flag == false){
                cout<<"Wrong username"<<endl;
                continue;
            }
            while(true)
            {
                cout<<" 1)List all friends"
                <<endl<<" 2)search by username"
                <<endl<<" 3)add friend"
                <<endl<<" 4)remove friend"
                <<endl<<" 5)people you may know"
                <<endl<<" 6)logout"<<endl;
                string user_input_two;
                cin>>user_input_two;
                if(user_input_two.compare("1")==0)
                {
                    cout<<endl;
                    cout<<"--------------- Friends List ---------------------"<<endl<<endl;
                    displayTreap(USER_ONE.fbst);
                    cout<<endl;
                    cout<<endl;
                    cout<<endl;
                    cout<<endl;
                    cout<<endl;
                    cout<<endl;
                    cout<<endl;
                }
                if(user_input_two.compare("2")==0)
                {
                    string username;
                    cin>>username;

                    if(SEARCH(USER_ONE.fbst,username)==true)
                    {
                        Node* n=a.head;
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
                if(user_input_two.compare("3")==0)
                {
                    string username;
                    cin>>username;
                    Node* n1=a.head;
                    User USER_TWO;
                    while (n1 != NULL)
                    {
                        if (n1->data.userName == username )
                        {
                            USER_TWO=n1->data;
                            break;
                        }
                        n1 = n1->next;
                    }

                    if(SEARCH(USER_ONE.fbst,username)!=true)
                    {
                        Node* n=a.head;
                        while (n != NULL)
                        {
                            if (n->data.userName == username )
                            {
                                INSERT(USER_ONE.fbst, username);
                                INSERT(USER_TWO.fbst, USER_ONE.userName);
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
                if(user_input_two.compare("4")==0)
                {
                    string username;
                    cin>>username;
                    Node* n1=a.head;
                    User USER_TWO;
                    while (n1 != NULL)
                    {
                        if (n1->data.userName == username )
                        {
                            USER_TWO=n1->data;
                            break;
                        }
                        n1 = n1->next;
                    }
                    Node* n=a.head;
                    while (n != NULL)
                    {
                        if (n->data.userName == username )
                        {
                            DELETE(USER_ONE.fbst, username);
                            DELETE(USER_TWO.fbst, USER_ONE.userName);
                            cout<<"Done"<<endl;
                            break;
                        }
                        n = n->next;
                    }
                }
                if(user_input_two.compare("5")==0)
                {
                    Node* n=a.head;
                    int count=0;
                    cout<<endl;
                    cout<<"--------------- People you may know ---------------------"<<endl<<endl;
                    while (n != NULL)
                    {
                        if(SEARCH(USER_ONE.fbst,n->data.userName)!=true && n->data.userName.compare(USER_ONE.userName) !=0 && count <5)
                        {
                            cout<<n->data.userName<<endl;

                            count++;
                        }
                        n = n->next;
                    }
                    cout<<endl;
                    cout<<endl;
                    cout<<endl;
                    cout<<endl;
                    cout<<endl;
                    cout<<endl;
                    cout<<endl;
                }
                if(user_input_two.compare("6")==0)
                {
                    break;
                }
                if(user_input_two.compare("exit")==0)
                    return false;

            }
        }
        else
        {
            return false;
        }

    }

    return 0;
}

