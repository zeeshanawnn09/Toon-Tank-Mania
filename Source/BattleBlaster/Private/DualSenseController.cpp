// Fill out your copyright notice in the Description page of Project Settings.


#include "DualSenseController.h"

#if PLATFORM_PS5 // Only compiles the code when building to PS5 DevKit

#include "SonyApplication.h"
#include "PS5Application.h"
#include "PS5Controllers.h"


FSonyInputInterface* TryGetPlatformInputInterface() //Gets the PS5 Controller

{

	if (FPS5Application::IsInitialized())

		return reinterpret_cast<FSonyInputInterface*>(FPS5Application::GetPS5Application()->GetInputInterface());

	else

		return nullptr;

}


#else


#endif

