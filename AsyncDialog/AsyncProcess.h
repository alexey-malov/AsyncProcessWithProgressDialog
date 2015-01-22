#pragma once

class ProcessInterrupted
{

};



class ICancelableProcess
{
public:
	enum Status
	{
		Succeeded,
		Cancelled,
		Failed,
	};
	typedef boost::signals2::signal<void(Status)> OnFinish;
	typedef OnFinish::slot_type OnFinishSlot;

	typedef boost::signals2::signal<void(double)> OnProgress;
	typedef OnProgress::slot_type OnProgressSlot;


	virtual bool HasFinished()const = 0;
	virtual boost::signals2::connection DoOnFinish(OnFinishSlot const& handler) = 0;
	virtual boost::signals2::connection DoOnProgressUpdate(OnProgressSlot const& handler) = 0;
	virtual void Cancel() = 0;
	virtual void Run() = 0;

	virtual ~ICancelableProcess(){}
};


class CAsyncProcess : public ICancelableProcess
{
public:
	CAsyncProcess();
	~CAsyncProcess();

	virtual boost::signals2::connection  DoOnFinish(OnFinishSlot const& handler) override;
	virtual boost::signals2::connection DoOnProgressUpdate(OnProgressSlot const& handler) override;
	virtual void Cancel() override;
	virtual void Run() override;
private:
	void LongRunningProcess();

	void Task1();

	void InterruptionPoint()const;

	virtual bool HasFinished() const;




	std::future<void> m_future;
	std::atomic_bool m_interrupted;
	std::atomic_bool m_finished;
	OnFinish m_onFinish;
	OnProgress m_onProgress;
};

