#pragma once
class EffectManager;
//int MakeHash(const char* string);

#include <d3d9.h>
#include <d3dx9effect.h>
#include <x3daudio.h>
#include <XAudio2.h>
#include <mmsystem.h>
#include <XInput.h>
#include <cstdlib>
#include <memory>
#include <vector>
#include <map>
#include <list>

#pragma comment ( lib, "winmm.lib" )

#include <stdio.h>
#include <string.h>

#include "Uncopyable.h"
#include "GameObject/GameObject.h"
#include "GameObject/GameObjectManager.h"
#include "btBulletDynamicsCommon.h"
#include "BulletCollision/CollisionDispatch/btGhostObject.h"