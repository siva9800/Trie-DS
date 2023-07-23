#include <bits/stdc++.h>
using namespace std;
struct Node{
    
    Node* links[52];
    bool flag=false;
    
    bool contains(char c){
        if(c>=97) return links[c-'a'+26]!=NULL;
        return links[c-'A']!=NULL;
    }
    void put(char c,Node* node){
        if(c>=97) links[c-'a'+26]=node;
        else links[c-'A']=node;
    }
    Node* getNext(char c){
        if(c>=97) return links[c-'a'+26];
        return links[c-'A'];
    }
    void setEnd(){
        flag=true;
    }
    bool isEnd(){
        return flag;
    }
    
};

class Solution {
public:
    
    Node* root= new Node();
    
    void insert(string word){
        Node* temp=root;
        for(int i=0; i<word.size(); i++){
            
            if(!temp->contains(word[i])){
                temp->put(word[i],new Node());
            }
            temp=temp->getNext(word[i]);
        }
        temp->setEnd();
    }
    
    unordered_set<string> resultset;
    int rows[8]={1,-1,0,0,1,1,-1,-1};
    int cols[8]={0,0,-1,1,1,-1,-1,1};
    
    bool isValid(int r, int c, int n, int m){
        return r>=0 && c>=0 && r<n && c<m;
    }
    
    void dfs(int r, int c,int n,int m,Node* node,vector<vector<char>> & board,string & currword,vector<vector<int>> &vis){
            
            if(node->isEnd()){
                resultset.insert(currword);
            }
            
            for(int i=0; i<8; i++){
                int dr=rows[i]+r;
                int dc=cols[i]+c;
                if(isValid(dr,dc,n,m) && !vis[dr][dc] && node->contains(board[dr][dc])){
                    vis[dr][dc]=1;
                    currword+=board[dr][dc];
                    dfs(dr,dc,n,m,node->getNext(board[dr][dc]),board,currword,vis);
                    vis[dr][dc]=0;
                    currword.pop_back();
                }
        }
        
    }
	vector<string> wordBoggle(vector<vector<char> >& board, vector<string>& dictionary) {
	    
	    int n=board.size(),m=board[0].size();
	    vector<vector<int>> vis(n,vector<int>(m,0));
	    string currword;
	    
	    for(string s: dictionary){
	        insert(s);
	    }
	    
	    for(int i=0; i<n; i++){
	        for(int j=0; j<m; j++){
	            if(root->contains(board[i][j])){
	                vis[i][j]=1;
	                currword+=board[i][j];
	                dfs(i,j,n,m,root->getNext(board[i][j]),board,currword,vis);
	                vis[i][j]=0;
	                currword.pop_back();
	            }
	        }
	    }
	    vector<string>result(resultset.begin(),resultset.end());
	    return result;
	}
};



int main() {
    int t;
    cin >> t;
    while (t--) {
        int N;
        cin >> N;
        vector<string> dictionary;
        for (int i = 0; i < N; ++i) {
            string s;
            cin >> s;
            dictionary.push_back(s);
        }
        
        int R, C;
        cin >> R >> C;
        vector<vector<char> > board(R);
        for (int i = 0; i < R; i++) {
            board[i].resize(C);
            for (int j = 0; j < C; j++) cin >> board[i][j];
        }
        Solution obj;
        vector<string> output = obj.wordBoggle(board, dictionary);
        if (output.size() == 0)
            cout << "-1";
        else {
            sort(output.begin(), output.end());
            for (int i = 0; i < output.size(); i++) cout << output[i] << " ";
        }
        cout << endl;
    }
}
