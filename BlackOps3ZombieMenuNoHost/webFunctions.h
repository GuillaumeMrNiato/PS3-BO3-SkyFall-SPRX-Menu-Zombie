#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <cell/http.h>
#include <netex/net.h>
 
 
 
#define HTTP_POOL_SIZE      (64 * 1024)
#define HTTP_POOL_BUFFER 0x2110000            //change this to an address with a free size of 0x10000 bytes ! This one is for ghosts 1.14
static char r_buffer[0x6000];  //MAX is 0x6000
 
 
/*Some function remade due to them making the sprx freeze for some reasons, might fix eventually*/
 
void memCpy(void * destination, const void * source, size_t num){for(int i = 0; i < num; i++){ *((char*)destination+i) = *((char*)source+i); } }
void memFree(char* ptr, int len){       for(int i=0;i < len; i++) { *(char*)(ptr+i) = 0x00;}}
int strCmp(const char* str1, const char* str2)
{
        int diff = 0;
 
        if(*(str1) == 0x00 || *(str2) == 0x00) {return -1;}
 
     for(int i = 0; i < 0x600; i++)
     {
                 if(*(str1+i) == 0x00 || *(str2+i) == 0x00) {break;}
                 if(*(str1+i) != *(str2+i)) {diff++;}
     }
 
         return diff;
}
void SendRequest(char* url,  char* retBuffer, int bufMaxLen) //url = url to request ("http://www.google.com/")    | retBuffer = ptr where the answer will be written to  | bufMaxLen = Max length of the buffer
{
        if(bufMaxLen > 0x6000) {return;} //ERROR, bufMaxLen is TOO BIG
 
                size_t numBuf = 0;
                CellHttpClientId client = 0;
                CellHttpTransId trans = 0;
                CellHttpUri uri;
                int ret;
                bool has_cl = true;
                uint64_t length = 0;
                uint64_t recvd;
                size_t poolSize = 0;
                void *uriPool = NULL;
                        void *httpPool = NULL;
                        const char *serverName;
                        size_t localRecv = 0;
 
            serverName = url;  //set url
                        memFree(r_buffer, bufMaxLen);
 
                        sys_net_initialize_network(); //init network
 
                        httpPool = (void*)HTTP_POOL_BUFFER; //address to: 0x10000 free bytes
                        if (httpPool == NULL) { ret = -1; goto end; }
 
                        ret = cellHttpInit(httpPool, HTTP_POOL_SIZE);
                        if (ret < 0) { goto end; }
       
                        ret = cellHttpCreateClient(&client);
                        if (ret < 0) { goto end; }
 
                        ret = cellHttpUtilParseUri(NULL, serverName, NULL, 0, &poolSize);
                        if (ret < 0) { goto end; }
       
                        char uriPoolAlloc[0x1024]; //allocate some space for the uri (a bit too much but eh)
                        uriPool = uriPoolAlloc;
                        if (NULL == uriPool) { goto end; } //fail
       
                        ret = cellHttpUtilParseUri(&uri, serverName, uriPool, poolSize, NULL);
                        if (ret < 0) {memFree((char*)uriPool, sizeof(uriPool)); goto end; }  
 
                        ret = cellHttpCreateTransaction(&trans, client, CELL_HTTP_METHOD_GET, &uri);
                        memFree((char*)uriPool, sizeof(uriPool));
                        if (ret < 0) { goto end; }
 
                        ret = cellHttpSendRequest(trans, NULL, 0, NULL); //send it :D
 
                        {//make a new scope for the status
                                int code = 0;
                                ret = cellHttpResponseGetStatusCode(trans, &code);
                                if (ret < 0) { goto end; }
               
                        }//end of status scope
 
                        ret = cellHttpResponseGetContentLength(trans, &length);
                        if (ret < 0) {
                                if (ret == CELL_HTTP_ERROR_NO_CONTENT_LENGTH) { has_cl = false;}
                            else { goto end; }}
               
                        recvd = 0;
 
                        while ((!has_cl) || (recvd < length))
                        {
                                ret = cellHttpRecvResponse(trans, r_buffer, bufMaxLen-1, &localRecv);
                                if (ret < 0) {goto end; } else if (localRecv == 0) break;
                                recvd += localRecv;
                                r_buffer[localRecv] = '\0'; //null terminate it
                    }
 
                        ret = 0;
 
                        {for(int i = 0;i<bufMaxLen;i++){retBuffer[i] = r_buffer[i];}}  //OUTPUT
 
 
 
                        /* shutdown procedures */
    end:
        if (trans) {
                cellHttpDestroyTransaction(trans);
                trans = 0;
        }
 
        if (client) {cellHttpDestroyClient(client);client = 0;}
       
 
        cellHttpEnd();  //END OF HTTP
 
        if (httpPool) {  memFree((char*)httpPool, sizeof(httpPool)); httpPool = NULL;}
 
 
        sys_net_finalize_network();
}