#pragma once

class IProgressDlg;
class ICancelableProcess;

bool ExecuteProcessWithProgressDialog(ICancelableProcess & process, IProgressDlg & progressDlg);