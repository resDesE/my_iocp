#include "stdafx.h"
#include "Request.h"

CRequest::CRequest()
{
}

CRequest::CRequest(PER_IO_CONTEXT* pIoContent)
{
}

CRequest::~CRequest()
{
}

// 服务器逻辑功能消息必须都先进这里
// 依据具体的消息号进行处理
// 所有消息在传输过程中必须以BSAEMSG结构发送
void CRequest::Run()
{

}