// ConsoleApplication2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "dllloader.h"


int main()
{
	FILE * pFile;
	size_t lSize;
	size_t result;
	/* 使用智能指针管理内存 */
	unique_ptr<MEM_LoadDllAPI> hDLL(GetMemLoadDllApp());
	unique_ptr<char> buffer;
	/* 若要一个byte不漏地读入整个文件，只能采用二进制方式打开 */
	pFile = fopen("dlltest.dll", "rb");
	if (pFile == NULL)
	{
		fputs("File error", stderr);
		goto nPause;
	}
	/* 获取文件大小 */
	fseek(pFile, 0, SEEK_END);
	lSize = ftell(pFile);
	rewind(pFile);
	/* 分配内存存储整个文件 */
	buffer.reset(new char[(sizeof(char)*lSize)]);
	if (buffer == NULL)
	{
		fputs("Memory error", stderr);
		goto nPause;
	}
	/* 将文件拷贝到buffer中 */
	result = fread(&*buffer, 1, lSize, pFile);
	if (result != lSize)
	{
		fputs("Reading error", stderr);
		goto nPause;
	}
	/* 读取成功，关闭文件。 */
	fclose(pFile);
	/* 装载内存当中的DLL文件 */
	hDLL->MemLoadLibrary(&*buffer, lSize);
	hDLL->MemFreeLibrary();
nPause:
	/* 成功或者失败最终都会到这一步 */
	system("pause");
    return 0;
}

