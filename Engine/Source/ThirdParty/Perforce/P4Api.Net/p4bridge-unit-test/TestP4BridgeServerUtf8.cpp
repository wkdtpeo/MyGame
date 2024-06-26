#include "StdAfx.h"
#include "UnitTestFrameWork.h"
#include "TestP4BridgeServerUtf8.h"

#include "../p4bridge/P4BridgeClient.h"
#include "../p4bridge/P4BridgeServer.h"

#include <conio.h>

CREATE_TEST_SUITE(TestP4BridgeServerUtf8)

TestP4BridgeServerUtf8::TestP4BridgeServerUtf8(void)
{
    UnitTestSuite::RegisterTest(ServerConnectionTest, "ServerConnectionTest");
    UnitTestSuite::RegisterTest(TestNonUnicodeClientToUnicodeServer, "TestNonUnicodeClientToUnicodeServer");
    UnitTestSuite::RegisterTest(TestUntaggedCommand, "TestUntaggedCommand");
    UnitTestSuite::RegisterTest(TestUnicodeUserName, "TestUnicodeUserName");
    UnitTestSuite::RegisterTest(TestTaggedCommand, "TestTaggedCommand");
    UnitTestSuite::RegisterTest(TestTextOutCommand, "TestTextOutCommand");
    UnitTestSuite::RegisterTest(TestBinaryOutCommand, "TestBinaryOutCommand");
    UnitTestSuite::RegisterTest(TestErrorOutCommand, "TestErrorOutCommand");
}


TestP4BridgeServerUtf8::~TestP4BridgeServerUtf8(void)
{
}

char unitTestDir8[MAX_PATH];
char unitTestZip8[MAX_PATH];
char * TestDir8 = "c:\\MyTestDir";
char * TestZip8 = "c:\\MyTestDir\\u.exe";
char * rcp_cmd8 = "p4d -r C:/MyTestDir -jr checkpoint.1";
char * udb_cmd8 = "p4d -r C:/MyTestDir -xu";
char * p4d_cmd8 = "p4d -p6666 -IdUnitTestServer -rC:/MyTestDir -Llog";
//char * p4d_xi_cmd8 = "p4d -xi";

void * pi8 = NULL;

bool TestP4BridgeServerUtf8::Setup()
{
    // remove the test directory if it exists
    UnitTestSuite::rmDir( TestDir8 ) ;

    GetCurrentDirectory(sizeof(unitTestDir8), unitTestDir8);

    strcpy( unitTestZip8, unitTestDir8);
    strcat( unitTestZip8, "\\u.exe");

    if (!CreateDirectory( TestDir8, NULL)) return false;

    if (!CopyFile(unitTestZip8, TestZip8, false)) return false;

    if (!SetCurrentDirectory(TestDir8)) return false;

    pi8= UnitTestSuite::RunProgram("u", TestDir8, true, true);
    if (!pi8) 
	{
		SetCurrentDirectory(unitTestDir8);
		return false;
	}

    delete pi8;

    pi8 = UnitTestSuite::RunProgram(rcp_cmd8, TestDir8, true, true);
    if (!pi8) 
	{
		SetCurrentDirectory(unitTestDir8);
		return false;
	}

    delete pi8;

    pi8 = UnitTestSuite::RunProgram(udb_cmd8, TestDir8, true, true);
    if (!pi8) 
	{
		SetCurrentDirectory(unitTestDir8);
		return false;
	}

    delete pi8;

    //server deployed by u.ex is already in Unicode mode
    //pi8 = UnitTestSuite::RunProgram(p4d_xi_cmd8, TestDir8, false, true);
    //if (!pi8) return false;

    //delete pi8;

    pi8 = UnitTestSuite::RunProgram(p4d_cmd8, TestDir8, false, false);
    if (!pi8) 
	{
		SetCurrentDirectory(unitTestDir8);
		return false;
	}

//    _getch();

    return true;
}

bool TestP4BridgeServerUtf8::TearDown(char* testName)
{
    if (pi8)
        UnitTestSuite::EndProcess( (LPPROCESS_INFORMATION) pi8 );

    SetCurrentDirectory(unitTestDir8);

    UnitTestSuite::rmDir( TestDir8 ) ;

	p4base::PrintMemoryState(testName);

    return true;
}

bool TestP4BridgeServerUtf8::ServerConnectionTest()
{
    P4ClientError* connectionError = NULL;
    // create a new server
    P4BridgeServer * ps = new P4BridgeServer("localhost:6666", "admin", "", "");
    ASSERT_NOT_NULL(ps);

    // connect and see if the api returned an error. 
    if( !ps->connected( &connectionError ) )
    {
        char buff[256];
        sprintf(buff, "Connection error: %s", *connectionError);
        // Abort if the connect did not succeed
        ASSERT_FAIL(buff);
    }

    ASSERT_INT_TRUE(ps->unicodeServer());
    ps->set_charset("utf8", "utf16le");

    delete ps;

	return true;
}

bool TestP4BridgeServerUtf8::TestNonUnicodeClientToUnicodeServer()
{
    P4ClientError* connectionError = NULL;
    // create a new server
    P4BridgeServer * ps = new P4BridgeServer("localhost:6666", "admin", "", "admin_space");
    ASSERT_NOT_NULL(ps);

    // connect and see if the api returned an error. 
    if( !ps->connected( &connectionError ) )
    {
        char buff[256];
        sprintf(buff, "Connection error: %s", *connectionError);
        // Abort if the connect did not succeed
        ASSERT_FAIL(buff);
    }

    
	ASSERT_INT_TRUE(ps->unicodeServer());

    char* params[1];
    params[0] = "//depot/mycode/*";

    ASSERT_FALSE(ps->run_command("files", 5, 0, params, 1))

    P4ClientError * out = ps->get_ui(5)->GetErrorResults();

    ASSERT_STRING_STARTS_WITH(out->Message.c_str(), "Unicode server permits only unicode enabled clients.")
   
    delete ps;

    return true;
}

bool TestP4BridgeServerUtf8::TestUntaggedCommand()
{
    P4ClientError* connectionError = NULL;
    // create a new server
    P4BridgeServer * ps = new P4BridgeServer("localhost:6666", "admin", "", "admin_space");
    ASSERT_NOT_NULL(ps);

    // connect and see if the api returned an error. 
    if( !ps->connected( &connectionError ) )
    {
        char buff[256];
        sprintf(buff, "Connection error: %s", *connectionError);
        // Abort if the connect did not succeed
        ASSERT_FAIL(buff);
    }

    ASSERT_INT_TRUE(ps->unicodeServer());
    ps->set_charset("utf8", "utf16le");

    char* params[1];
    params[0] = "//depot/mycode/*";

    ASSERT_INT_TRUE(ps->run_command("files", 7, 0, params, 1))

    P4ClientInfoMsg * out = ps->get_ui(7)->GetInfoResults();

    ASSERT_STRING_EQUAL(out->Message.c_str(), "//depot/MyCode/ReadMe.txt#1 - add change 1 (text)")
	ASSERT_NOT_NULL(out->Next)
    ASSERT_STRING_EQUAL(out->Next->Message.c_str(), "//depot/MyCode/Silly.bmp#1 - add change 1 (binary)")
	ASSERT_NOT_NULL(out->Next->Next)
    ASSERT_STRING_EQUAL(out->Next->Next->Message.c_str(), "//depot/MyCode/\xD0\x9F\xD1\x8E\xD0\xBF.txt#1 - add change 3 (utf16)")

    delete ps;

    return true;
}


// Callback to provide password for "login" in TestUnicodeUserName()
void _stdcall ProvidePassword(int cmdId, const char *message, char *response, int responseSize, int noEcho)
{
	strncpy(response,"pass",responseSize);
}


bool TestP4BridgeServerUtf8::TestUnicodeUserName()
{
    P4ClientError* connectionError = NULL;
    // create a new server
    //Алексей = "\xD0\x90\xD0\xbb\xD0\xB5\xD0\xBA\xD1\x81\xD0\xB5\xD0\xB9\0" IN utf-8
    P4BridgeServer * ps = new P4BridgeServer("localhost:6666", "\xD0\x90\xD0\xBB\xD0\xB5\xD0\xBA\xD1\x81\xD0\xB5\xD0\xB9\0", "pass", "\xD0\x90\xD0\xbb\xD0\xB5\xD0\xBA\xD1\x81\xD0\xB5\xD0\xB9\0");
    ASSERT_NOT_NULL(ps);

    // connect and see if the api returned an error. 
    if( !ps->connected( &connectionError ) )
    {
        char buff[256];
        sprintf(buff, "Connection error: %s", (*connectionError).Message);
        // Abort if the connect did not succeed
        ASSERT_FAIL(buff);
    }

    ASSERT_INT_TRUE(ps->unicodeServer());
    ps->set_charset("utf8", "utf16le");

	bool needLogin = ps->UseLogin();

	P4BridgeClient* myClient = ps->get_ui(7);

	if (needLogin)
	{
		ps->SetPromptCallbackFn( ProvidePassword );

		ps->set_user("\xD0\x90\xD0\xBB\xD0\xB5\xD0\xBA\xD1\x81\xD0\xB5\xD0\xB9\0");
		ps->set_password("pass");
	
		char *loginArgs = "-a";
		ps->run_command("login", 7, 0, &loginArgs, 1);

		P4ClientInfoMsg * lout = ps->get_ui(7)->GetInfoResults();
	}

    char* params[1];
    params[0] = "//depot/mycode/*";

    ASSERT_INT_TRUE(ps->run_command("files", 7, 0, params, 1))

    P4ClientInfoMsg * out = ps->get_ui(7)->GetInfoResults();

	ASSERT_STRING_EQUAL(out->Message.c_str(), "//depot/MyCode/ReadMe.txt#1 - add change 1 (text)")
	ASSERT_NOT_NULL(out->Next)
	ASSERT_STRING_EQUAL(out->Next->Message.c_str(), "//depot/MyCode/Silly.bmp#1 - add change 1 (binary)")
	ASSERT_NOT_NULL(out->Next->Next)
    ASSERT_STRING_EQUAL(out->Next->Next->Message.c_str(), "//depot/MyCode/\xD0\x9F\xD1\x8E\xD0\xBF.txt#1 - add change 3 (utf16)")

    delete ps;

    return true;
}

bool TestP4BridgeServerUtf8::TestTaggedCommand()
{
    P4ClientError* connectionError = NULL;
    // create a new server
    P4BridgeServer * ps = new P4BridgeServer("localhost:6666", "admin", "", "admin_space");
    ASSERT_NOT_NULL(ps);

    // connect and see if the api returned an error. 
    if( !ps->connected( &connectionError ) )
    {
        char buff[256];
        sprintf(buff, "Connection error: %s", *connectionError);
        // Abort if the connect did not succeed
        ASSERT_FAIL(buff);
    }

    ASSERT_INT_TRUE(ps->unicodeServer());
    ps->set_charset("utf8", "utf16le");

    char* params[1];
    params[0] = "//depot/mycode/*";

    ASSERT_INT_TRUE(ps->run_command("files", 7, 1, params, 1))

    StrDictListIterator * out = ps->get_ui(7)->GetTaggedOutput();

    ASSERT_NOT_NULL(out);

    int itemCnt = 0;
    while (StrDictList * pItem = out->GetNextItem())
    {
        int entryCnt = 0;

        while (KeyValuePair * pEntry = out->GetNextEntry())
        {
            if ((itemCnt == 0) && (strcmp(pEntry->key.c_str(), "depotFile") == 0))
                ASSERT_STRING_EQUAL(pEntry->value.c_str(), "//depot/MyCode/ReadMe.txt")
            if ((itemCnt == 1) && (strcmp(pEntry->key.c_str(), "depotFile") == 0))
                ASSERT_STRING_EQUAL(pEntry->value.c_str(), "//depot/MyCode/Silly.bmp")
            if ((itemCnt == 2) && (strcmp(pEntry->key.c_str(), "depotFile") == 0))
                ASSERT_STRING_EQUAL(pEntry->value.c_str(), "//depot/MyCode/\xD0\x9F\xD1\x8E\xD0\xBF.txt")
            entryCnt++;
        }
        ASSERT_NOT_EQUAL(entryCnt, 0);
        itemCnt++;
    }
    ASSERT_EQUAL(itemCnt, 3);

    delete out;

	delete ps;


    return true;
}

bool TestP4BridgeServerUtf8::TestTextOutCommand()
{
    P4ClientError* connectionError = NULL;
    // create a new server
    P4BridgeServer * ps = new P4BridgeServer("localhost:6666", "admin", "", "admin_space");
    ASSERT_NOT_NULL(ps);

    // connect and see if the api returned an error. 
    if( !ps->connected( &connectionError ) )
    {
        char buff[256];
        sprintf(buff, "Connection error: %s", *connectionError);
        // Abort if the connect did not succeed
        ASSERT_FAIL(buff);
    }

    ASSERT_INT_TRUE(ps->unicodeServer());
    ps->set_charset("utf8", "utf16le");

    char* params[1];
    params[0] = "//depot/MyCode/ReadMe.txt";

    ASSERT_INT_TRUE(ps->run_command("print", 7, 1, params, 1))

    const char * out = ps->get_ui(7)->GetTextResults();

    ASSERT_NOT_NULL(out);

    ASSERT_STRING_EQUAL(out, "Don't Read This!\n\nIt's Secret!")

    delete ps;

    return true;
}

bool TestP4BridgeServerUtf8::TestBinaryOutCommand()
{
    P4ClientError* connectionError = NULL;
    // create a new server
    P4BridgeServer * ps = new P4BridgeServer("localhost:6666", "admin", "", "admin_space");
    ASSERT_NOT_NULL(ps);

    // connect and see if the api returned an error. 
    if( !ps->connected( &connectionError ) )
    {
        char buff[256];
        sprintf(buff, "Connection error: %s", *connectionError);
        // Abort if the connect did not succeed
        ASSERT_FAIL(buff);
    }

    ASSERT_INT_TRUE(ps->unicodeServer());
    ps->set_charset("utf8", "utf16le");

    char* params[1];
    params[0] = "//depot/MyCode/Silly.bmp";

    ASSERT_INT_TRUE(ps->run_command("print", 3, 1, params, 1))

    int cnt = ps->get_ui(3)->GetBinaryResultsCount();

    ASSERT_EQUAL(cnt, 3126)

    const unsigned char * out = ps->get_ui(3)->GetBinaryResults();

    ASSERT_NOT_NULL(out);
    ASSERT_EQUAL((*(((unsigned char*)out) + 1)), 0x4d)

    delete ps;

    return true;
}

bool TestP4BridgeServerUtf8::TestErrorOutCommand()
{
    P4ClientError* connectionError = NULL;
    // create a new server
    P4BridgeServer * ps = new P4BridgeServer("localhost:6666", "admin", "", "admin_space");
    ASSERT_NOT_NULL(ps);

    // connect and see if the api returned an error. 
    if( !ps->connected( &connectionError ) )
    {
        char buff[256];
        sprintf(buff, "Connection error: %s", *connectionError);
        // Abort if the connect did not succeed
        ASSERT_FAIL(buff);
    }

    ASSERT_INT_TRUE(ps->unicodeServer());
    ps->set_charset("utf8", "utf16le");

    char* params[1];
    params[0] = "//depot/MyCode/Billy.bmp";

    // run a command against a nonexistent file
    // Should fail
    ASSERT_FALSE(ps->run_command("rent", 88, 1, params, 1))

    P4ClientError * out = ps->get_ui(88)->GetErrorResults();

    ASSERT_NOT_NULL(out);

	ASSERT_EQUAL(out->ErrorCode, 805379098);
    ASSERT_NULL(out->Next)

    delete ps;

    return true;
}
