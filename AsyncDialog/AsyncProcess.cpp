#include "stdafx.h"
#include "AsyncProcess.h"


using namespace std;
using namespace std::chrono;

CAsyncProcess::CAsyncProcess()
{
	m_interrupted = false;
	m_finished = false;
}


CAsyncProcess::~CAsyncProcess()
{
	try
	{
		m_future.get();
	}
	catch (exception const&)
	{

	}
}

void CAsyncProcess::Run()
{
	if (m_future.valid())
	{
		throw std::logic_error("Already running");
	}

	m_future = async(launch::async, &CAsyncProcess::LongRunningProcess, this);
}

void CAsyncProcess::LongRunningProcess()
{
	Status status = Failed;
	try
	{
		Task1();
		status = Succeeded;
	}
	catch (ProcessInterrupted const&)
	{
		status = Cancelled;
	}
	catch (...) //-V565
	{
	}

	m_finished = true;
	m_onFinish(status);
}

void CAsyncProcess::InterruptionPoint()const
{
	if (m_interrupted)
	{
		throw ProcessInterrupted();
	}
}

void CAsyncProcess::Cancel()
{
	m_interrupted = true;
}

boost::signals2::connection CAsyncProcess::DoOnFinish(OnFinishSlot const& handler)
{
	return m_onFinish.connect(handler);
}

void CAsyncProcess::Task1()
{
	for (int i = 1; i < 30; ++i)
	{
		this_thread::sleep_for(chrono::milliseconds(200));
		ATLTRACE("Working:%d\n", i);

		double progress = i / 29.0;
		m_onProgress(progress);

		InterruptionPoint();
	}
}

bool CAsyncProcess::HasFinished() const
{
	return m_finished;
}

boost::signals2::connection CAsyncProcess::DoOnProgressUpdate(OnProgressSlot const& handler)
{
	return m_onProgress.connect(handler);
}

