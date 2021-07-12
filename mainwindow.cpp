#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include<string>
#include<string.h>
#include<algorithm>



using namespace std;
class Node {
public:
    string name;
    string value;
    string attribute;
    bool is_self_closing;
    Node* parent;
    vector <Node*> children;
    Node(string name) : name{ name }, value{ "\0" }, attribute{ "\0" }, is_self_closing{false}, children{}, parent{ nullptr }{}
};

class Tree
{
    Node* root;
    Node* add;

public:
    vector<int> vector_to_tree(vector<xml_parse> v) {
        string s ;
        int space;
        Node* new_node;
        space = v[0].xml_parsed.find(' ');
        if (space == -1) {
            s = v[0].xml_parsed.substr(1, v[0].xml_parsed.length() - 2);
            new_node = new Node(s);
        }
        else {
            s = v[0].xml_parsed.substr(1, space -1);
            new_node = new Node(s);
            s = v[0].xml_parsed.substr(space + 1, v[0].xml_parsed.length() - space - 2);
            new_node->attribute = s;
        }
        root = new_node;
        add = new_node;
        vector<int> error;

        for (int i = 1; i < v.size(); i++) {
            if (v[i].xml_parsed[0] == '<') {
                if (v[i].xml_parsed[1] == '/'){
                    s = v[i].xml_parsed.substr(2, v[i].xml_parsed.length() - 3);
                    if (add->name == s) {
                        add = add->parent;
                    }
                    else {
                        error.push_back((v[i].line_no));
                        add = add->parent;
                    }
                }
                else {
                    if (add->value != "\0") {
                        error.push_back((v[i].line_no));
                        add = add->parent;
                    }
                    space = v[i].xml_parsed.find(' ');
                    if (space == -1) {
                        s = v[i].xml_parsed.substr(1, v[i].xml_parsed.length() - 2);
                        new_node = new Node(s);
                        new_node->parent = add;
                    }
                    else {
                        s = v[i].xml_parsed.substr(1,space -1);
                        new_node = new Node(s);
                        new_node->parent = add;
                        s = v[i].xml_parsed.substr(space + 1, v[i].xml_parsed.length()-space-2);
                        if (s.back() == '/') {
                            new_node->is_self_closing = true;
                            s = v[i].xml_parsed.substr(space + 1, v[i].xml_parsed.length() - space - 3);
                            new_node->attribute = s;
                        }
                        else {
                            new_node->attribute = s;
                        }
                    }
                    add->children.push_back(new_node);
                    if (!(new_node->is_self_closing)) {
                        add = new_node;
                    }
                }
            }

            else {
                add->value = v[i].xml_parsed;
            }
        }

        return error;
    }

    void print(Node* root_ptr,string * no_space) {
        string temp;

        *no_space += '<' + (root_ptr->name);
        if (root_ptr->attribute != "\0") {
            for (int i=0;i< (root_ptr->attribute).length();i++){
                if((root_ptr->attribute)[i] !=' '){
                    temp += (root_ptr->attribute)[i];
                }
            }
            *no_space += temp;
        }
        if (root_ptr->is_self_closing) {
            *no_space += '/';
        }
        *no_space += '>';
        if (root_ptr->value != "\0") {
            temp = "\0";
            for (int i=0;i< (root_ptr->value).length();i++){
                if((root_ptr->value)[i] !=' '){
                    temp += (root_ptr->value)[i];
                }
            }
            *no_space += temp;
        }
        for (int i = 0; i < (root_ptr->children.size()); i++) {
            print(root_ptr->children[i],no_space);
        }
        if (!(root_ptr->is_self_closing)) {
            *no_space += "</" + (root_ptr->name) + '>';
        }

    }

    Node* get_root() {
        return root;
    }

    void format(Node* root, int count)
        {
            for (int i = 0; i < count; i++)
            {
                cout << "   ";
            }
            cout << "<" << root->name;
            if (root->attribute.length() != 0)
            {
                cout << " " << root->attribute;
            }
            if (root->is_self_closing) {
                cout<< '/';
            }
            cout << ">";
            if (root->value == "" && !root->is_self_closing)
            {
                count++;
                cout << endl;
            }
            else
            {
                if (!root->is_self_closing) {
                    cout << root->value; cout << "</" << root->name << ">\n";
                }
                else {
                    cout << "\n";
                }
                return;
            }
            for (int i = 0; i < root->children.size(); i++)
            {
                    format(root->children[i], count);
            }
            count--;
            for (int i = 0; i < count; i++)
            {
                cout << "   ";
            }

            cout << "</" << root->name << ">";
            cout << endl;
    }
};


void MainWindow::parse_xml(vector<xml_parse> &xml , string line, int& line_number) {
    xml_parse temp;
    int new_i = 0;

    for (int i = 0; i < line.length(); i++) {
        if (line[i] == '<' && (line[i + 1] != '!' && line[i + 1] != '?')) {
            new_i = line.find('>', i);
            temp = { line.substr(i, new_i + 1 - i), line_number };
            xml.push_back(temp);
            i = new_i - 1;
        }
        else if (line[i] == '>' && i != line.length() - 1 && line[i + 1] != '<') {
            new_i = line.find('<', i);
            temp = { line.substr(i + 1, line.length() - i), line_number };
            for (int j = 0; j < temp.xml_parsed.length(); j++) {
                if (temp.xml_parsed[j] == ' ') {
                    temp.xml_parsed.erase(j, 1);
                    j--;
                }
            }
            if (new_i == -1 && !temp.xml_parsed.empty()) {
                xml.push_back(temp);
                i = line.length();
            }
            else {
                temp = { line.substr(i + 1, new_i - 1 - i), line_number };
                for (int j = 0; j < temp.xml_parsed.length(); j++) {
                    if (temp.xml_parsed[j] == ' ') {
                        temp.xml_parsed.erase(j, 1);
                        j--;
                    }
                }
                if (!temp.xml_parsed.empty()) {
                    xml.push_back(temp);
                }
                i = new_i - 1;
            }
        }
    }
    line_number++;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

