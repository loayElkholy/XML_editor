#ifndef TREE_H
#define TREE_H
#include <string>
#include <vector>
#include <iostream>

using namespace std;

typedef struct {
    string name;
    vector<pair<string, string>> attr;
}tag;

struct xml_parse {
    string xml_parsed;
    int line_no;
};

class Node {
public:
    string name;
    string value;
    string attribute;
    bool is_self_closing;
    bool found;
    Node* parent;
    vector <Node*> children;
    Node(string name) : name{ name },found{false}, value{ "\0" }, attribute{ "\0" }, is_self_closing{false}, children{}, parent{ nullptr }{}
};

class Tree
{
    Node* root;
    Node* add;
    int depth = 0;
    void print(Node* root_ptr, string* no_space);
    void Pjson(Node* r, bool flag);
    void print_attr(vector<pair<string, string>>s);
    void find(Node* r, int ind, vector<int>& index);
    void ind();
    tag get_tag_struct(string s1, string name);
    void format(Node* root, int count);

public:
    void format_public();
    void minify(string no_space);
    vector<int> vector_to_tree(vector<xml_parse> v);
    void json();
};

#endif // TREE_H
