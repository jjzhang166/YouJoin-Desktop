//֧����չ�ַ�����trie��ʵ��
//֧�ֿ����ַ������ҡ��ַ���ǰ׺ƥ��

#ifndef CHTRIETREE_H
#define CHTRIETREE_H
#include<vector>
#include<string>
using std::vector;
using std::string;

inline int hashGb2312(const char* ch);
inline int hashGbk(const char* ch);

struct Node{
	vector<char*> mKeyWordVec; //�ؼ�������(����˳��,�����Ժ���ֲ���)
	vector<Node*> mLinkVec; //ָ���Ӽ�������ָ������
	int amount = 0;

};

int bSearch(const vector<char*> vec, const char* word);			//���ֲ���
int word_compare(const char* chinese1, const char*chinese2);			//�Ƚ������ʵ�λ�ô�С��������ֲ��ң��Ҵ���������GBK����GB-2312
int insertToVec(vector<char*>& vec, char *chinese);			//	�Ҳ����λ��
int specBSearch(const vector<char*>& vec, char* chinese);			//�ö��ַ��Ҿ���Ĳ���λ��

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
	chTrieTree& insertChinese(const char* str);			//���뺺�ּ�
	chTrieTree& delChinese(const char* str);			//ɾ�����ּ�
	bool findChinese(const char*str);				//�ж��Ƿ����
	chTrieTree findCh(const char* ch);
	vector<string> getPrefixWords(char* key);			//����ǰ׺��key�����дʵļ���
	void getPrefixHelp(Node* node, vector<string>& vec, string str);
	Node* findLastNode(Node* node, char* key);// �������һ���ֵĽڵ�
};


#endif