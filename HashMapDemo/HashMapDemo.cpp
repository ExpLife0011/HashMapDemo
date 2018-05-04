
#include <string>
#include <map>
#include <utility> // make_pair
#include <stdio.h>
//////////////////////////////////////////////////////////////////////////
//http://partow.net/programming/hashfunctions/index.html

#define HashFun1 RSHash
#define HashFun2 JSHash
// hash �㷨һ
unsigned int RSHash(const char* str, unsigned int length)
{
	unsigned int b    = 378551;
	unsigned int a    = 63689;
	unsigned int hash = 0;
	unsigned int i    = 0;

	for (i = 0; i < length; ++str, ++i)
	{
		hash = hash * a + (*str);
		a    = a * b;
	}

	return hash;
}

// hash �㷨��
unsigned int JSHash(const char* str, unsigned int length)
{
	unsigned int hash = 1315423911;
	unsigned int i    = 0;

	for (i = 0; i < length; ++str, ++i)
	{
		hash ^= ((hash << 5) + (*str) + (hash >> 2));
	}

	return hash;
}

//////////////////////////////////////////////////////////////////////////

// �Ƴ��ַ���ĩβ�Ļ��з�
void RemoveLastInvalidValue(std::string &str, std::string &strValue);


int main(int agrc,char* agrv)
{
	std::map<unsigned int,std::string >  hashMap;

	FILE *pFile = fopen("./words.txt","rb");
	if (!pFile)
		return -1;
	std::string str;
	int nCount = 0;
	char szline[1000];  
	while(!feof(pFile))
	{
		fgets(szline,1000,pFile);  
		str = szline;
		printf("%s",str.c_str());

		std::string strValue;
		RemoveLastInvalidValue(str,strValue);
		if (strValue.empty())
			continue;
		unsigned int Hash = HashFun1(strValue.c_str(),strValue.size());
		std::pair< std::map< unsigned int,std::string >::iterator,bool > ret = hashMap.insert(std::make_pair(Hash,strValue));
		if (!ret.second)
		{
			if (str.find(hashMap[Hash]))
			{
				printf("��ֵ��ͬ��ʹ�õڶ���hash�㷨\n");
				Hash = HashFun2(strValue.c_str(),strValue.size());
				std::pair< std::map< unsigned int,std::string >::iterator,bool > ret = hashMap.insert(std::make_pair(Hash,strValue));
				// ����hash�㷨ͬʱ��ײ�ĸ���̫С�ˣ�����Ͳ��ж��Ƿ����ʧ����
			}
		}
		nCount ++;
	}

	printf("\n///////////// \n");
	printf("\n����ȡ��Ч����%d��  HashMap��С%d\n",nCount,hashMap.size());

//////////////////////////////////////////////////////////////////////////
///////////// ���Ҳ���

	std::string strFind = "����";
	unsigned int findHash = HashFun1(strFind.c_str(),strFind.size());

	std::map<unsigned int,std::string>::iterator it;
	it = hashMap.find(findHash);
	if (it!=hashMap.end())
	{
		printf("�ҵ��� %s\n",strFind.c_str());
	}
	else
	{
		printf("δ���ҵ�����\n");
	}
///////////// �����ݲ��Ҳ�����ʱ�򣬾͵���hash2��������һ�Σ����±���һ�Σ������˷ǳ���ļ�����
//// �ṩ�Ż�������˼·������ͻ��hasn���浽�������ͻ��Ĵ�С�϶��ǳ�С�����Ա�֤Ч��
	findHash = HashFun2(strFind.c_str(),strFind.size());
	it = hashMap.find(findHash);
	if (it!=hashMap.end())
	{
		printf("�ҵ��� %s\n",strFind.c_str());
	}
	else
	{
		printf("δ���ҵ�����\n");
	}

	return 0;
} 

void RemoveLastInvalidValue(std::string &str, std::string &strValue)
{
	if (str.size() <1)  // �����������
		return;
	int nRemove = 0;
	for (int i=str.size()-1;i>=0;i--)
	{
		if (str[i] == '\r' || str[i]=='\n' || str[i]=='\0')
		{
			nRemove ++;
		}
		else
			break;
	}
	if(nRemove>=str.size())
		nRemove = 0;
	strValue = str.substr(0,str.size() - nRemove);
}


