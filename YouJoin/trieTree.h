//支持扩展字符集的trie树实现
//支持快速字符串查找、字符串前缀匹配

#ifndef CHTRIETREE_H
#define CHTRIETREE_H
#include<vector>
#include<string>
using std::vector;
using std::string;

inline int hashGb2312(const char* ch);
inline int hashGbk(const char* ch);

struct Node{
	vector<char*> mKeyWordVec; //关键字向量(递增顺序,便于以后二分查找)
	vector<Node*> mLinkVec; //指向子检索树的指针向量
	int amount = 0;

};

int bSearch(const vector<char*> vec, const char* word);			//二分查找
int word_compare(const char* chinese1, const char*chinese2);			//比较两个词的位置大小，方便二分查找，且处理文字是GBK还是GB-2312
int insertToVec(vector<char*>& vec, char *chinese);			//	找插入的位置
int specBSearch(const vector<char*>& vec, char* chinese);			//用二分法找具体的插入位置

class chTrieTree{
private:
	Node* mRoot;
	//vector<char> mapChar;
public:
	chTrieTree(Node* node = NULL){
		mRoot = node;
	}

	Node* getChTrieTree()const{
		return mRoot;
	}
	chTrieTree& insertChinese(const char* str);			//插入汉字集
	chTrieTree& delChinese(const char* str);			//删除汉字集
	bool findChinese(const char*str);				//判断是否存在
	chTrieTree findCh(const char* ch);
	vector<string> getPrefixWords(char* key);			//返回前缀是key的所有词的集合
	void getPrefixHelp(Node* node, vector<string>& vec, string str);
	Node* findLastNode(Node* node, char* key);// 返回最后一个字的节点
};


#endif