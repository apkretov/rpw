#include "server.h"

//"Named Pipe Server Using Overlapped I/O" @ https://msdn.microsoft.com/en-us/library/aa365603(v=vs.85).aspx
#include <strsafe.h> 

using std::exception;

#include "terminal.h"
#include "messages.h"

using namespace mtqc;
#include "MT4QuikConnector.h"
using namespace mtqc::MT4QuikConnector;

namespace mtqc {
	namespace server {
		constexpr int CONNECTING_STATE = 0, 
			READING_STATE = 1, 
			WRITING_STATE = 2, 
			INSTANCES = 4, 
			PIPE_TIMEOUT = 5000, 
			BUFSIZE = 4096;
		
		//There is an easier way to define structs or you could "alias" types you create.For example :
		//typedef struct { char title[50]; int book_id; } Books; 
		//Now, you can use Books directly to define variables of Books type without using struct keyword.Following is the example :
		//Books Book1, Book2; 
		//"The typedef Keyword" @ https://www.tutorialspoint.com/cplusplus/cpp_data_structures.htm
		typedef struct { 
			OVERLAPPED oOverlap;
			HANDLE hPipeInst;
			TCHAR chRequest[BUFSIZE];
			DWORD cbRead;
			TCHAR chReply[BUFSIZE];
			DWORD cbToWrite;
			DWORD dwState;
			BOOL fPendingIO;
		} PIPEINST, *LPPIPEINST; //typedef char CHAR; /*Character type.*/ 
										 //typedef CHAR * PSTR; /*Pointer to a string (char *).*/ 
										//Для того чтобы при помощи ключевого слова typedef определить основные и производные типы в одном и том же объявлении, 
										//деклараторы можно разделять запятыми. Например:
										//typedef char CHAR, *PSTR; 
										//"Спецификатор typedef" @ https://msdn.microsoft.com/ru-ru/library/05w82thz(v=vs.120).aspx
		
		static PIPEINST Pipe[INSTANCES];
		static HANDLE hEvents[INSTANCES];

		// This function is called to start an overlapped connect operation. It returns TRUE if an operation is pending or FALSE if the connection has been completed. 
		static BOOL srvConnectToNewClient(HANDLE hPipe, LPOVERLAPPED lpo, lua_State* L) { 
			BOOL fConnected, fPendingIO = FALSE;
			
			// Start an overlapped connection for this pipe instance. 
			fConnected = ConnectNamedPipe(hPipe, lpo); 
			if (fConnected) {
				srvMessageToQuik("9. ConnectNamedPipe failed with ...");
				return 0;
			}
			
			switch (GetLastError()) {
			case ERROR_IO_PENDING: // The overlapped connection in progress.
				fPendingIO = TRUE;
				break;
			case ERROR_PIPE_CONNECTED: // Client is already connected, so signal an event.
				if (SetEvent(lpo->hEvent)) break;
			default: {
				srvMessageToQuik("10. ConnectNamedPipe failed with ...");
				return 0; } // If an error occurs during the connect operation...
			}
			
			return fPendingIO;
		}

		// This function is called when an error occurs or when the client closes its handle to the pipe. Disconnect from this client, then call ConnectNamedPipe 
		//to wait for another client to connect. 
		static VOID srvDisconnectAndReconnect(DWORD i, lua_State* L) { 
			// Disconnect the pipe instance. 
			if (!DisconnectNamedPipe(Pipe[i].hPipeInst)) 
				srvMessageToQuik("8. DisconnectNamedPipe failed with ..."); 
			
			// Call a subroutine to connect to the new client. 
			Pipe[i].fPendingIO = srvConnectToNewClient(Pipe[i].hPipeInst, &Pipe[i].oOverlap, L); 
			
			Pipe[i].dwState = Pipe[i].fPendingIO 
				? CONNECTING_STATE : /*still connecting*/ 
				READING_STATE /*ready to read*/;
		}

		static VOID srvGetAnswerToRequest(LPPIPEINST pipe, lua_State* L) {
			srvMessageToQuik(pipe->chRequest);
			StringCchCopy(pipe->chReply, BUFSIZE, TEXT("Default answer from server"));
			pipe->cbToWrite = (lstrlen(pipe->chReply) + 1)*sizeof(TCHAR);
		}

		//"Named Pipe Server Using Overlapped I/O" @ https://msdn.microsoft.com/en-us/library/aa365603(v=vs.85).aspx
		static int srvStartQuikServer(lua_State* L) { 
			try {
				DWORD i, dwWait, cbRet, dwErr;
				BOOL fSuccess;
				LPTSTR lpszPipename = TEXT("\\\\.\\pipe\\mynamedpipe");
				srvMessageToQuik("Start Quik server.");
				
				// The initial loop creates several instances of a named pipe along with an event object for each instance. An overlapped ConnectNamedPipe operation 
				//is started for each instance. 
				for (i = 0; i < INSTANCES; i++) { 
					// Create an event object for this instance. 
					hEvents[i] = CreateEvent(
						NULL /*default security attribute*/, 
						TRUE /*manual-reset event*/, 
						TRUE /*initial state = signaled*/, 
						NULL /*unnamed event object*/
					); 
					
					if (hEvents[i] == NULL) {
						srvMessageToQuik("1. CreateEvent failed with error...");
						return 0;
					}
					
					Pipe[i].oOverlap.hEvent = hEvents[i];
					Pipe[i].hPipeInst = CreateNamedPipe(
						lpszPipename /*pipe name*/, 
						PIPE_ACCESS_DUPLEX | /*read/write access*/ 
							FILE_FLAG_OVERLAPPED /*overlapped mode*/, 
						PIPE_TYPE_MESSAGE | /*message-type pipe*/ 
							PIPE_READMODE_MESSAGE | /*message-read mode*/ 
							PIPE_WAIT /*blocking mode*/, 
						INSTANCES /*number of instances*/, 
						BUFSIZE*sizeof(TCHAR) /*output buffer size*/, 
						BUFSIZE*sizeof(TCHAR) /*input buffer size*/, 
						PIPE_TIMEOUT /*client time-out*/, 
						NULL /*default security attributes*/
					);
					
					if (Pipe[i].hPipeInst == INVALID_HANDLE_VALUE) {
						srvMessageToQuik("2. CreateNamedPipe failed with error...");
						return 0;
					}
					// Call the subroutine to connect to the new client
					Pipe[i].fPendingIO = srvConnectToNewClient(Pipe[i].hPipeInst, &Pipe[i].oOverlap, L); 
					Pipe[i].dwState = Pipe[i].fPendingIO 
						? CONNECTING_STATE 
						: /*still connecting*/ 
						READING_STATE /*ready to read*/;
				}
				
				// Wait for the event object to be signaled, indicating completion of an overlapped read, write, or connect operation. 
				while (gobjTerminal.getRun()) { 
					// dwWait shows which pipe completed the operation. 
					dwWait = WaitForMultipleObjects(
						INSTANCES /*number of event objects*/, 
						hEvents /*array of event objects*/, 
						FALSE /*does not wait for all*/, 
						INFINITE /*waits indefinitely*/
					); 
					
					// determines which pipe
					i = dwWait - WAIT_OBJECT_0;   
					if (i < 0 || i >(INSTANCES - 1)) {
						srvMessageToQuik("3. Index out of range.");
						return 0;
					}
					
					// Get the result if the operation was pending. 
					if (Pipe[i].fPendingIO) { 
						fSuccess = GetOverlappedResult(
							Pipe[i].hPipeInst /*handle to pipe*/, 
							&Pipe[i].oOverlap /*OVERLAPPED structure */, 
							&cbRet /*bytes transferred */, 
							FALSE /*do not wait */
						);
						
						switch (Pipe[i].dwState) {
						// Pending connect operation
						case CONNECTING_STATE: 
							if (!fSuccess) {
								srvMessageToQuik("4. Error...");
								return 0;
							}
							Pipe[i].dwState = READING_STATE;
							break;
						
						// Pending read operation 
						case READING_STATE: 
							if (!fSuccess || cbRet == 0) {
								srvDisconnectAndReconnect(i, L);
								continue;
							}
							Pipe[i].cbRead = cbRet;
							Pipe[i].dwState = WRITING_STATE;
							break;
						
						// Pending write operation
						case WRITING_STATE:  
							if (!fSuccess || cbRet != Pipe[i].cbToWrite) {
								srvDisconnectAndReconnect(i, L);
								continue;
							}
							Pipe[i].dwState = READING_STATE;
							break;
						
						default: {
							srvMessageToQuik("5. Invalid pipe state.");
							return 0;
						}
					}
					}

					// The pipe state determines which operation to do next.
					switch (Pipe[i].dwState) { 
					// READING_STATE: The pipe instance is connected to the client and is ready to read a request from the client. 
					case READING_STATE: 
						fSuccess = ReadFile(Pipe[i].hPipeInst, Pipe[i].chRequest, BUFSIZE*sizeof(TCHAR), &Pipe[i].cbRead, &Pipe[i].oOverlap);
					
						// The read operation completed successfully. 
						if (fSuccess && Pipe[i].cbRead != 0) { 
							Pipe[i].fPendingIO = FALSE;
							Pipe[i].dwState = WRITING_STATE;
							continue;
						}
					
						// The read operation is still pending. 
						dwErr = GetLastError(); 
						if (!fSuccess && (dwErr == ERROR_IO_PENDING)) {
							Pipe[i].fPendingIO = TRUE;
							continue;
						}
						srvDisconnectAndReconnect(i, L); // An error occurred; disconnect from the client. 
						break;

					// WRITING_STATE: The request was successfully read from the client. Get the reply data and write it to the client. 
					case WRITING_STATE: 
						srvGetAnswerToRequest(&Pipe[i], L);
						fSuccess = WriteFile(Pipe[i].hPipeInst, Pipe[i].chReply, Pipe[i].cbToWrite, &cbRet, &Pipe[i].oOverlap);
					
						// The write operation completed successfully. 
						if (fSuccess && cbRet == Pipe[i].cbToWrite) { 
							Pipe[i].fPendingIO = FALSE;
							Pipe[i].dwState = READING_STATE;
							continue;
						}
					
						dwErr = GetLastError(); // The write operation is still pending. 
						if (!fSuccess && (dwErr == ERROR_IO_PENDING)) {
							Pipe[i].fPendingIO = TRUE;
							continue;
						}
						srvDisconnectAndReconnect(i, L); // An error occurred; disconnect from the client. 
						break;

					default: {
						srvMessageToQuik("7. Invalid pipe state.");
						return 0; 
					}
					}	
				}

				return 0;
			}
			catch (const exception& objException) {
				messages::messageException(objException, __FUNCTION__, __LINE__);
				return 0;
			}	
		}

		//"Вызов функций QLua(Lua) из DLL, написанной на C/C++" @ http://quikluacsharp.ru/qlua-c-cpp-csharp/vyzov-funktsij-qlua-lua-iz-dll-napisannoj-na-c-c/
		int startQuikServer(lua_State* L) { 
			try {
				//Запускает выполнение функции MyCallback() в отдельном потоке
				std::thread objThread(srvStartQuikServer, L); 
				//Отсоединяет созданный поток от основного, делая его "фоновым"
				objThread.detach(); 
				//Завершает работу функции forLua_StartCallback, при этом функция MyCallback продолжает работать в отдельном потоке
				return 0; 
			}
			catch (const exception& objException) {
				messages::messageException(objException, __FUNCTION__, __LINE__);
				return 0;
			}
		}	
	}	
}
