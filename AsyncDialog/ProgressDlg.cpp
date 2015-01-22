#include "stdafx.h"
#include "ProgressDlg.h"
#include "AsyncProcess.h"


CProgressDlg::CProgressDlg()
{
}


CProgressDlg::~CProgressDlg()
{
}

LRESULT CProgressDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	CenterWindow();

	m_progressBar = GetDlgItem(IDC_PROGRESS1);
	m_progressBar.SetRange(0, 100);

	if (m_openHandler)
	{
		m_openHandler();
	}

	return TRUE;
}

LRESULT CProgressDlg::OnCancel(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CButton cancelButton = GetDlgItem(IDCANCEL);
	cancelButton.EnableWindow(FALSE);

	if (m_cancelHandler)
	{
		m_cancelHandler();
	}

	return 0;
}

LRESULT CProgressDlg::OnFinish(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	EndDialog(wParam ? IDOK : IDABORT);
	return 0;
}

LRESULT CProgressDlg::OnProgress(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	m_progressBar.SetPos(wParam);
	return 0;
}

void CProgressDlg::Close(bool success)
{
	PostMessage(FINISH_MESSAGE, success);
}

void CProgressDlg::SetProgress(double progress)
{
	PostMessage(PROGRESS_MESSAGE, static_cast<WPARAM>(progress * 100));
}

void CProgressDlg::DoOnCancel(CancelHandler const& handler)
{
	m_cancelHandler = handler;
}

void CProgressDlg::DoOnOpen(OpenHandler const& handler)
{
	m_openHandler = handler;
}

bool CProgressDlg::Show()
{
	return DoModal() == IDOK;
}


