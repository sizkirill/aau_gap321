#pragma once

#include <Logic/IGameLayer.h>

class GAP321Game : public yang::IGameLayer
{
public:
	GAP321Game() = default;

	~GAP321Game() = default;

	const char* GetGameName() const override final { return "GAP321_KirillSizykh"; }
    virtual bool Init(const yang::ApplicationLayer& app) override final;

	void RegisterEvents();
	void RegisterCollisionCallbacks();
	void RegisterComponents();
	void RegisterProcesses();
	void RegisterViews();
	void RegisterScenes();
private:

};
