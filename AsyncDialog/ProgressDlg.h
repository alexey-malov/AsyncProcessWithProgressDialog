#pragma once
#include "resource.h"

class ICancelableProcess;

class IProgressDlg
{
public:
	typedef std::function<void()> CancelHandler;
	typedef std::function<void()> OpenHandler;

	virtual bool Show() = 0;
	virtual void Close(bool success) = 0;
	virtual void SetProgress(double progress) = 0;
	virtual void DoOnCancel(CancelHandler const& handler) = 0;
	virtual void DoOnOpen(OpenHandler const& handler) = 0;
	virtual ~IProgressDlg(){}
};


class CProgressDlg 
	: public CDialogImpl<CProgressDlg>
	, public IProgressDlg
{
	enum { 
		FINISH_MESSAGE = WM_USER + 1,
		PROGRESS_MESSAGE,
	};
public:
	CProgressDlg();
	~CProgressDlg();

	enum { IDD = IDD_PROGRESS_DLG };


	BEGIN_MSG_MAP(CProgressDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
		MESSAGE_HANDLER(FINISH_MESSAGE, OnFinish)
		MESSAGE_HANDLER(PROGRESS_MESSAGE, OnProgress)
	END_MSG_MAP()

	virtual bool Show() override;
	virtual void Close(bool success) override;
	virtual void SetProgress(double progress) override;
	virtual void DoOnCancel(CancelHandler const& handler) override;
	virtual void DoOnOpen(OpenHandler const& handler) override;
private:

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnFinish(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnProgress(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);





private:
	CProgressBarCtrl m_progressBar;
	CancelHandler m_cancelHandler;
	OpenHandler m_openHandler;
};

