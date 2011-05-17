#pragma once

#include <winsvc.h>

class AFX_EXT_CLASS KNTService
{
static BOOL				      m_bInstance;			     //每个应用只有一个KNTService
	
protected:
	LPCTSTR               m_lpServiceName;
	LPCTSTR               m_lpDisplayName;
	DWORD                 m_dwCheckPoint;
	DWORD                 m_dwErr;
	BOOL                  m_bDebug;			        // 如果程序参数包含-d选项该值为TRUE
	SERVICE_STATUS        m_ssStatus;			      // 服务的当前状态
	SERVICE_STATUS_HANDLE	m_sshStatusHandle;
	DWORD                 m_dwControlsAccepted;	// bit-field of what control requests the
													                    // service will accept
													                    // (dflt: SERVICE_ACCEPT_STOP)
	PSID                  m_pUserSID;			      // 当前用户的安全ID
	BOOL                  m_bWinNT;			        // 如果是NT=TRUE,win95=FALSE
	BOOL                  m_fConsoleReady;

	// CreateService()函数的参数
	DWORD                 m_dwDesiredAccess;		// 缺省: SERVICE_ALL_ACCESS
	DWORD                 m_dwServiceType;		  // 缺省: SERVICE_WIN32_OWN_PROCESS
	DWORD                 m_dwStartType;			  // 缺省: SERVICE_AUTO_START
	DWORD                 m_dwErrorControl;		  // 缺省: SERVICE_ERROR_NORMAL
	LPCTSTR               m_pszLoadOrderGroup;	// 缺省: NULL
	DWORD                 m_dwTagID;				    // 检索TagID
	LPCTSTR               m_pszDependencies;		// 缺省: NULL
	LPCTSTR               m_pszStartName;			  // 缺省: NULL
	LPCTSTR               m_pszPassword;			  // 缺省: NULL


public:		// 构造/析构
	// 如果<DisplayName>没有设置, 那么缺省为then it defaults to <ServiceName>.
	KNTService(LPCTSTR ServiceName, LPCTSTR DisplayName = 0);
	~KNTService();

private:	//私有函数
	KNTService( const KNTService & );
	KNTService & operator=( const KNTService & );

public:		// 重载
		// You have to override the following two functions.
		// "Run()" will be called to start the real
		// service's activity. You must call
		//		ReportStatus(SERVICE_RUNNING);
		// before you enter your main-loop !
		// "Stop()" will be called to stop the work of
		// the service. You should break out of the mainloop
		// and return control to the KNTService class.
		//
		// In most cases these functions look like these:
		//
		//		void CMyService :: Run(DWORD argc, LPTSTR * argv) {
		//			ReportStatus(SERVICE_START_PENDING);
		//			// do some parameter processing ...
		//			ReportStatus(SERVICE_START_PENDING);
		//			// do first part of initialisation ...
		//			ReportStatus(SERVICE_START_PENDING);
		//			// do next part of initialisation
		//			// ...
		//			m_hStop = CreateEvent(0, TRUE, FALSE, 0);
		//			ReportStatus(SERVICE_RUNNING);
		//			while( WaitForSingleObject(m_hStop, 10) != WAIT_OBJECT_0 ) {
		//				// do something
		//			}
		//			if( m_hStop )
		//				CloseHandle(m_hStop);
		//		}
		//
		//		void CMyService :: Stop() {
		//			if( m_hStop )
		//				SetEvent(m_hStop);
		//			ReportStatus(SERVICE_STOP_PENDING);
		//		}
	virtual void	Run(DWORD argc, LPTSTR * argv) = 0;
	virtual void	Stop() = 0;

		// Pause() and Continue() do nothing by default.
		// You can override them to handle a control request.
		// Pause() should report the status SERVICE_PAUSED
		// and Continue() should report the status SERVICE_RUNNING
		// (see ReportStatus() below).
		// Note that normally these functions will never be called. If
		// you want a service, that accepts PAUSE and CONTINUE control
		// requests, you have to to add SERVICE_ACCEPT_PAUSE_CONTINUE
		// to the m_dwControlsAccepted data member.
	virtual void	Pause();
	virtual void	Continue();

		// Shutdown() will be called, if the service manager
		// requests for the SERVICE_CONTROL_SHUTDOWN control.
		// This control type occurs, when the system shuts down.
		// If you want to process this notification, you have to
		// add SERVICE_ACCEPT_SHUTDOWN to the m_dwControlsAccepted
		// data member (and to override this function). The default
		// implementation of Shutdown() does nothing.
	virtual void	Shutdown();

		// Call "RegisterService()" after you have constructed
		// a KNTService object:
		// A typical "main()" function of a service looks like this:
		//
		//		int main( int argc, char ** argv ) {
		//			CMyService serv;
		//			exit(serv.RegisterService(argc, argv));
		//		}
		//
		// Where "CMyService" is a KNTService derived class.
		// RegisterService() checks the parameterlist. The
		// following parameters will be detected:
		//		-i			install the service (calls
		//					"InstallService()" - see below)
		//
		//			-l <account>
		//					<account> is the name of a user,
		//					under which the service shall run.
		//					This option is useful with -i only.
		//					<account> needs to have the advanced
		//					user-right "Log on as a service"
		//					(see User-Manager)
		//					<account> should have the following
		//					format: "<Domain>\<user>"
		//					"EuroS2Team\jko" for instance.
		//					The domain "." is predefined as the
		//					local machine. So one might use
		//					".\jko" too.
		//
		//			-p <password>
		//					The password of the user, under which
		//					the service shall run. Only useful
		//					with -i and -l together.
		//
		//		-u			uninstall the service (calls
		//					"RemoveService()" - see below)
		//
		//		-d			debug the service (run as console
		//					process; calls "DebugService()"
		//					see below)
		//
		//		-e			end the service (if it is running)
		//
		//		-s			start the service (if it is not running)
		//					(Note that *you* normally cannot start
		//					an NT-service from the command-line.
		//					The SCM can.)
		//
		// Do not use -l and -p, if your service is of type
		// SERVICE_KERNEL_DRIVER or SERVICE_FILE_SYSTEM_DRIVER.
		// Furthermore you canot use -i and -s together. Instead
		// you have to start the command twice, first you install
		// the service, then you start it.
		// If none of the flags -i, -u, -e, -s and -d is set, then the
		// program starts as an NT service (only the SCM can start it
		// this way!).
		// NOTE: If UNICODE is #define'd, then <argc> and <argv>
		//		will be ignored and the original commandline
		//		of the program will be used to parse the
		//		arguments !
	virtual BOOL	RegisterService(int argc, char ** argv);
	
		// "StartDispatcher()" registers one service-procedure
		// to the service control dispatcher (using the predefined
		// "ServiceMain()" function below).
		// Override this funtion, if you want to develop a
		// multithreaded NT-Service.
	virtual BOOL	StartDispatcher();

		// Override "InstallService()" to manipulate the
		// installation behavior.
		// This function will only be called, if the
		// "-i" flag was passed to "RegisterService()"
		// (see above)
		// After "InstallService()" has completed, you
		// should be able to see the service in the
		// "services" control-panel-applet.
	virtual BOOL	InstallService();
	
		// RemoveService() removes a service from the system's
		// service-table.
		// It first tries to stop the service.
		// This function will be called only if the -u
		// flag was passed to the program. (see "RegisterService()"
		// above)
		// After removal of the service, it should no longer
		// appear in the "services" control-panel-applet.
	virtual BOOL	RemoveService();
	

		// EndService() stops a running service (if the service
		// is running as a service! Does not end a service
		// running as a console program (see DebugService()
		// below))
	virtual BOOL	EndService();

		// Start the service. Does the same as if the
		// SCM launches the program. Note that this method
		// will create a new instance of the program.
	virtual BOOL	StartupService();
	
		// Run a service as a console application. This makes it
		// easier to debug the service.
		// This function will be called only if the -d flag
		// was passed to the program(see "RegisterService()" above).
		// It transparently calls "Run()". You can simulate a
		// stop-request by pressing either Ctrl-C or Ctrl-Break (that
		// will call the "Stop()" method).
	virtual BOOL	DebugService(int argc, char **argv,BOOL faceless=FALSE);	//!! TCW MOD - added FACELESS parm to allow Win95 usage.

protected:	// implementation
		// Override "RegisterApplicationLog()", if you want to register
		// a different message file and/or differend supported types
		// than the default.
		// The proposed message file is the application itself.
		// The proposed types are:
		// EVENTLOG_ERROR_TYPE | EVENTLOG_WARNING_TYPE | EVENTLOG_INFORMATION_TYPE
		// This method will be called from inside "InstallService()" (see above)
		// Thus if you support errors only (for instance):
		//		void CMyService :: RegisterApplicationLog(LPCTSTR filename, DWORD ) {
		//			KNTService::RegisterApplicationLog(filename, EVENTLOG_ERROR_TYPE);
		//		}
		// This method will never be called on Win95.
	virtual void	RegisterApplicationLog(
						LPCTSTR lpszProposedMessageFile,
						DWORD dwProposedTypes
					);

		// "DeregisterApplicationLog()" is called from inside "RemoveService()"
		// (see above) to clear the registry-entries made by
		// "RegisterApplicationLog()"
	virtual void	DeregisterApplicationLog();

public:	// helpers
		// Retrieve a human-readable error message. The message
		// will be stored in <Buf> which is of size <Size>.
		// Returns a pointer to <Buf>.
	LPTSTR			GetLastErrorText(LPTSTR Buf, DWORD Size);

		// report status to the service-control-manager.
		// <CurState> can be one of:
		//		SERVICE_START_PENDING		-	the service is starting
		//		SERVICE_RUNNING				-	the service is running
		//		SERVICE_STOP_PENDING		-	the service is stopping
		//		SERVICE_STOPPED				-	the service is not running
		//		SERVICE_PAUSE_PENDING		-	the service pause is pending
		//		SERVICE_PAUSE				-	the service is paused
		//		SERVICE_CONTINUE_PENDING	-	the service is about to continue
	BOOL			ReportStatus(
						DWORD CurState,				// service's state
						DWORD WaitHint = 3000,		// expected time of operation in milliseconds
						DWORD ErrExit = 0			//!! TCW MOD - set to nonzero to flag *FATAL* error
					);

		// AddToMessageLog() writes a message to the application event-log.
		// (use EventViewer from the menu "Administrative Tools" to watch the log).
		// The <EventType> parameter can be set to one of the following values:
		//		EVENTLOG_ERROR_TYPE			Error event
		//		EVENTLOG_WARNING_TYPE		Warning event
		//		EVENTLOG_INFORMATION_TYPE	Information event
		//		EVENTLOG_AUDIT_SUCCESS		Success Audit event
		//		EVENTLOG_AUDIT_FAILURE		Failure Audit event
		// See "ReportEvent()" in the help-topics for further information.
	virtual void	AddToMessageLog(
						LPTSTR	Message,
						WORD	EventType = EVENTLOG_ERROR_TYPE,
						DWORD	dwEventID = DWORD(-1)
					);

public:		// default handlers
		// The following functions will be used by default.
		// You can provide other handlers. If so, you have to
		// overload several of the "virtual"s above.
	static void WINAPI	ServiceCtrl(DWORD CtrlCode);
	static void WINAPI	ServiceMain(DWORD argc, LPTSTR * argv);
	static BOOL WINAPI	ControlHandler(DWORD CtrlType);

//!! TCW MOD - added console support for Faceless Apps. Needed sometimes when something goes wrong.
public:
	BOOL OsIsWin95() const { return ! m_bWinNT; }
	void SetupConsole();
};

// Retrieve the one and only KNTService object:
KNTService * AfxGetService();
