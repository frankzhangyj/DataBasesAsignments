
// englishStudy.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"		// 主符号
#import "C:/Program Files/Common Files/System/ado/msado15.dll" no_namespace rename("EOF" , "adoEOF") rename("BOF", "adoBOF")



// CenglishStudyApp:
// 有关此类的实现，请参阅 englishStudy.cpp
//

class CenglishStudyApp : public CWinApp
{
public:
	CenglishStudyApp();
	// 连接数据库
	_ConnectionPtr m_pCon;
	BOOL ConnectDataBase(CString strLinkWord);

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CenglishStudyApp theApp;
