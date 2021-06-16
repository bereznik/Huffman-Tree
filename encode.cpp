#include "huffman.h"

using namespace std;


void print_freq_table(unordered_map<char,int> table) {
    unordered_map<char, int>::iterator it;
    for (it = table.begin(); it != table.end(); ++it)
      cout << it -> first << " => " << it -> second << endl;
}

void make_freq_table(unordered_map<char,int> &table) {
    fstream my_file;
    my_file.open("input.txt", ios::in);

    if (!my_file)
        cout << "No such file" << endl;
    else {
        char ch;
        while (!my_file.eof()) {
            my_file >> ch;
            if (!my_file.eof()) //To prevent from counting the last char one extra time
                table[ch]++; 
        }
    }
    my_file.close();
}



void dfs(Node* nd, ofstream& file) { //Print pre-order and write to file
    if (nd == nullptr)
        return;
    file << nd -> val << "*" << nd -> freq << "*";
    //cout << "Char: " << nd -> val << " Freq: " << nd ->freq << endl;
    
    dfs(nd -> left, file);
    dfs(nd -> right, file);
}

void sim(Node* nd, ofstream& file) { //Print in-order and write to file
    if (nd == nullptr)
        return;
    sim(nd -> left, file);
    sim(nd -> right, file);
    
    file << nd -> val << "*" << nd ->freq << "*";
    //cout << "Char: " << nd -> val << " Freq: " << nd -> freq << endl;    
}

bool char_code(Node *root, char x, string& code) {
    code = "";
    // if root is NULL
    // there is no path
    if (!root)
        return false;
      
    // push the node's value in 'arr'
    //arr.push_back(root->val);    
      
    // if it is the required node
    // return true
    if (root -> val == x)    
        return true;
      
    // else check whether the required node lies
    // in the left subtree or right subtree of 
    // the current node
    if (char_code(root -> left, x, code)) { 
        code = '0' + code;
        return true;
    }    
    if (char_code(root -> right, x, code)) {
        code = '1' + code;
        return true; 
    }
    // required node does not lie either in the 
    // left or right subtree of the current node
    // Thus, remove current node's value from 
    // 'arr'and then return false    
    //arr.pop_back();
    return false;            
}

void get_encoded_file(Node *root, string input_file) { // Creates texto.hfm file representing original text
    fstream my_file;
    fstream output_file;
    string aux;
    
    my_file.open(input_file, ios::in);
    
    if (!my_file)
        cout << "No such file" << endl;
    else {
        char ch;
        string aux="";
        while (!my_file.eof()) {
                string aux2= "";
                my_file >> ch;
                char_code(root, ch, aux2);
                aux = aux + aux2; 
    }
        my_file.close();
        output_file.open("texto.hfm", ios::out);
            output_file << aux;
        output_file.close();
    }
}

int main() {
    
    unordered_map<char,int> table;
    make_freq_table(table);
    print_freq_table(table);

    Tree t (table);
    
    ofstream my_file;
    my_file.open("arvhuf.txt");
    sim(t.root, my_file);
    dfs(t.root, my_file);
    my_file.close();

    string aux = "";
    get_encoded_file(t.root,"input.txt");

}

