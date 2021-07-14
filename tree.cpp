#include "tree.h"
#include "fstream"
void Tree::json()
{
    cout << '{' << endl;
    depth++;
    Pjson(root,true);
    cout << "\n}";
}
vector<int> Tree::vector_to_tree(vector<xml_parse> v) {
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

void Tree::print(Node* root_ptr,string * no_space) {
 string temp;

 *no_space += '<' + (root_ptr->name);
 if (root_ptr->attribute != "\0") {
   *no_space += root_ptr->attribute;
 }
 if (root_ptr->is_self_closing) {
     *no_space += '/';
 }
 *no_space += '>';
 if (root_ptr->value != "\0") {
  *no_space += root_ptr->value;
 }
 for (int i = 0; i < (root_ptr->children.size()); i++) {
     print(root_ptr->children[i],no_space);
 }
 if (!(root_ptr->is_self_closing)) {
     *no_space += "</" + (root_ptr->name) + '>';
 }

}

void Tree::minify(string no_space) {
    print(root,&no_space);
}

void Tree::format_public()
{
    format(root,0);
}

void Tree::format(Node* root, int count)
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


tag Tree::get_tag_struct(string s1 ,string name)
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
void Tree::find(Node * r,int ind ,vector<int> &index)
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
void Tree::ind()
{
   for (int i = 0; i < depth; i++)cout << "   ";
}
void Tree::print_attr(vector<pair<string, string>>s)
{
   for (int i = 0; i <s.size(); i++)
   {
       if (i) { cout << ",\n"; }
       ind(); cout<<"\"@"<<s[i].first <<"\": "<<s[i].second;
   }
}

void Tree::Pjson(Node* r ,bool flag=true)
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
