#include <bits/stdc++.h>
using namespace std;


map<char, string> HuffmanCodes;
map<char, int> CharFreq;
class DataNode
{
    public:
    char data;
    int CharFreq;
    DataNode *left, *right;

    DataNode(char data, int CharFreq)
    {
        left = NULL;
        right = NULL;
        this->data = data;
        this->CharFreq = CharFreq;
    }
};

void countCharFreq(string str,int n){
    for(int i=0;i<n;i++){
        CharFreq[str[i]]++;
        }
}

struct compare
{
    bool operator()(DataNode* l, DataNode* r)
    {
        return (l->CharFreq > r->CharFreq);
    }
};

void printHuffmanCodes(struct DataNode* root, string str)
{
    if (!root)
        return;
    if (root->data != '$')
        cout << root->data << ": " << str << "\n";
    printHuffmanCodes(root->left, str + "0");
    printHuffmanCodes(root->right, str + "1");
}


void storeHuffmanCodes(struct DataNode* root, string str)
{
    if (root==NULL)
        return;
    if (root->data != '$')
        HuffmanCodes[root->data]=str;
    storeHuffmanCodes(root->left, str + "0");
    storeHuffmanCodes(root->right, str + "1");
}

priority_queue<DataNode*, vector<DataNode*>, compare> HuffmanTree;


void findHuffmanCodes(int size)
{
    struct DataNode *left, *right, *top;
    map<char, int>::iterator mp;
    for (mp=CharFreq.begin(); mp!=CharFreq.end(); mp++){
        DataNode *node=new DataNode(mp->first, mp->second);
        HuffmanTree.push(node);
    }
    while (HuffmanTree.size() != 1)
    {
        left = HuffmanTree.top();
        HuffmanTree.pop();
        right = HuffmanTree.top();
        HuffmanTree.pop();
        top = new DataNode('$', left->CharFreq + right->CharFreq);
        top->left = left;
        top->right = right;
        HuffmanTree.push(top);
    }
    storeHuffmanCodes(HuffmanTree.top(), "");
}

string decode_file(struct DataNode* root, string s)
{
    string ans = "";
    DataNode* curr = root;
    for (int i=0;i<s.size();i++)
    {
        if (s[i] == '0')
           curr = curr->left;
        else
           curr = curr->right;
        if (curr->left==NULL and curr->right==NULL)
        {
            ans += curr->data;
            curr = root;
        }
    }
    return ans+'\0';
}

int main()
{
    string str;
    cout<<"ENTER THE DATA TO BE COMPRESSED:-"<<endl;
    cin>>str;
    string EncodedData,DecodedData;
    countCharFreq(str,str.size());
    findHuffmanCodes(str.length());
    cout<<endl;
    cout << "Characters with there HuffmanCodes:-"<<endl;
    map<char,string>:: iterator itr;
    for ( itr=HuffmanCodes.begin(); itr!=HuffmanCodes.end(); itr++){
        cout << itr->first <<' ' << itr->second << endl;}

    for(int i=0;i<str.size();i++){
        EncodedData+=HuffmanCodes[str[i]];
    }
    cout << "\nEncoded Huffman data:\n" << EncodedData << endl;

    DecodedData = decode_file(HuffmanTree.top(), EncodedData);
    cout << "\nDecoded Huffman Data:\n" << DecodedData << endl;

    cout<<"\nSpace Requirement Of The Original File:-"<<" "<<str.size()*8<<" bits"<<endl;
    cout<<endl;
    cout<<"\nSpace Requirement Of The Encoded File:-"<<" "<<EncodedData.size()<<" bits"<<endl;

    return 0;
}
