#ifndef __APPLICATION_H__
#define __APPLICATION_H__

class App : public ElvGame::Application
{
public:
	App();
	~App();

	virtual bool onInitialize();
	virtual bool onShutdown();
};

#endif