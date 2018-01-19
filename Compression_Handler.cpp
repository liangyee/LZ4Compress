#include "Compression_Handler.h"
#include "lz4.h"
#include "lz4hc.h"

int __stdcall CompressionBound(int s) {
	return LZ4_COMPRESSBOUND(s);
}
//assume dest is big enough to hold the compressed data
int __stdcall Compress(const char* source, char* dest, int inputSize, int dest_size){
	if (inputSize < 1024){
		memcpy(dest, source, inputSize);
		return -1;//no compression occurred too small to waste time trying
	}
	int* dstsize = (int*)dest;
	int compressedsize = LZ4_compress(source, dest + sizeof(int), inputSize);
	*dstsize = inputSize;
	return compressedsize + sizeof(int);//return new size of compressed data
}
int __stdcall Decompress(const char* source, char* dest, int compressedSize, int maxDecompressedSize){
	return LZ4_decompress_safe(source + sizeof(int), dest, compressedSize - sizeof(int), maxDecompressedSize);
}

int __stdcall Decompressed_Size(const char* source) {
	return *((int*)source); 
}




int __stdcall CompressFile(LPCTSTR SrcFilePath,LPCTSTR DesFilePath)
{
	CFile file;
	file.Open(SrcFilePath,CFile::modeRead);
	int FileSize=file.GetLength();
	LPBYTE pFileBuffer=new BYTE[FileSize];
	file.Read(pFileBuffer,FileSize);
	file.Close();
	LPBYTE pDesBuffer=new BYTE[FileSize];
	int DesSize=FileSize;
	DesSize=Compress((CHAR*)pFileBuffer,(CHAR*)pDesBuffer,DesSize,DesSize);
	delete [] pFileBuffer;
	file.Open(DesFilePath,CFile::modeWrite|CFile::modeCreate);
	file.Write(pDesBuffer,DesSize);
	file.Close();
	delete [] pDesBuffer;
	return 0;
}

int __stdcall DecompressFile(LPCTSTR SrcFilePath,LPCTSTR DesFilePath)
{
	CFile file;
	file.Open(SrcFilePath,CFile::modeRead);
	int FileSize=file.GetLength();
	LPBYTE pFileBuffer=new BYTE[FileSize];
	file.Read(pFileBuffer,FileSize);
	file.Close();
	//int DesSize=*((int*)pFileBuffer);
	int DesSize = Decompressed_Size((const char*)pFileBuffer);
	LPBYTE pDesBuffer=new BYTE[DesSize];
	DesSize=Decompress((CHAR*)pFileBuffer,(CHAR*)pDesBuffer,FileSize,DesSize);
	delete [] pFileBuffer;
	file.Open(DesFilePath,CFile::modeWrite|CFile::modeCreate);
	file.Write(pDesBuffer,DesSize);
	file.Close();
	delete [] pDesBuffer;
	return 0;
}

