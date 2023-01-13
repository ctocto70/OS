

#include <iostream>
#include <vector>
#include <windows.h>
#include <algorithm>

	int main()
	{
		const wchar_t* pathAProcess = L"..\\..\\A\\x64\\Debug\\A.exe";
		const wchar_t* pathMProcess = L"..\\..\\M\\x64\\Debug\\M.exe";
		const wchar_t* pathPProcess = L"..\\..\\P\\x64\\Debug\\P.exe";
		const wchar_t* pathSProcess = L"..\\..\\S\\x64\\Debug\\S.exe";

		std::vector<HANDLE> hPipes;
		auto closePipes = [&hPipes]() {
			std::for_each(hPipes.begin(), hPipes.end(), CloseHandle);
		};

		SECURITY_ATTRIBUTES saPipe = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };

		HANDLE readPipeAM, writePipeAM;
		bool pipeAM = CreatePipe(&readPipeAM, &writePipeAM, &saPipe, 0);
		hPipes.push_back(readPipeAM);
		hPipes.push_back(writePipeAM);

		HANDLE readPipeMP, writePipeMP;
		bool pipeMP = CreatePipe(&readPipeMP, &writePipeMP, &saPipe, 0);
		hPipes.push_back(readPipeMP);
		hPipes.push_back(writePipeMP);

		HANDLE readPipePS, writePipePS;
		bool pipePS = CreatePipe(&readPipePS, &writePipePS, &saPipe, 0);
		hPipes.push_back(readPipePS);
		hPipes.push_back(writePipePS);

		STARTUPINFO startInfoProcessM, startInfoProcessA, startInfoProcessP, startInfoProcessS;

		GetStartupInfo(&startInfoProcessA);
		startInfoProcessA.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
		startInfoProcessA.hStdOutput = writePipeAM;
		startInfoProcessA.dwFlags = STARTF_USESTDHANDLES;

		std::vector<PROCESS_INFORMATION> processes;
		auto closeAllProcesses = [&processes]() {
			std::for_each(processes.begin(), processes.end(), [](const PROCESS_INFORMATION& process_Info) {
				TerminateProcess(process_Info.hProcess, 1);
				CloseHandle(process_Info.hThread);
				CloseHandle(process_Info.hProcess);
				});
		};

		
		
		
		
		
		PROCESS_INFORMATION processA_Info;
		if (!CreateProcess(pathAProcess, NULL, NULL, NULL, TRUE, 0, NULL, NULL, &startInfoProcessA, &processA_Info)) {
			return 1;
		}
		processes.push_back(processA_Info);





		GetStartupInfo(&startInfoProcessM);
		startInfoProcessM.hStdInput = readPipeAM;
		startInfoProcessM.hStdOutput = writePipeMP;
		startInfoProcessM.dwFlags = STARTF_USESTDHANDLES;		
		PROCESS_INFORMATION processM_Info;
		if (!CreateProcess(pathMProcess, NULL, NULL, NULL, TRUE, 0, NULL, NULL, &startInfoProcessM, &processM_Info)) {
			closeAllProcesses();
			return 1;
		}
		processes.push_back(processM_Info);








		GetStartupInfo(&startInfoProcessP);
		startInfoProcessP.hStdInput = readPipeMP;
		startInfoProcessP.hStdOutput = writePipePS;
		startInfoProcessP.dwFlags = STARTF_USESTDHANDLES;		
		PROCESS_INFORMATION processP_Info;
		if (!CreateProcess(pathPProcess, NULL, NULL, NULL, TRUE, 0, NULL, NULL, &startInfoProcessP, &processP_Info)) {
			closeAllProcesses();
			return 1;
		}
		processes.push_back(processP_Info);








		GetStartupInfo(&startInfoProcessS);
		startInfoProcessS.hStdInput = readPipePS;
		startInfoProcessS.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
		startInfoProcessS.dwFlags = STARTF_USESTDHANDLES;

			
		PROCESS_INFORMATION processS_Info;
		if (!CreateProcess(pathSProcess, NULL, NULL, NULL, TRUE, 0, NULL, NULL, &startInfoProcessS, &processS_Info)) {
			closeAllProcesses();
			return 1;
		}
		processes.push_back(processS_Info);






		std::for_each(processes.begin(), processes.end(), [](const PROCESS_INFORMATION& process_Info) {
			WaitForSingleObject(process_Info.hProcess, INFINITY);
			CloseHandle(process_Info.hThread);
			CloseHandle(process_Info.hProcess);
			});

		closePipes();
	}