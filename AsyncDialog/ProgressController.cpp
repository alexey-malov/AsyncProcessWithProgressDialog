#include "stdafx.h"
#include "ProgressController.h"
#include "ProgressDlg.h"
#include "AsyncProcess.h"

using namespace std;

bool ExecuteProcessWithProgressDialog(ICancelableProcess & process, IProgressDlg & progressDlg)
{
	progressDlg.DoOnCancel([&](){
		process.Cancel();
	});

	progressDlg.DoOnOpen([&](){
		process.Run();
	});

	process.DoOnFinish([&](ICancelableProcess::Status status){
		progressDlg.Close(status == ICancelableProcess::Succeeded);
	});

	process.DoOnProgressUpdate([&](double progress){
		progressDlg.SetProgress(progress);
	});

	return progressDlg.Show();
}
