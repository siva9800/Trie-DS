//trie ds is used for string searching problems here we have a ds called node which have 2 parts one is like linked list a referense to other node or link and other part is bool flag which tells we have complete  word
//or not 

struct Node{
    Node *links[26]; //is we have upper case just do 52 and do if c>=97 links[c-'a'+26]
    bool  flag=false;

    bool contains(char c){
        return links[c-'a']!=NULL;
    }
    void put(char c,Node* node){
        links[c-'a']=node;
    }
    Node*  getNext(char c){
        return links[c-'a'];
    }
    void set_end(){
        flag=true;
    }
    bool is_end(){
        return flag;
    }
};

class Trie {
private: Node* root;
public:
    Trie() {
        root= new Node();
    }
    
    void insert(string word) {
        Node* temp_node=root;
        for(int i=0; i<word.size(); i++){
            if(!temp_node->contains(word[i])){
                temp_node->put(word[i],new Node());
            }
            temp_node=temp_node->getNext(word[i]);
        }
        temp_node->set_end();
    }
    
    bool search(string word) {
        Node* temp_node=root;
        for(int i=0; i<word.size(); i++){
            if(!temp_node->contains(word[i])) return false;
            temp_node=temp_node->getNext(word[i]);
        }
        return temp_node->is_end();
    }
    
    bool startsWith(string prefix) {
        Node* temp_node=root;
        for(int i=0; i<prefix.size();i++){
            if(!temp_node->contains(prefix[i])) return false;
            temp_node=temp_node->getNext(prefix[i]);
        }
        return true;
    }
};
