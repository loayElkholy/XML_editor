#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include<string>
#include<string.h>
#include<algorithm>
#include <QtWidgets>
#include <QTextStream>
#include <QFile>
#include <QFileDialog>

using namespace std;

typedef struct {
    string name;
    vector<pair<string, string>> attr;
}tag;

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

    tag get_tag_struct(string s1 ,string name)
       {
           tag t;
           string s = "<"+ s1 + " " + name;
           string tmp = "";
           for (int i = 1;; i++)
           {
               if (s[i] == ' ' || i == s.length() - 1)
               {
                   t.name = tmp;
                   break;
               }
               else
               {
                   tmp += s[i];
               }
           }
           int sp = -1, eq = -1;

           while (1)
           {
               if(sp==-1)
                   sp = s.find(' ', sp + 1)-1;
               else
                   sp = s.find("\" ", sp + 1);
               eq = s.find('=', eq + 1);
               if (sp == string::npos)return t;
               pair<string, string> p;
               p.first = s.substr(sp + 2, eq - 1 - sp);
               p.second = s.substr(eq + 1, s.find('\"', eq + 2) - eq);
               t.attr.push_back(p);
           }

       }
       void find(Node * r,int ind ,vector<int> &index)
       {
           index = {};
           index.push_back(ind);
           for (int i = ind+1; i < r->children.size(); i++)
           {
               if (r->children[i]->name == r->children[ind]->name)
               {
                   index.push_back(i);
                   r->children[i]->found = true;
               }
           }
       }
       void ind()
       {
           for (int i = 0; i < depth; i++)cout << "   ";
       }
       void print_attr(vector<pair<string, string>>s)
       {
           for (int i = 0; i <s.size(); i++)
           {
               if (i) { cout << ",\n"; }
               ind(); cout<<"\"@"<<s[i].first <<"\": "<<s[i].second;
           }
       }
       void Pjson(Node* r ,bool flag=true)
       {
           tag t = get_tag_struct(r->name ,r->attribute);
           if (r->children.size() == 0)
           {
               if(flag){ind(); cout << "\"" << t.name << "\": ";}
               if(t.attr[0].first != ""){
                   if (!flag)ind();
                   cout << "{" << endl;
                   depth++;
                   print_attr(t.attr);
                   cout << ",\n";
                   if (r->value != "") { ind(); cout << "\"#text" << ": " << '"' << r->value << "\"\n"; }
                   depth--; ind(); cout << "}";
               }
               else
               {
                  cout << '"' << r->value << '"';
               }
               return;
           }
           else
           {
               vector<int>index;
               if (r->children.size() > 1)
               {
                   if (flag) { ind(); cout << '"' << t.name << "\": {\n"; depth++; }
                   if (t.attr[0].first != "") {
                       print_attr(t.attr);
                       cout << ",\n";
                   }
                   for (int i = 0; i < r->children.size(); i++)
                   {
                       if (r->children[i]->found)
                       {
                           continue;
                       }
                       if (i) {cout << ",\n"; }
                       find(r, i, index);
                       if (index.size() > 1)
                       {
                           Node* ch = r->children[i];
                           ind(); cout << "\"" << ch->name << "\": [\n"; depth++;
                           if (ch->children.size()==0 && ch->attribute=="")
                           {
                               for (int x = 0; x < index.size(); x++)
                               {
                                   if (x) { cout << ",\n"; }
                                   ind(); cout << r->children[index[x]]->value;
                               }
                           }
                           else {
                                   for (int x = 0; x < index.size(); x++)
                                   {
                                       if (x) { cout << ",\n"; }
                                       if (r->children[index[x]]->children.size()) {
                                           ind(); cout << "{\n"; depth++;
                                           Pjson(r->children[index[x]], false);
                                           depth--;  cout << "\n"; ind(); cout << "}";
                                       }
                                       else
                                       {
                                           Pjson(r->children[index[x]], false);
                                       }
                                   }

                           }
                           depth--;  cout << "\n"; ind(); cout << "]";
                       }
                       else
                       {
                           Pjson(r->children[i]);
                       }
                   }
                   if (flag) { depth--;  cout << "\n"; ind(); cout << "}"; }
               }
               else
               {
                   ind(); cout<< '"' << t.name << '"' << ": {\n"; depth++;
                   if (t.attr[0].first!="") {
                       print_attr(t.attr);
                       cout << ",\n";
                   }
                   for (int i = 0; i < r->children.size(); i++)
                   {
                       if (i) { ind(); cout << ",\n"; }
                       Pjson(r->children[i]);
                   }
                   depth--;  cout << "\n"; ind(); cout << "}";
               }

           }

       }
public:
       void json()
       {
           cout << '{' << endl;
           depth++;
           Pjson(root);
           cout << "\n}";
       }
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
                    if (temp.xml_parsed[j] == ' ') {
                        if (j == 0) {
                            temp.xml_parsed.erase(j, 1);
                            j--;
                        }
                        else if (j == temp.xml_parsed.length() - 1) {
                            temp.xml_parsed.erase(j, 1);
                            j = temp.xml_parsed.length() - 2;
                        }
                    }
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
                        if (j == 0) {
                            temp.xml_parsed.erase(j, 1);
                            j--;
                        }
                        else if (j == temp.xml_parsed.length() - 1) {
                            temp.xml_parsed.erase(j, 1);
                            j = temp.xml_parsed.length() - 2;
                        }
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

vector<int> compress_file(map<string, int> &table, string s1, int &mul_char_code) {
    vector<int> encoded_code;
    string current = "", next = "";
    current += s1[0];
    for (int i = 0; i < s1.length(); i++) {
        if (i != s1.length() - 1) {
            next += s1[i + 1];
        }
        if (table.find(current + next) != table.end()) {
            current = current + next;
        }
        else {
            encoded_code.push_back(table[current]);
            table[current + next] = mul_char_code;
            mul_char_code++;
            current = next;
        }
        next = "";
    }
    encoded_code.push_back(table[current]);
    return encoded_code;
}

void decode(map<int, string> table_decode, vector<int> encoded_code) {
    string s;
    for (int i = 0; i < encoded_code.size(); i++) {
        s += table_decode[encoded_code[i]];
    }
    cout << s;
}

//********************************************** should be placed in button of compressing *********************************
//int mul_char_code = 256;
//vector<int> code;
//vector<int> total_code;
//map<string, int> table;
//for (int i = 0; i <= 255; i++) {
//    string character = "";
//    character += char(i);
//    table[character] = i;
//}

//map<int, string> table_decode;
//map<string, int>::iterator itr;
//for (itr = table.begin(); itr != table.end(); itr++) {
//    table_decode[itr->second] = itr->first;
//}
//****************************************************************************************************************************

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget *widget= new QWidget() ;
    QHBoxLayout *main_layout =new QHBoxLayout();
    QVBoxLayout *vertical_layout =new QVBoxLayout();

    pushButton =new QPushButton();
    pushButton->setText("open file");

    textBrowser =new QTextBrowser();

    vertical_layout->addWidget(textBrowser);
    vertical_layout->addWidget(pushButton);

    connect_fun();
    main_layout->addLayout(vertical_layout);
    widget->setLayout(main_layout);
    setCentralWidget(widget);

}
void MainWindow::connect_fun()
{
    connect(pushButton,SIGNAL(clicked()),this,SLOT(on_push_button_clicked()));
}
void MainWindow::on_push_button_clicked()
{
    QString filter = "All Files (*.*) ;; Text Files (*.txt) ;; XML Files (*.xml)";
    QString file_name = QFileDialog::getOpenFileName(this,"choose file","D:\\loay\\College\\3rd year\\2nd term\\datastructure and algorithm",filter);

    QFile file(file_name);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&file);
        QString text;
        while (!in.atEnd()) {
            QString line = in.readLine();
            text.append(line+"\n");
            string line_string = line.toStdString();
            qDebug() << QString::fromStdString(line_string);
        }

        textBrowser->setText(text);
    file.close();
}
MainWindow::~MainWindow()
{
    delete ui;
}

























