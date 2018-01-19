

int __stdcall CompressionBound(int s);//worst case compression where the size grows! This can happen if you compress something that is already compressed
int __stdcall Compress(const char* source, char* dest, int inputSize, int dest_size);
int __stdcall Decompress(const char* source, char* dest, int compressedSize, int maxDecompressedSize);
int __stdcall Decompressed_Size(const char* source);
int __stdcall CompressFile(LPCTSTR SrcFilePath,LPCTSTR DesFilePath);
int __stdcall DecompressFile(LPCTSTR SrcFilePath,LPCTSTR DesFilePath);