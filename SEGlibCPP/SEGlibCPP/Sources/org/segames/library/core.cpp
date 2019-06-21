#include <org/segames/library/core.h>

#ifdef _WIN32
#include <Windows.h>
#undef ERROR //Because why the f*ck should this exist?
#include <ImageHlp.h>
#include <Psapi.h>
#include <memory>
#endif

namespace org
{

	namespace segames
	{

		namespace library
		{

			bool Core::printTime = true;
			std::istream* Core::in = &std::cin;
			std::ostream* Core::err = &std::cerr;
			std::ostream* Core::warn = &std::cout;
			std::ostream* Core::out = &std::cout;
			const std::string* const Core::labels = new std::string[4]{
				" [Info]   ",
				"<Warning> ",
				"<<ERROR>> ",
				" *Note*   "
			};

			void Core::printlnInternal(const PrintLabel label, const std::string& message, std::ostream& stream)
			{
				if (label != PrintLabel::NONE)
					stream << labels[(size_t)label].c_str() << message.c_str() << std::endl;
				else
					stream << message.c_str() << std::endl;
			}

			std::istream& Core::getIn()
			{
				return *in;
			}

			std::ostream& Core::getErr()
			{
				return *err;
			}

			std::ostream& Core::getWarn()
			{
				return *warn;
			}

			std::ostream& Core::getOut()
			{
				return *out;
			}

			void Core::setIn(std::istream& in_)
			{
				in = &in_;
			}

			void Core::setErr(std::ostream& err_)
			{
				err = &err_;
			}

			void Core::setWarn(std::ostream& warn_)
			{
				warn = &warn_;
			}

			void Core::setOut(std::ostream& out_)
			{
				out = &out_;
			}

			void Core::setAllOut(std::ostream& out_)
			{
				setErr(out_);
				setWarn(out_);
				setOut(out_);
			}

			void Core::setPrintTime(const bool flag)
			{
				printTime = flag;
			}

			void Core::println(const std::string& message)
			{
				println(PrintLabel::NONE, message);
			}

			void Core::println(const PrintLabel label, const std::string& message)
			{
				switch (label)
				{
				case PrintLabel::WARNING:
					if (warn)
						printlnInternal(label, message, getWarn());
					else
						printlnInternal(label, message, getOut());
					break;
				case PrintLabel::ERROR:
					if (err)
						printlnInternal(label, message, getErr());
					else
						printlnInternal(label, message, getOut());
					break;
				default:
					printlnInternal(label, message, getOut());
					break;
				}

			}

#ifdef _WIN32
			int addr2line(char const * const program_name, void const * const addr)
			{
				char addr2line_cmd[512] = { 0 };

				/* have addr2line map the address to the relent line in the code */
#ifdef __APPLE__
  /* apple does things differently... */
				sprintf(addr2line_cmd, "atos -o %.256s %p", program_name, addr);
#else
				sprintf(addr2line_cmd, "addr2line -f -p -e %.256s %p", program_name, addr);
#endif

				return system(addr2line_cmd);
			}

			void Core::getStackTrace(std::ostream& out, const int offset = 1)
			{
				/*HANDLE process;
				HANDLE thread;
				CONTEXT context;
				MODULEINFO moduleInfo;
				IMAGE_NT_HEADERS* imageHeaders;
				STACKFRAME64 frame;
				DWORD numModules;
				std::unique_ptr<HMODULE> modules;

				process = GetCurrentProcess();
				thread = GetCurrentThread();

				if (!SymInitialize(process, NULL, true))
					return;

				if (!GetThreadContext(thread, &context))
				{
					SymCleanup(process);
					return;
				}

				EnumProcessModules(process, NULL, 0, &numModules);
				modules = std::unique_ptr<HMODULE>(new HMODULE[numModules]);
				EnumProcessModules(process, modules.get(), sizeof(HMODULE), &numModules);

				GetModuleInformation(process, modules.get()[0], &moduleInfo, sizeof(MODULEINFO));
				imageHeaders = ImageNtHeader(moduleInfo.lpBaseOfDll);

				out << GetLastError() << std::endl;

#ifdef _M_X64
				frame.AddrPC.Offset = context.Rip;
				frame.AddrPC.Mode = AddrModeFlat;
				frame.AddrStack.Offset = context.Rsp;
				frame.AddrStack.Mode = AddrModeFlat;
				frame.AddrFrame.Offset = context.Rbp;
				frame.AddrFrame.Mode = AddrModeFlat;
#else
				frame.AddrPC.Offset = context.Eip;
				frame.AddrPC.Mode = AddrModeFlat;
				frame.AddrStack.Offset = context.Esp;
				frame.AddrStack.Mode = AddrModeFlat;
				frame.AddrFrame.Offset = context.Ebp;
				frame.AddrFrame.Mode = AddrModeFlat;
#endif
				out << GetLastError() << std::endl;

				out << "MACHINE: " << imageHeaders->FileHeader.Machine << "   " << IMAGE_FILE_MACHINE_AMD64 << std::endl;

				DWORD64 symbolOffset = 0;
				DWORD lineOffset = 0;
				while (StackWalk(imageHeaders->FileHeader.Machine,
					process, thread,
					&frame, &context,
					NULL, SymFunctionTableAccess, SymGetModuleBase, NULL))
				{
					const int nameLen = 1024;
					char name[nameLen];
					char buf[nameLen + sizeof(IMAGEHLP_SYMBOL)];
					IMAGEHLP_SYMBOL* symbol = (IMAGEHLP_SYMBOL*)buf;
					IMAGEHLP_LINE line = { 0 };

					out << GetLastError() << std::endl;

					memset(name, 0, sizeof(name));
					memset(buf, 0, sizeof(buf));

					symbol->SizeOfStruct = sizeof(*symbol);
					symbol->MaxNameLength = nameLen;

					SymGetSymFromAddr(process, frame.AddrPC.Offset, &symbolOffset, symbol);

					out << GetLastError() << std::endl;

					UnDecorateSymbolName(symbol->Name, name, nameLen, UNDNAME_COMPLETE);

					out << GetLastError() << std::endl;

					SymGetLineFromAddr(process, frame.AddrPC.Offset, &lineOffset, &line);

					out << GetLastError() << std::endl;

					out << "[" << frame.AddrPC.Offset << "]: \"" << std::string(name).c_str() << "\" # \"" << symbol->Name << "\" " << symbolOffset << std::endl;
					out << "\\ \"" << line.FileName << "\" \"" << line.LineNumber << "\"" << std::endl;
					//out << GetLastError() << " / " << frame.AddrPC.Offset << std::endl;
				}

				SymCleanup(process);*/

				void* frames[16];
				int captured = CaptureStackBackTrace(0, 16, frames, NULL);

				for (int i = 0; i < captured-4; i++)
					addr2line(__argv[0], frames[i]);
					//printf("%p\n", frames[i]);
				
			}
#endif

		}

	}

}
