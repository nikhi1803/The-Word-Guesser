#include<iostream>
#include<fstream>
#include<stdio.h>
#include<bits/stdc++.h>
#include<string.h>
#include<windows.h>
//#include"samledspack1.h"
#define ALPHABET_SIZE (26)
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')
using namespace std;
class TrieNode
{
public:
    TrieNode *children[ALPHABET_SIZE];
    bool isWordEnd;     // flag variable for the wordend
};
void serialize(TrieNode *root,ofstream &fp);
int deserialize(TrieNode *root,ifstream &fp);
TrieNode* getNode()
{
	TrieNode *pNode = new TrieNode;
	pNode->isWordEnd = false;
	for (int i = 0; i < ALPHABET_SIZE; i++)
		pNode->children[i] = NULL;
	return pNode;
}
void insert1(TrieNode *root, const string key)
{
	TrieNode *pCrawl = root;
	TrieNode*a;
	for (int level = 0; level < key.length(); level++)
	{   int index = CHAR_TO_INDEX(key[level]);
        if(!pCrawl->children[index])
        {
              (pCrawl->children[index] = getNode());
        }
        pCrawl = pCrawl->children[index];
	}
    pCrawl->isWordEnd = true;
}
bool search(TrieNode *root, const string key)
{
	int length = key.length();
	TrieNode *pCrawl = root;
	for (int level = 0; level < length; level++)
	{
		int index = CHAR_TO_INDEX(key[level]);

		if (!pCrawl->children[index])
			return false;

		pCrawl = pCrawl->children[index];
	}

	return (pCrawl != NULL && pCrawl->isWordEnd);
}
bool isLastNode(TrieNode* root)
{
	for (int i = 0; i < ALPHABET_SIZE; i++)
		if (root->children[i])
			return 0;
	return 1;
}
void suggestions(TrieNode* root, string currPrefix)
{
	// found a string in Trie with the given prefix
	//myrfile.read((char *)&pCrawl,sizeof(pCrawl));

	if (root->isWordEnd)
	{
		cout << currPrefix;
		//cout<<"\nprinting in currprefix\n\n";
		cout << endl;
	}

	// All children struct node pointers are NULL
	if (isLastNode(root))
		return;

	for (int i = 0; i < ALPHABET_SIZE; i++)
	{
		if (root->children[i])
		{
			// append current character to currPrefix string
			char c=97+i;
			currPrefix+=c;
			suggestions(root->children[i], currPrefix);
			char ch;
            int n=currPrefix.length();
			for(int j=0;j<n;j++)
            {
                if(ch=='\0')
                {
                    currPrefix[j-1]='\0';
                    currPrefix.erase(n-1);
                    break;

                }
            }
		}
	}
}
int printAutoSuggestions(TrieNode* root, const string query)
{
	TrieNode* pCrawl = root;
	int level;
	int n = query.length();
	for (level = 0; level < n; level++)
	{
		int index = CHAR_TO_INDEX(query[level]);
		if (!pCrawl->children[index])
		{   return 0;
		}
		pCrawl= pCrawl->children[index];
	}
	bool isWord = search(pCrawl,query);
	// If prefix is last node of tree (has no
	// children)
	bool isLast = isLastNode(pCrawl);

	// If prefix is present as a word, but
	// there is no subtree below the last
	// matching node.
	if (isWord && isLast)
	{
		cout << query << endl;
		return -1;
	}
	if (!isWord)
	{
		string prefix = query;
		suggestions(pCrawl, prefix);
		return 1;
	}
}
int main()
{
    //string ch;
    //ofstream Myfile;
    //Myfile.open("filename.txt");
    for(int i=0;i<1000;i++)
    {
        cout<<".";
        if(i%5==0)
        {
            system("cls");
            cout<<"\n\n\n\n\t\t\t\t\tLOADING.";
        }
    }
    system("cls");
    cout<<"\n\n\n\n\n\t\t\t\t\tWELCOME TO AUTOCORRECT FEATURE \n\n";
    cout<<"\t\tIN THIS PROGRAM WE HAVE USED TRIE DATA STRUCTURE FOR AUTOCOMPLETE WHICH IS MORE EFFICIENT";
    cout<<" \n\n\t\tIT REDUCES THE SEARCH TIME AND IT IMPLEMENTED FROM BINARY SEACRH TREE ";
    cout<<"\n\n\t\t\t\t\t\t\tDONE BY:\n\n\t\t\t\t\t\t\t\tMATHUMITHA S R (19PW14)\n\n\t\t\t\t\t\t\t\tNIKHITA BINU(19PW18)";
    Sleep(5000);
    system("CLS");
    TrieNode*root = getNode();
    /*ifstream fin("ttext.txt",ios::in);
    string k;
    int i=0;
    while(!fin.eof())
    {
        fin>>k;
        insert1(root,k);
        i++;

    }
    cout<<i;
    fin.close();
    cout<<"trie imsertion completed:";
    cout<<"trie imsertion completed:";
    serialize(root,Myfile);
    Myfile.close();*/
    ifstream Myfile("filename.txt",ios::in);
    deserialize(root,Myfile);
	string temp,t;
	int f,f1;
	int n;
	//do
   // {
        cout<<"\n\t\t\tSearch for a string\t\n\n";
        int ch;
        do
        {   cout<<"\n\t\tSearch string";
            cout<<"\n\nENTER A STRING   :";
            cin>>temp;
            int comp = printAutoSuggestions(root, temp);
            if (comp == -1)
                cout << "No other strings found with this prefix\n";
            else if (comp == 0)
                cout << "No string found with this prefix\n";
            cout<<"\n Do u want to continue :";
            cin>>ch;
        }while(ch!=0);
      //  cout<<"\n Do u want to continue :";
        //cin>>f1;
    //}while(f1==1);
    cout<<"\n\n--------------------------------------------THANK YOU------------------------------------------------";
    return 0;
}
void serialize(TrieNode *root,ofstream &fp)
{
    if(root->isWordEnd==true )
        if(root==NULL)
            return;
    for(int i=0;i<26;i++)
    {
        if(root->children[i])
        {
            char k = i+97;
            fp<<k;
            serialize(root->children[i],fp);
            fp<<'(';
        }
    }
}

int deserialize(TrieNode *root,ifstream &fp)
{
    char c;
    string str;
    int a=0,b=0;
    while(!fp.eof())
    {   fp>>c;
        if(c == '(')
        {
            if(a == 0)
            {
                insert1(root , str);
                a++;
                b++;
            }
            int k=str.size()-1;
            if(k >= 0)
                str.resize(k);
        }
        else
        {
            str+=c;
            a=0;
        }
    }
    cout<<"insertion completed:"<<b<<endl;
    return 0;
}
