#include "trieTree.h"

chTrieTree& chTrieTree::insertChinese(const char*str){
	char *ch = new char[3];
	ch[0] = str[0];
	if ((unsigned)ch[0] <= 127) {
		ch[1] = '\0';
	}
	else{
		ch[1] = str[1];
		ch[2] = '\0';
	}

	//���Ϊ�գ������ڣ�
	if (mRoot == NULL){
		mRoot = new Node();
		mRoot->mKeyWordVec.push_back(ch);
		mRoot->mLinkVec.push_back(NULL);
		const char* s;
		if ((unsigned)ch[0] <= 127) s = str + 1;
		else s = str + 2;
		if (*s != '\0'){
			Node* node = new Node();
			chTrieTree childTree(node);
			mRoot->mLinkVec[0] = node;

			childTree.insertChinese(s);
		}
		else{
			Node* node = new Node();
			node->mKeyWordVec.push_back("**");
			node->mLinkVec.push_back(NULL);
			mRoot->mLinkVec[0] = node;
		}
	}
	//������ڣ���mRoot
	else if (mRoot != NULL){
		int index = bSearch(mRoot->mKeyWordVec, ch);
		//��mRoot���Ҹ��ִ���
		if (index != -1){
			mRoot->amount++;
			const char*s;
			if ((unsigned)ch[0] <= 127) s = str + 1;
			else s = str + 2;
			if (*s != '\0'){
				Node* node = mRoot->mLinkVec[index];
				chTrieTree childTree(node);
				childTree.insertChinese(s);
			}
			else{
				Node* mroot = mRoot->mLinkVec[index];
				if (mroot == NULL){
					Node* n = new Node();
					n->mKeyWordVec.push_back("**");
					n->mLinkVec.push_back(NULL);
					mroot = n;
				}
				else{
					int insertEnd = insertToVec(mroot->mKeyWordVec, "**");
					if (insertEnd >= 0)
						mroot->mLinkVec.insert(mroot->mLinkVec.begin() + insertEnd, NULL);
				}
			}
		}
		//��mRoot�������ֲ�����
		else{
			int insertPoint = insertToVec(mRoot->mKeyWordVec, ch);
			mRoot->mLinkVec.insert(mRoot->mLinkVec.begin() + insertPoint, NULL);
			const char*s;
			if ((unsigned)ch[0] <= 127) s = str + 1;
			else s = str + 2;
			if (*s != '\0'){
				Node* n = new Node();
				chTrieTree childTree(n);
				mRoot->mLinkVec[insertPoint] = n;
				childTree.insertChinese(s);
			}
			else{
				Node* node = new Node();
				node->mKeyWordVec.push_back("**");
				node->mLinkVec.push_back(NULL);
				mRoot->mLinkVec[insertPoint] = node;
			}
		}
	}
	return *this;
}


bool chTrieTree::findChinese(const char*str){
	char *ch = new char[3];
	ch[0] = str[0];
	if ((unsigned)ch[0] <= 127) {
		ch[1] = '\0';
	}
	else{
		ch[1] = str[1];
		ch[2] = '\0';
	}
	int index = bSearch(mRoot->mKeyWordVec, ch);
	//��һ���ֲ�����
	if (index == -1){
		return false;
	}
	//��һ���ִ��ڣ�������һ���ֵĲ���
	else{
		const char* s;
		if ((unsigned)ch[0] <= 127) s = str + 1;
		else s = str + 2;
		if (*s != '\0'){
			if (mRoot->mLinkVec[index] == NULL){
				return false;
			}
			chTrieTree childTree(mRoot->mLinkVec[index]);
			return childTree.findChinese(s);
		}
		else{
			Node* node = mRoot->mLinkVec[index];
			if (bSearch(node->mKeyWordVec, "**") != -1){
				return true;
			}
			else{
				return false;
			}
		}
	}
	return true;
}


chTrieTree chTrieTree::findCh(const char*str){
	int index = bSearch(mRoot->mKeyWordVec, str);
	//��һ���ֲ�����
	if (index == -1){
		return chTrieTree();
	}
	//�ݹ�����������Ƿ񶼴��ڣ�
	chTrieTree childTree(mRoot->mLinkVec[index]);
	return childTree;
}

chTrieTree& chTrieTree::delChinese(const char* str){
	//���mRoot������
	if (mRoot == NULL){
		return *this;
	}
	//���δ�ҵ��ôʼ�
	if (findChinese(str) == false){
		return *this;
	}
	size_t lenth = strlen(str);
	//��countVec[]��ôʼ�������node�ķ�֧����1��ʾ>1;0��ʾ1��
	vector<int> countVec(lenth / 2);
	Node* temp1 = mRoot;
	Node* temp2;
	char ch[3];
	for (size_t i = 0; i < lenth; i += 2){
		ch[0] = str[i];
		ch[1] = str[i + 1];
		ch[2] = '\0';
		int index = bSearch(temp1->mKeyWordVec, ch);
		temp2 = temp1->mLinkVec[index];
		if (temp2->mKeyWordVec.size()>1){
			countVec[i / 2] = 1;
		}
		else{
			countVec[i / 2] = 0;
		}
		temp1 = temp2;
	}
	//��pos��ʾ�ôʼ����������Ǹ�1��λ�ã������һ����֧��������ɾ��
	int pos = -1;
	for (int i = int(countVec.size() - 1); i >= 0; --i){
		if (countVec[i] == 1){
			pos = i;
			break;
		}
	}
	temp1 = mRoot;
	const char* s = str;
	//temp1�������£�ֱ���ҵ����һ����֧���Ǹ��ڵ�
	for (int i = 0; i <= pos; ++i){
		ch[0] = *s;
		ch[1] = *(s + 1);
		ch[2] = '\0';
		s += 2;
		int index = bSearch(temp1->mKeyWordVec, ch);
		temp1 = temp1->mLinkVec[index];
	}
	if (*s == '\0'){
		int index = bSearch(temp1->mKeyWordVec, "**");
		temp1->mKeyWordVec.erase(temp1->mKeyWordVec.begin() + index);
		temp1->mLinkVec.erase(temp1->mLinkVec.begin() + index);
		return *this;
	}
	while (*s != '\0'){
		ch[0] = *s;
		ch[1] = *(s + 1);
		ch[2] = '\0';
		int index = bSearch(temp1->mKeyWordVec, ch);
		temp2 = temp1->mLinkVec[index];
		temp1->mKeyWordVec.erase(temp1->mKeyWordVec.begin() + index);
		temp1->mLinkVec.erase(temp1->mLinkVec.begin() + index);
		temp1 = temp2;
		s += 2;
	}
	if (*s == '\0'){
		delete temp1;
		return *this;
	}
	return *this;
}


Node* chTrieTree::findLastNode(Node* node, char* key){
	//if (!findChinese(key)) return NULL;;
	char ch[3];
	ch[0] = key[0];
	if ((unsigned)ch[0] <= 127) ch[1] = '\0';
	else{
		ch[1] = key[1];
		ch[2] = '\0';
	}
	int index = bSearch(node->mKeyWordVec, ch);
	if (index == -1) return NULL;
	char* s;
	if ((unsigned)ch[0] <= 127) s = key + 1;
	else s = key + 2;
	while (*s != '\0'){
		index = bSearch(node->mKeyWordVec, ch);
		node = node->mLinkVec[index];
		return findLastNode(node, s);
	}
	return node->mLinkVec[index];
}

vector<string> chTrieTree::getPrefixWords(char* key){
	Node* p = mRoot;
	Node* node = findLastNode(p, key);
	//int temp = node->mKeyWordVec.size();
	//int temp = getNodeAmount(node);
	vector<string> vec;
	getPrefixHelp(node, vec, key);
	return vec;
}
void chTrieTree::getPrefixHelp(Node* node, vector<string>& vec, string key){
	/*
	string str = key;
	int R = node->amount;
	Node* nodeTemp = node;
	if (node->mKeyWordVec[0]== "**") {
	vec.push_back(str);
	R--;
	}
	//if (R == 0) return;
	for (int i = 0; i <= R;i++){
	str = key;
	nodeTemp = node->mLinkVec[i];
	if (nodeTemp->mLinkVec[i] != NULL){

	str += nodeTemp->mKeyWordVec[i];
	//nodeTemp = nodeTemp->mLinkVec[i];
	int temp = nodeTemp->mKeyWordVec.size();

	//int temp = getNodeAmount(nodeTemp);
	getPrefixHelp(nodeTemp, vec, str, temp);
	}
	}
	*/
	if (node == NULL) return;
	int number = node->mKeyWordVec.size();
	for (int i = 0; i < number; i++){
		if (string(node->mKeyWordVec[i]) == string("**")){
			vec.push_back(key);
		}
		else{
			string tempKey = key;
			key += node->mKeyWordVec[i];
			//node = node->mLinkVec[i];
			getPrefixHelp(node->mLinkVec[i], vec, key);
			key = tempKey;
		}
	}

}

//���ֲ��ҹؼ��֣����ҵ��������±ꣻ��δ�ҵ�������-1��
int bSearch(const vector<char*> vec, const char* word){
	int low = 0;
	int high = int(vec.size() - 1);
	while (low <= high){
		int mid = (low + high) / 2;
		if (word_compare(vec[mid], word) == 0){
			return mid;
		}
		else if (word_compare(vec[mid], word) > 0){
			low = mid + 1;
		}
		else if (word_compare(vec[mid], word)<0){
			high = mid - 1;
		}
	}
	return -1;
}

// �ж�����������ʲô���룬�����ر������ֵĴ�С���������ڶ��ֲ���
int word_compare(const char* chinese1, const char*chinese2){
	size_t lenth1 = strlen(chinese1);
	size_t lenth2 = strlen(chinese2);
	int index1;
	int index2;
	size_t i;
	size_t indexMin = lenth1 < lenth2 ? lenth1 : lenth2;
	for (i = 0; i < indexMin; i += 2){
		char ch1[3];
		ch1[0] = chinese1[i];
		ch1[1] = chinese1[i + 1];
		ch1[2] = '\0';
		char ch2[3];
		ch2[0] = chinese2[i];
		ch2[1] = chinese2[i + 1];
		ch2[2] = '\0';
		index1 = hashGb2312(ch1);
		index2 = hashGb2312(ch2);
		if (index1 >= 0 && index2 >= 0){
			if (index1 > index2){
				return -1;
			}
			else if (index1<index2){
				return 1;
			}
		}
		else if (index1<0 && index2 >= 0){
			return 1;
		}
		else if (index2 >= 0 && index2 < 0){
			return -1;
		}
		else{
			index1 = hashGbk(ch1);
			index2 = hashGbk(ch2);
			if (index1 < index2){
				return -1;
			}
			else if (index1>index2){
				return 1;
			}
		}
	}
	if (i < lenth1){			//������ȣ���λ����ȣ��Ŷ϶��������
		return 1;
	}
	else if (i < lenth2){
		return -1;
	}
	return 0;
}
int insertToVec(vector<char*>& vec, char *chinese){
	int insertPoint = specBSearch(vec, chinese);
	if (insertPoint == -1){
		return -1;
	}
	vec.insert(vec.begin() + insertPoint, chinese);
	return insertPoint;
}
int specBSearch(const vector<char*>& vec, char* chinese){
	int low = 0;
	int high = int(vec.size() - 1);
	int insertPoint = 0;
	while (low <= high){
		int mid = (low + high) / 2;
		if (word_compare(vec[mid], chinese) == 0){
			return -1;
		}
		else if (word_compare(vec[mid], chinese) < 0){
			high = mid - 1;
		}
		else{
			low = mid + 1;
			insertPoint = low;
		}
	}
	return insertPoint;
}

inline int hashGb2312(const char* ch)
{
	//�ж��ǲ����ַ�
	if ((unsigned)ch[0] <= 127) return ch[0];
	//�����ǲ���gb2312����
	if (((ch[0] + 256) % 256 - 0xA0 < 16) || ((ch[0] + 256) % 256 - 0xA0 > 87))
		//gb2312���ֱ����λ�ӵ�16������87��
	{
		return -1;
	}
	if (((ch[1] + 256) % 256 - 0xA0 < 1) || ((ch[1] + 256) % 256 - 0xA0 > 94))
		//gb2312���ֱ����λ��1��94
	{
		return -1;
	}
	/*
	if ((ch[0] + 256) % 256 - 0xA0 == 3){
	int sectionIndex = (ch[0] + 256) % 256 - 0xA0 - 3;
	int locationIndex = (ch[1] + 256) % 256 - 0xA0 - 1;
	int index = sectionIndex * 94 + locationIndex;
	return index;
	}
	*/
	int sectionIndex = (ch[0] + 256) % 256 - 0xA0 - 16;
	//����(����Ϊ0),��16��Ϊgb2312ǰ15��û�ã��������Ŵӵ�16����ʼ
	int locationIndex = (ch[1] + 256) % 256 - 0xA0 - 1;
	//λ��(����Ϊ0),��1��Ϊgb2312λ�Ŵ�1��ʼ��ϣ����0��ʼ���ʼ�1
	int index = sectionIndex * 94 + locationIndex;
	//*******gb2312ÿ��94���ַ��������֤hash�Ľ������λ����һһ��Ӧ��
	return index + 128;
}
inline int hashGbk(const char* ch)
{
	int highIndex = (ch[0] + 256) % 256 - 0x81;
	int lowIndex;
	if ((ch[1] + 256) % 256 > 0x7f)
	{
		lowIndex = (ch[1] + 256) % 256 - 0x40 - 1;
		//�ڶ��ֽڲ�����0x7f�����Եڶ��ֽڱ�0x7f����ٶ��1��������ֹhash�հ׿ռ���˷�
	}
	else
	{
		lowIndex = (ch[1] + 256) % 256 - 0x40;
	}
	int index = highIndex * 190 + lowIndex;
	return index + 128;
}

